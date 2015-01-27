/*
 * Context.h
 *
 *  Created on: Jan 27, 2015
 *      Author: hongsan
 */

#ifndef CONTEXT_H_
#define CONTEXT_H_

class Context
{
	Context()
	{

	}
	virtual ~Context()
	{

	}
};

typedef boost::shared_ptr<Context> context_ptr;


#endif /* CONTEXT_H_ */
