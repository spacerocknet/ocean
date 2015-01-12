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
using namespace std;

class Task
{
public:
	Task()
	{
	}
	virtual ~Task()
	{
	}
	/* return true if this task need to be deleted after execute, otherwise return false */
	virtual bool execute(Worker* worker)=0;
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
