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
	/*TODO: validate request data */
	/*TODO: send notification to all players in this session */
	reply.set_type(0);
}



