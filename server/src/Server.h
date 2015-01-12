/*
 * Server.h
 *
 *  Created on: Jan 9, 2015
 *      Author: hongsan
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <boost/smart_ptr/shared_ptr.hpp>
#include <google/dense_hash_map>
#include <google/dense_hash_set>
#include <boost/thread/mutex.hpp>
#include <vector>
#include "Component.h"
#include "Worker.h"
#include "TaskQueue.h"
#include "Service.h"

typedef boost::shared_ptr<Component> component_ptr;
typedef std::vector<service_ptr> service_vec;
typedef std::vector<worker_ptr> worker_vec;
typedef google::dense_hash_map<std::string, component_ptr> component_map;

class Server
{
public:
	Server();
	virtual ~Server();
	Server& get_instance();

	/* service */
	void register_service(service_ptr service);
	/* component */
	void register_component(component_ptr component);
	component_ptr get_component(std::string id);



private:
	service_vec services;
	worker_vec workers;
	component_map components;
};

#endif /* SERVER_H_ */
