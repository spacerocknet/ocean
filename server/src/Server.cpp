/*
 * Server.cpp
 *
 *  Created on: Jan 9, 2015
 *      Author: hongsan
 */

#include "Server.h"

Server::Server()
{
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
}

bool Server::running()
{
}

