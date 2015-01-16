/*
 * Server.cpp
 *
 *  Created on: Jan 9, 2015
 *      Author: hongsan
 */

#include "Server.h"
#include "Worker.h"
#include <boost/smart_ptr/make_shared.hpp>

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
//	dispatcher().assign("/o/(.+)", &Server::get_object, this, 1);
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

void Server::process_task()
{
	task_ptr task = tasks.dequeue();
	if (task==nullptr) return;

	auto it = services.find(task->get_type());
	if (it == services.end())
	{
	}
	else
	{
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

