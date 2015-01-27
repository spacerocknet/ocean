/*
 * Task.h
 *
 *  Created on: Jan 27, 2015
 *      Author: hongsan
 */

#ifndef TASK_H_
#define TASK_H_
#include "Context.h"

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
private:
	int type;
	context_ptr context;
};

typedef Task* task_ptr;

#endif /* TASK_H_ */
