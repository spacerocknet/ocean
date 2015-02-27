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

HTTP_SERVICE_DEC(HelloService,comm::Service::HELLO, comm::HelloRequest, comm::HelloReply);
TCP_SERVICE_DEC(PingPongService,comm::Service::PINGPONG, comm::PingpongRequest, comm::PingpongReply);


#endif /* SERVICES_H_ */
