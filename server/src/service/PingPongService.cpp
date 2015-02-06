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
	reply.null();
}




