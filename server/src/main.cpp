/*
 * main.cpp
 *
 *  Created on: Mar 20, 2013
 *      Author: nhsan
 */
#include <glog/logging.h>
#include "Server.h"
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/filesystem.hpp>
#include "service/Service.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
using namespace boost::filesystem;

#define REG_SERVICE(name)\
server->register_service(boost::make_shared<name>(server.get()));\
DLOG(INFO)<<"Service '" << #name << "' is registered";

boost::function<void(void)> stop_server;
void interrupt_cb( int value )
{
	stop_server();
}
void hook_interrupt(Server* server)
{
	/* hook SIGTERM (kill) and SIGINT (Ctrl-C) */
	struct sigaction act;
	memset(&act, 0, sizeof(act));
	stop_server = boost::bind(&Server::stop, server);
	act.sa_handler = interrupt_cb;
	if (sigaction(SIGINT, &act, 0))
	{
		DLOG(ERROR)<< "Sigint action error";
	}
	if (sigaction(SIGTERM, &act, 0))
	{
		DLOG(ERROR)<< "Sigterm action error";
	}
}

int main(int argc, char **argv)
{
	google::InitGoogleLogging(argv[0]);
	google::LogToStderr();

	try
	{
		cppcms::service service(argc, argv);
		booster::intrusive_ptr<Server> server = new Server(service);
		hook_interrupt(server.get());

		/* register services */
		REG_SERVICE(HelloService);
		REG_SERVICE(PingPongService);
		REG_SERVICE(CreateSessionService);

		/* start server */
		service.applications_pool().mount(server);
		DLOG(INFO)<<"Server is running...";
		server->start();
		server->stop();
		DLOG(INFO)<<"Server is stopped";
	}
	catch (std::exception const &e)
	{
		DLOG(ERROR)<< "Catched exception: " << e.what();
		return 1;
	}

	return 0;
}
