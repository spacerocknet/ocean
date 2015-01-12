/*
 * Worker.cpp
 *
 *  Created on: Jan 12, 2015
 *      Author: hongsan
 */

#include "Worker.h"
#include <glog/logging.h>
#include <boost/lexical_cast.hpp>
#include <stdlib.h>
#include "commons/SocketUtil.h"

Worker::Worker(int id)
{
	this->id = id;
}

Worker::~Worker()
{
}

void Worker::run()
{
	DLOG(INFO)<< "Worker " << id << " has started";
//	Engine& server = Engine::get_instance();
//	TaskQueue& tasks = server.get_tasks();
//
//	while (server.running)
//	{
//		task_ptr t = tasks.dequeue();
//		if (t == NULL) continue;
//		if (t->execute(this)) delete t;
//	}
	DLOG(INFO) << "Worker " << id << " is stopped";
}



