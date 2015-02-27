/*
 * HttpTemplate.h
 *
 *  Created on: Jan 27, 2015
 *      Author: hongsan
 */

#ifndef HTTPTEMPLATE_H_
#define HTTPTEMPLATE_H_

#include <boost/make_shared.hpp>
#include "Utils.h"
#include "../Service.h"
#include "../Server.h"
#include "comm.pb.h"

/******************************************************************************************************************/
#define HTTP_SERVICE_DEC(name, type, REQUEST, REPLY) \
class name: public HttpService<REQUEST, REPLY> \
{\
public:\
	name(Server* server) : HttpService(type, server)\
	{\
	}\
	virtual ~name()\
	{\
	}\
	void execute(REQUEST& request, REPLY& reply);\
};

#define TCP_SERVICE_DEC(name, type, REQUEST, REPLY) \
class name: public TcpService<REQUEST, REPLY> \
{\
public:\
	name(Server* server) : TcpService(type, server)\
	{\
	}\
	virtual ~name()\
	{\
	}\
	void execute(REQUEST& request, REPLY& reply);\
};

/******************************************************************************************************************/


#endif /* HTTPTEMPLATE_H_ */
