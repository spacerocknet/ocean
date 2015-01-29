/*
 * HelloService.cpp
 *
 *  Created on: Jan 27, 2015
 *      Author: hongsan
 */

#include "Service.h"

void HelloService::execute(cppcms::json::value& request, cppcms::json::value& reply)
{
	DLOG(INFO)<<"Receive HelloRequest";
	if (request["text"].is_undefined()) throw EXCEPTION(ErrorType::INVALID_REQUEST);
	reply["type"] = 0;
	reply["text"] = "Hello " + request["text"].str();
	DLOG(INFO)<<reply["text"].str();
}

