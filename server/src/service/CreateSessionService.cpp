/*
 * CreateSessionService.cpp
 *
 *  Created on: Feb 27, 2015
 *      Author: hongsan
 */

#include "Service.h"

void CreateSessionService::execute(comm::CreateSessionRequest& request, comm::CreateSessionReply& reply)
{
	DLOG(INFO)<<"Receive CreateSessionRequest";
	reply.set_type(0);
	reply.set_host("127.0.0.1");
	reply.set_port(5678);
	reply.set_sid(Utils::generate_session_id());

	/* TODO: validate and put session to SessionManager */
}


