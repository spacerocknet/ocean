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

/******************************************************************************************************************/
#define HTTP_SERVICE_DEC(name, type) \
class name: public HttpService \
{\
public:\
	name(Server* server) : HttpService(type, server)\
	{\
	}\
	virtual ~name()\
	{\
	}\
	void execute(cppcms::json::value& request, cppcms::json::value& reply);\
};

#define TCP_SERVICE_DEC(name, type) \
class name: public TcpService \
{\
public:\
	name(Server* server) : TcpService(type, server)\
	{\
	}\
	virtual ~name()\
	{\
	}\
	void execute(cppcms::json::value& request, cppcms::json::value& reply);\
};

/******************************************************************************************************************/


#endif /* HTTPTEMPLATE_H_ */
