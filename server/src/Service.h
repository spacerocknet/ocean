/*
 * Service.h
 *
 *  Created on: Jan 12, 2015
 *      Author: hongsan
 */

#ifndef SERVICE_H_
#define SERVICE_H_

#include <string>
#include <boost/smart_ptr/shared_ptr.hpp>

class Context
{
};

class Service
{
protected:
	bool _activated;
public:
	Service()
	{
	}

	virtual ~Service()
	{
	}

	bool activated()
	{
		return _activated;
	}

	/* initialize service if necessary and set _activated flag to true */
	virtual bool activate()
	{
		_activated = true;
		return true;
	}

	/* something need to be done before deactivate service and set _activated flag to false */
	virtual void deactivate()
	{
		_activated = false;
	}

	/* return true if message match service, else return false */
	virtual bool process(Context& context)=0;
};

typedef boost::shared_ptr<Service> service_ptr;

#endif /* SERVICE_H_ */
