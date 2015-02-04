/*
 * Connection.cpp
 *
 *  Created on: Dec 13, 2011
 *      Author: NGUYEN Hong San
 */

#include "Connection.h"
#include <glog/logging.h>
#include "Message.h"
#include <boost/make_shared.hpp>
#include "commons/SocketUtil.h"
#define MAXTRIES 100

Connection::Connection(int fd)
{
	this->fd = fd;
	received = 0;
	processing = false;
	some_event_come = false;
	task = new Task(0, boost::make_shared<ReadContext>(this));
}

Connection::~Connection()
{
}

void Connection::push_read_task(TaskQueue& tasks)
{
	boost::mutex::scoped_lock lock(check_mutex);
	if (processing) watch_dog++;
	else
	{
		tasks.enqueue(task);
		processing = true;
	}
}

int Connection::get_socket()
{
	return fd;
}

int Connection::send(char* data, size_t size)
{
	boost::mutex::scoped_lock slock(send_mutex);
	int sent = 0;
	int tries = 0;
	while (sent < size)
	{
		int n = write(fd, data + sent, (size - sent));
		if (n == -1)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
			{
				tries++;
				if (tries > MAXTRIES)
				{
					DLOG(ERROR)<< "Network may has some problems";
					return -1;
				}
				usleep(100);
			}
			else return -1;
		}
		else
		{
			sent += n;
			tries = 0;
		}
	}
	return size;
}

int Connection::send_message(message_ptr const & message)
{
	int n = send(message->get_data(), message->size);
	return n;
}

bool Connection::alive()
{
	int error = 0;
	socklen_t len = sizeof(error);
	int retval = getsockopt(fd, SOL_SOCKET, SO_ERROR, &error, &len);
	return (retval == 0);
}

ReadContext::ReadContext(Connection* connection)
{
	this->connection = connection;
}
ReadContext::~ReadContext()
{
}

Connection* ReadContext::get_connection()
{
	return connection;
}

