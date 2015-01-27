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

Server::Server(cppcms::service &srv) :
		cppcms::application(srv), service(srv)
{
	services.set_deleted_key(-1);
	services.set_empty_key(-2);
	components.set_empty_key("");
	components.set_deleted_key(" ");
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
		auto reply = it->second->process(context);

		auto hc = dynamic_cast<HttpContext*>(context.get());
		if (hc != nullptr)
		{
			/* http context */
			auto c = hc->get_context();
			if (!reply.empty())
			{
				c->response().out() << reply;
				c->async_complete_response();
			}
		}
		else
		{
			/* tcp context */
		}
	}
	delete task;
}

bool Server::running()
{
	return (!end);
}

void Server::start()
{
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
	service.run();
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

