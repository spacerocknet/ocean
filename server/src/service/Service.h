/*
 * Services.h
 *
 *  Created on: Jan 27, 2015
 *      Author: hongsan
 */

#ifndef SERVICES_H_
#define SERVICES_H_

#include "Template.h"
#include "Exception.h"
using namespace comm;


HTTP_SERVICE_DEC(TictactoeCreateService,ServiceType::TICTACTOE_CREATE, TictactoeCreateRequest, TictactoeCreateReply);
HTTP_SERVICE_DEC(TictactoeJoinService,ServiceType::TICTACTOE_JOIN, TictactoeJoinRequest, TictactoeJoinReply);
HTTP_SERVICE_DEC(TictactoeMoveService,ServiceType::TICTACTOE_MOVE, TictactoeMoveRequest, TictactoeMoveReply);
HTTP_SERVICE_DEC(TictactoeListService,ServiceType::TICTACTOE_LIST, TictactoeListRequest, TictactoeListReply);


#endif /* SERVICES_H_ */
