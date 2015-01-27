/*
 * Worker.cpp
 *
 *  Created on: Jan 16, 2015
 *      Author: hongsan
 */

#include "Worker.h"
#include "Server.h"

Worker::Worker(int id, Server* server)
{
	this->id = id;
	this->server = server;
}

Worker::~Worker()
{

}

void Worker::run()
{
	DLOG(INFO)<< "Worker " << id << " has started";

	while (server->running())
	{
		server->process_task();
		DLOG(INFO)<<"Worker:"<<id;
	}
	DLOG(INFO) << "Worker " << id << " is stopped";
}
