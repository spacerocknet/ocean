/*
 * HelloService.cpp
 *
 *  Created on: Jan 27, 2015
 *      Author: hongsan
 */

#include "Service.h"

string HelloService::process(context_ptr context)
{
	auto hc = dynamic_cast<HttpContext*>(context.get());
	if (hc == nullptr) return "";
	auto c = hc->get_context();
	std::pair<void*, size_t> data = c->request().raw_post_data();
	comm::HelloRequest request;
	comm::Reply reply;

	try
	{
		if ((!data.first) || (!request.ParseFromArray(data.first, data.second))) throw EXCEPTION(REQUEST_INVALID);
		reply.set_type(OK);

	}
	catch (Exception &e)
	{
		reply.set_type(e.get_type());
		DLOG(INFO)<<"Exception "<<e.get_type();
	}

	return reply.SerializeAsString();
}

