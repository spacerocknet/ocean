/*
 * TaskQueue.h
 *
 *  Created on: Jan 9, 2015
 *      Author: hongsan
 */

#ifndef TASKQUEUE_H_
#define TASKQUEUE_H_

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include <google/dense_hash_map>
#include <list>
#include "Worker.h"
#include "Context.h"
using namespace std;

class Task
{
public:
	Task(int type, context_ptr context)
	{
		this->type = type;
		this->context = context;
	}
	virtual ~Task()
	{
	}
	int get_type()
	{
		return type;
	}
	context_ptr get_context()
	{
		return context;
	}
private:
	int type;
	context_ptr context;
};

typedef Task* task_ptr;

class TaskQueue
{
private:
	task_ptr* data;
	task_ptr* first;
	task_ptr* last;
	task_ptr* next;
	task_ptr* end_of_data;

	boost::mutex read_mutex;
	boost::mutex write_mutex;
	boost::condition empty_cond;
	boost::condition full_cond;
	bool end;

	//boost::mutex lock_mutex;
public:
	TaskQueue();
	void init(int size);
	virtual ~TaskQueue();
	void enqueue(task_ptr task);
	task_ptr dequeue();
	bool empty();
	void start();
	void stop();
};

#endif /* TASKQUEUE_H_ */
