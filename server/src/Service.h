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
#include "comm.pb.h"

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

template<class Request, class Reply>
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
		Request request;
		Reply reply;

		auto hc = dynamic_cast<HttpContext*>(context.get());
		if (hc == nullptr) return;
		auto c = hc->get_context();

		try
		{
			auto data = c->request().raw_post_data();
			if (data.second == 0) throw EXCEPTION(comm::Error::INVALID_REQUEST);
			if (!request.ParseFromArray(data.first, data.second)) throw EXCEPTION(comm::Error::INVALID_REQUEST);
			execute(request, reply);
		}
		catch (Exception &e)
		{
			DLOG(INFO)<<"Exception "<<e.get_type();
			reply.set_type(e.get_type());
		}

		c->response().out() << reply.SerializeAsString();
		c->async_complete_response();
	}

	virtual void execute(Request& request, Reply& reply) = 0;
};

template<class Request, class Reply>
class TcpService: public Service
{
public:
	TcpService(int type, Server* server): Service(type,server)
	{
	}

	virtual ~TcpService()
	{
	}

	virtual void process(context_ptr context)
	{
		Request request;
		Reply reply;

		auto tc = dynamic_cast<TcpContext*>(context.get());
		if (tc == nullptr) return;
		auto con = tc->get_connection();
		auto msg = tc->get_message();


		try
		{
			if (!request.ParseFromArray(msg->get_content_data(), msg->get_content_size())) throw EXCEPTION(comm::Error::INVALID_REQUEST);
			execute(request, reply);
		}
		catch (Exception &e)
		{
			DLOG(INFO)<<"Exception "<<e.get_type();
			reply.set_type(e.get_type());
		}

		auto rep = Message::encode(reply.SerializeAsString(),0, msg->id);
		con->send_message(rep);
	}

	virtual void execute(Request& request, Reply& reply) = 0;
};

#endif /* SERVICE_H_ */
