/*
 * HelloService.cpp
 *
 *  Created on: Jan 27, 2015
 *      Author: hongsan
 */

#include "Service.h"

void HelloService::process(context_ptr context)
{
	cppcms::json::value request;
	cppcms::json::value reply;

	DLOG(INFO)<<"Receive HelloRequest";
	auto hc = dynamic_cast<HttpContext*>(context.get());
	if (hc == nullptr) return;
	auto c = hc->get_context();

	try
	{
		auto data = c->request().raw_post_data();
		if (data.second>0)
		{
			std::istringstream ss(std::string(reinterpret_cast<char const *>(data.first),data.second));
			if(!request.load(ss,true)) throw EXCEPTION(1);
		}

		reply["type"] = 0;
		reply["text"] = request["text"];
	}
	catch (Exception &e)
	{
		DLOG(INFO)<<"Exception "<<e.get_type();
		reply["type"] = e.get_type();
	}

	c->response().out() << reply;
	c->async_complete_response();
}

