/*
 * PingPongService.cpp
 *
 *  Created on: Feb 6, 2015
 *      Author: hongsan
 */

#include "Service.h"

void PingPongService::execute(cppcms::json::value& request, cppcms::json::value& reply)
{
	DLOG(INFO)<<"Receive PingPongRequest";
	if (request["text"].is_undefined()) throw EXCEPTION(ErrorType::INVALID_REQUEST);
	DLOG(INFO)<<request["text"].str();
	reply["type"] = 0;
	reply["text"] = "PONG";
}




