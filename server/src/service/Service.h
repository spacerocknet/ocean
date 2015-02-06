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

HTTP_SERVICE_DEC(HelloService,ServiceType::HELLO);
TCP_SERVICE_DEC(PingPongService,ServiceType::PINGPONG);


#endif /* SERVICES_H_ */
