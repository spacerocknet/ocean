/*
 * main.cpp
 *
 *  Created on: Mar 20, 2013
 *      Author: nhsan
 */
#include <glog/logging.h>
#include "Server.h"
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/filesystem.hpp>
#include "service/Service.h"

using namespace boost::filesystem;

int main(int argc, char **argv)
{
	google::InitGoogleLogging(argv[0]);
	google::LogToStderr();

	try
	{
		cppcms::service service(argc, argv);
		booster::intrusive_ptr<Server> server = new Server(service);

//		component_ptr dao = boost::make_shared<uki3d::DAO>((db::Database*) database.get());
//		server->register_component(dao);

		/* register services */
		server->register_service(boost::make_shared<HelloService>(server.get()));

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
