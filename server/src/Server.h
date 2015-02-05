/*
 * Server.h
 *
 *  Created on: Jan 9, 2015
 *      Author: hongsan
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <cppcms/application.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/applications_pool.h>
#include <cppcms/service.h>
#include <cppcms/http_response.h>
#include <cppcms/http_request.h>
#include <cppcms/http_context.h>
#include <booster/intrusive_ptr.h>

#include <boost/smart_ptr/shared_ptr.hpp>
#include <google/dense_hash_map>
#include <google/dense_hash_set>
#include <boost/thread/mutex.hpp>
#include <vector>
#include "Component.h"
#include "Worker.h"
#include "TaskQueue.h"
#include "Service.h"
#include "Connection.h"

#define WORKER_COUNT 10
#define QUEUE_SIZE   1000

typedef boost::shared_ptr<Component> component_ptr;
typedef google::dense_hash_map<int, service_ptr> service_map;
typedef std::vector<worker_ptr> worker_vec;
typedef google::dense_hash_map<std::string, component_ptr> component_map;
typedef google::dense_hash_set<int> listenfd_set;
typedef google::dense_hash_map<int, connection_ptr> connection_map;

class HttpLauncher: public ThreadBase
{
public:
	HttpLauncher(cppcms::service& service): service(service)
	{
	}
	virtual ~HttpLauncher()
	{

	}

	void run()
	{
		service.run();
	}
private:
	cppcms::service& service;
};

class Server: public cppcms::application
{
public:
	Server(cppcms::service &srv);
	virtual ~Server();

	/* service */
	void register_service(service_ptr service);
	/* component */
	void register_component(component_ptr component);
	component_ptr get_component(std::string id);

	void start();
	void stop();
	void push_http_task(string type);
	void push_tcp_task(message_ptr message, Connection* connection);

	void process_task();
	bool running();

	/*tcp connection*/
	bool watch(int fd);
	void tcp_loop();
	connection_ptr open_connection(std::string host, int port);
	connection_ptr add_connection(int fd);
	void close_connection(int fd);
	connection_ptr get_connection(int fd);
	int listen_connection(std::string host, int port);

	TaskQueue& get_tasks();

private:
	service_map services;
	worker_vec workers;
	component_map components;
	TaskQueue tasks;
	bool end;

	/* http */
	cppcms::service& service;
	HttpLauncher* launcher;

	/* tcp */
	int epoll_fd;
	int max_event;
	listenfd_set fds;
	connection_map connections;
	boost::mutex connection_mutex;
};

#endif /* SERVER_H_ */
