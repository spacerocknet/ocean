/*
 * Server.cpp
 *
 *  Created on: Jan 9, 2015
 *      Author: hongsan
 */

#include "Server.h"
#include "Worker.h"
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/lexical_cast.hpp>
#include "commons/SocketUtil.h"
#include <sys/epoll.h>

Server::Server(cppcms::service &srv) :
		cppcms::application(srv), service(srv)
{
	services.set_deleted_key(-1);
	services.set_empty_key(-2);

	components.set_empty_key("");
	components.set_deleted_key(" ");

	fds.set_empty_key(-1);
	fds.set_deleted_key(-2);

	connections.set_empty_key(-1);
	connections.set_deleted_key(-2);

	tasks.init(QUEUE_SIZE);
	for (int i = 0; i < WORKER_COUNT; i++)
	{
		workers.push_back(boost::make_shared<Worker>(i, this));
	}
	end = true;
	dispatcher().assign("/r/([0-9]+)", &Server::push_http_task, this, 1);
}

Server::~Server()
{
}

void Server::register_service(service_ptr service)
{
	services[service->get_type()] = service;
}

void Server::register_component(component_ptr component)
{
	components[component->get_id()] = component;
}

component_ptr Server::get_component(std::string id)
{
	component_map::iterator it = components.find(id);
	if (it != components.end()) return it->second;
	return component_ptr();
}

void Server::push_http_task(string type)
{
	DLOG(INFO)<<"Push http task:"<<type<< " from:"<< request().remote_addr();
	http_context c = this->release_context();
	context_ptr context = boost::make_shared<HttpContext>(c);
	task_ptr t = new Task(boost::lexical_cast<int>(type),context);
	tasks.enqueue(t);
}

void Server::process_task()
{
	auto task = tasks.dequeue();
	if (task == nullptr) return;

	auto it = services.find(task->get_type());

	if (it != services.end())
	{
		auto context = task->get_context();
		it->second->process(context);
	}
	delete task;
}

bool Server::running()
{
	return (!end);
}

void Server::start()
{
	/* create epoll */
	epoll_fd = epoll_create1(0);
	if (epoll_fd == -1)
	{
		throw std::runtime_error("Error in epoll_create");
	}

	for (auto& c : components)
	{
		c.second->init();
	}

	for (auto& c : components)
	{
		c.second->start();
	}

	end = false;
	tasks.start();
	for (auto& w : workers)
	{
		w->start();
	}
	//service.run();
	launcher = new HttpLauncher(service);
	launcher->start();
	tcp_loop();
}

void Server::stop()
{
	end = true;
	tasks.stop();
	for (auto& w : workers)
	{
		w->join();
	}

	for (auto& c : components)
	{
		c.second->stop();
	}
	service.shutdown();
}

bool Server::watch(int fd)
{
	int s;
	struct epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN | EPOLLET;
	s = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event);
	if (s == -1)
	{
		DLOG(ERROR)<< "Error in epoll_ctl";
		return false;
	}
	return true;
}

void Server::tcp_loop()
{
	int s;
	struct epoll_event event;
	struct epoll_event *events;

	/* Buffer where events are returned */
	events = (epoll_event*) calloc(max_event, sizeof event);

	DLOG(INFO)<< "Starting main loop";
	while (running())
	{
		int n, i;
		n = epoll_wait(epoll_fd, events, max_event, -1);
		for (i = 0; i < n; i++)
		{
			if ((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP) || (!(events[i].events & EPOLLIN)))
			{
				/* An error has occured on this fd, or the socket is not ready for reading (why were we notified then?) */
				DLOG(ERROR)<< "epoll error";
				close_connection(events[i].data.fd);
				continue;
			}
			else if (fds.count(events[i].data.fd) > 0)
			{
				/* We have a notification on the listening socket, which means one or more incoming connections. */
				while (1)
				{
					struct sockaddr in_addr;
					socklen_t in_len;
					int infd;
					char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];

					in_len = sizeof in_addr;
					infd = accept(events[i].data.fd, &in_addr, &in_len);
					if (infd == -1)
					{
						if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
						{
							/* We have processed all incoming connections. */
							break;
						}
						else
						{
							perror("accept");
							break;
						}
					}

					s = getnameinfo(&in_addr, in_len, hbuf, sizeof hbuf, sbuf, sizeof sbuf, NI_NUMERICHOST | NI_NUMERICSERV);
					if (s == 0) DLOG(INFO) << "Accepted connection on descriptor " << infd << " (host=" << hbuf << ", port=" << sbuf << ")";

					/* Make the incoming socket non-blocking and add it to the list of fds to monitor. */
					s = SocketUtils::make_socket_non_blocking(infd);
					if (s == -1)
					{
						break;
					}

					connection_ptr conn = add_connection(infd);
					if (conn == NULL) close(infd);
					continue;
				}
			}
			else
			{
				/* push event to queue */
				//DLOG(INFO) << "new read event";
				connection_ptr con = get_connection(events[i].data.fd);
				//TODO: if (con != NULL) con->notify_read();
			}
		}
	}

	free(events);

}

connection_ptr Server::open_connection(std::string host, int port)
{
	std::string port_str = boost::lexical_cast<std::string>(port);
	int fd = SocketUtils::socket_connection_new(host.c_str(), port_str.c_str(), 0);
	if (fd < 0) return connection_ptr();
	SocketUtils::make_socket_non_blocking(fd);
	connection_ptr conn = add_connection(fd);
	return conn;
}

int Server::listen_connection(std::string host, int port)
{
	std::string mport = boost::lexical_cast<std::string>(port);
	int listen_fd = SocketUtils::create_and_bind(mport.c_str());
	if (listen_fd == -1) return -1;

	int s = SocketUtils::make_socket_non_blocking(listen_fd);
	if (s == -1)
	{
		close(listen_fd);
		return -1;
	}

	s = listen(listen_fd, SOMAXCONN);
	if (s == -1)
	{
		DLOG(ERROR)<< "Error in connection listening";
		close(listen_fd);
		return -1;
	}

	if (!watch(listen_fd))
	{
		close(listen_fd);
		return -1;
	}
	DLOG(INFO)<<"Start listing on "<<host<<":"<<port;
	fds.insert(listen_fd);
	return listen_fd;
}

void Server::close_connection(int fd)
{
	if (fd == 0) return;
	boost::mutex::scoped_lock lock(connection_mutex);
	connections.erase(fd);

	/* check if socket is closed */
	int error = 0;
	socklen_t len = sizeof(error);
	int retval = getsockopt(fd, SOL_SOCKET, SO_ERROR, &error, &len);

	/* close it */
	if (retval != 0)
	{
		DLOG(INFO)<<"Close socket:"<<fd;
		close(fd);
	}
}

connection_ptr Server::add_connection(int fd)
{
	int s;
	struct epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN | EPOLLET;
	s = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event);
	if (s == -1)
	{
		DLOG(ERROR)<< "Error in epoll_ctl";
		return connection_ptr();
	}
	connection_ptr conn = boost::make_shared<Connection>(fd);
	conn->me = conn;
	connection_mutex.lock();
	connections[fd] = conn;
	connection_mutex.unlock();
	return conn;
}

connection_ptr Server::get_connection(int fd)
{
	boost::mutex::scoped_lock lock(connection_mutex);
	connection_map::iterator it = connections.find(fd);
	if (it == connections.end()) return connection_ptr();
	return it->second;
}

void Server::interrupt_cb(int sig)
{
	DLOG(INFO)<<"Stop by SIGINT";
	this->stop();
}



