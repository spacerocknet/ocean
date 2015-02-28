/*
 * JoinSessionService.cpp
 *
 *  Created on: Feb 28, 2015
 *      Author: hongsan
 */

#include "Service.h"

void JoinSessionService::execute(comm::JoinSessionRequest& request, comm::JoinSessionReply& reply)
{
	DLOG(INFO)<<"Receive JoinSessionRequest";
	reply.set_type(0);
	reply.set_name("test");
}



