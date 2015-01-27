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
#include "comm.pb.h"
#include "error.pb.h"

SERVICE_DEC(HelloService,comm::Service::HELLO);


#endif /* SERVICES_H_ */
