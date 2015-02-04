/*
 * Session.h
 *
 *  Created on: Dec 13, 2011
 *      Author: NGUYEN Hong San
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include <queue>
#include "Message.h"
#include "Context.h"
#include "TaskQueue.h"

class Connection;
class ReadContext: public Context
{
public:
	ReadContext(Connection* connection);
	virtual ~ReadContext();
	Connection* get_connection();
private:
	Connection* connection;
};

class Connection
{
private:
	boost::mutex send_mutex; /* manage sending concurrence */
	boost::mutex check_mutex;
	bool some_event_come;
	bool processing;
	unsigned char header[PACKET_HEADER_SIZE];
	int received; //received data
	message_ptr reading_message;
	int fd;
	int watch_dog;
	task_ptr task;
public:
	boost::weak_ptr<Connection> me;

	Connection(int fd);
	virtual ~Connection();
	int get_socket();
	int send(char* data, size_t size);
	int send_message(message_ptr const & message);
	bool alive();
	void push_read_task(TaskQueue& tasks);
};

typedef boost::shared_ptr<Connection> connection_ptr;

#endif /* SESSION_H_ */
