/*
 * Service.h
 *
 *  Created on: Jan 12, 2015
 *      Author: hongsan
 */

#ifndef SERVICE_H_
#define SERVICE_H_

#include <string>
#include "TaskQueue.h"
#include <boost/smart_ptr/shared_ptr.hpp>

class Server;

class Service
{
protected:
	int type;
	Server* server;
public:
	Service(int type, Server* server)
	{
		this->type = type;
		this->server = server;
	}

	int get_type()
	{
		return type;
	}

	virtual ~Service()
	{
	}
	virtual string process(context_ptr context)=0;
};

typedef boost::shared_ptr<Service> service_ptr;

#endif /* SERVICE_H_ */
