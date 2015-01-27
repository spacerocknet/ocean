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
	TcpContext()
	{
	}

	virtual ~TcpContext()
	{
	}
};


#endif /* CONTEXT_H_ */
