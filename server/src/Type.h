/*
 * Type.h
 *
 *  Created on: Jan 29, 2015
 *      Author: hongsan
 */

#ifndef TYPE_H_
#define TYPE_H_

class ServiceType
{
public:
	enum
	{
		HELLO = 1,
		PINGPONG = 2
	};
};

class ErrorType
{
public:
	enum
	{
		INVALID_REQUEST = 1
	};
};

#endif /* TYPE_H_ */
