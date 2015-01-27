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
#define SERVICE_DEC(name, type) \
class name: public Service \
{\
public:\
	name(Server* server) : Service(type, server)\
	{\
	}\
	virtual ~name()\
	{\
	}\
	string process(context_ptr context);\
};
/******************************************************************************************************************/


#endif /* HTTPTEMPLATE_H_ */
