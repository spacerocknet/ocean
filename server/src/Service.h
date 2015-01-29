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

#include <cppcms/http_response.h>
#include <cppcms/http_request.h>
#include <cppcms/json.h>
#include "Exception.h"
#include "Type.h"

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
	virtual void process(context_ptr context)=0;
};

typedef boost::shared_ptr<Service> service_ptr;

class HttpService: public Service
{
public:
	HttpService(int type, Server* server): Service(type,server)
	{
	}

	virtual ~HttpService()
	{
	}

	virtual void process(context_ptr context)
	{
		cppcms::json::value request;
		cppcms::json::value reply;

		auto hc = dynamic_cast<HttpContext*>(context.get());
		if (hc == nullptr) return;
		auto c = hc->get_context();

		try
		{
			auto data = c->request().raw_post_data();
			if (data.second == 0) throw EXCEPTION(ErrorType::INVALID_REQUEST);
			std::istringstream ss(std::string(reinterpret_cast<char const *>(data.first), data.second));
			if (!request.load(ss, true)) throw EXCEPTION(ErrorType::INVALID_REQUEST);
			execute(request, reply);
		}
		catch (Exception &e)
		{
			DLOG(INFO)<<"Exception "<<e.get_type();
			reply["type"] = e.get_type();
		}

		c->response().out() << reply;
		c->async_complete_response();
	}

	virtual void execute(cppcms::json::value& request, cppcms::json::value& reply) = 0;
};

#endif /* SERVICE_H_ */
