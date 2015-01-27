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

#define WORKER_COUNT 10
#define QUEUE_SIZE   1000

typedef boost::shared_ptr<Component> component_ptr;
typedef google::dense_hash_map<int, service_ptr> service_map;
typedef std::vector<worker_ptr> worker_vec;
typedef google::dense_hash_map<std::string, component_ptr> component_map;

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
	void process_task();
	bool running();
private:
	service_map services;
	worker_vec workers;
	component_map components;
	TaskQueue tasks;
	bool end;
	cppcms::service& service;
};

#endif /* SERVER_H_ */
