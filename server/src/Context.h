/*
 * Context.h
 *
 *  Created on: Jan 27, 2015
 *      Author: hongsan
 */

#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <cppcms/http_context.h>
#include <booster/intrusive_ptr.h>
#include "Message.h"
#include "Connection.h"

class Context
{
public:
	Context()
	{

	}
	virtual ~Context()
	{

	}
};

typedef boost::shared_ptr<Context> context_ptr;
typedef booster::shared_ptr<cppcms::http::context> http_context;

class HttpContext: public Context
{
public:
	HttpContext(http_context context)
	{
		this->context = context;
	}

	virtual ~HttpContext()
	{
	}

	http_context get_context()
	{
		return context;
	}
private:
	http_context context;
};

class TcpContext: public Context
{
public:
	TcpContext(message_ptr message, Connection* connection)
	{
		this->message= message;
		this->connection = connection;
	}

	virtual ~TcpContext()
	{
	}
private:
	message_ptr message;
	Connection* connection;
};

class ReadContext: public Context
{
public:
	ReadContext(Connection* connection)
	{
		this->connection = connection;
	}
	virtual ~ReadContext()
	{

	}
	Connection* get_connection()
	{
		return connection;
	}
private:
	Connection* connection;
};

#endif /* CONTEXT_H_ */
