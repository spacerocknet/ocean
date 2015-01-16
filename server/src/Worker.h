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
#include <glog/logging.h>

using namespace std;

class Server;
class Worker: public ThreadBase
{
private:
	int id;
	Server* server;
public:
	Worker(int id, Server* server);
	virtual ~Worker();
	void run();
};

typedef boost::shared_ptr<Worker> worker_ptr;

#endif /* WORKER_H_ */
