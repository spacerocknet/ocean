/*
 * PingPongService.cpp
 *
 *  Created on: Feb 6, 2015
 *      Author: hongsan
 */

#include "Service.h"

void PingPongService::execute(comm::PingpongRequest& request, comm::PingpongReply& reply)
{
	DLOG(INFO)<<"Receive PingPongRequest";
	reply.set_type(0);
	reply.set_text("PONG");
}




