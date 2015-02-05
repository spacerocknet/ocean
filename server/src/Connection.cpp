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
#include "Server.h"
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

void Connection::push_read_task(Server* server)
{
	TaskQueue& tasks = server->get_tasks();
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
	size_t sent = 0;
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

bool Connection::read_message(Server* server)
{
	while (1) //loop until no more data in socket
	{
		watch_dog = 0;
		if (received < PACKET_HEADER_SIZE)
		{
			/* read header data */
			int count = read(fd, header, PACKET_HEADER_SIZE - received);
			if (count == 0)
			{
				DLOG(INFO)<< "Close connection:" << fd;
				server->close_connection(fd);
				return false;
			}
			else if (count == -1)
			{
				if (errno != EAGAIN)
				{
					DLOG(ERROR) << "Something wrong with connection:" << fd;
					return false;
				}
				else
				{
					boost::mutex::scoped_lock lock(check_mutex);
					if (watch_dog == 0)
					{
						processing = false;
						break;
					}
					else continue;
				}
			}

			received += count;
			if (received == PACKET_HEADER_SIZE)
			{
				if (header[0] != PACKET_MAGIC || header[1] != PACKET_MAGIC)
				{
					DLOG(ERROR)<< "Magic bytes are not matched";
					//TODO: handle error
				}

				int size, type;
				size = (header[2] << 8) + header[3]; // 2 bytes for size
				type = (header[4] << 16) + (header[5] << 8) + header[6];//3 bytes for type

				reading_message = boost::make_shared<Message>(size, type);
				memcpy(reading_message->get_data(), header, PACKET_HEADER_SIZE);
			}
		}
		else if (received < reading_message->size) //size here mean packet size not content size
		{
			/* read message data */
			int count = read(fd, reading_message->get_data() + received, reading_message->size - received);
			if (count == 0)
			{
				//DLOG(INFO) << "Close connection:" << ev->fd;
				reading_message.reset();
				return false;
			}
			else if (count == -1)
			{
				if (errno != EAGAIN)
				{
					DLOG(ERROR) << "Something wrong with connection:" << fd;
					reading_message.reset();
					return false;
				}
				else
				{
					boost::mutex::scoped_lock lock(check_mutex);
					if (watch_dog == 0)
					{
						processing = false;
						break;
					}
					else continue;
				}
			}

			received += count;
		}
		else if (received == reading_message->size)
		{
			/* decode message_id and streaming type*/
			bool has_id;
			has_id = ((header[7] & 0x02) == 2);

			unsigned char* tmp_data = (unsigned char*) (reading_message->get_data() + 8);

			if (has_id)
			{
				uint64_t message_id = tmp_data[0];
				message_id <<= 8;
				message_id += tmp_data[1];
				message_id <<= 8;
				message_id += tmp_data[2];
				message_id <<= 8;
				message_id += tmp_data[3];
				message_id <<= 8;
				message_id += tmp_data[4];
				message_id <<= 8;
				message_id += tmp_data[5];
				message_id <<= 8;
				message_id += tmp_data[6];
				message_id <<= 8;
				message_id += tmp_data[7];
				reading_message->id = message_id;
			}
			else reading_message->id = 0;
			server->push_tcp_task(reading_message, this);
			received = 0;//ready for new packet
			reading_message.reset();
		}
	}

	return true;
}
