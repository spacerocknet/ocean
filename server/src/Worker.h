/*
 * Worker.h
 *
 *  Created on: Jan 9, 2015
 *      Author: hongsan
 */

#ifndef WORKER_H_
#define WORKER_H_

#include "commons/ThreadBase.h"
#include <list>
using namespace std;

class Worker: public ThreadBase
{
private:
	int id;
public:
	Worker(int id);
	virtual ~Worker();
	void run();
};

typedef boost::shared_ptr<Worker> worker_ptr;

#endif /* WORKER_H_ */
