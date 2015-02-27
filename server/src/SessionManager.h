/*
 * SessionManager.h
 *
 *  Created on: Feb 27, 2015
 *      Author: hongsan
 */

#ifndef SESSIONMANAGER_H_
#define SESSIONMANAGER_H_
#include <boost/smart_ptr/shared_ptr.hpp>
#include <list>
#include <string>
using namespace std;

class Player
{

private:
	string name;
public:

};

typedef boost::shared_ptr<Player> player_ptr;
typedef list<player_ptr> player_list;

class Session
{

private:
	player_list players;
public:

};

typedef boost::shared_ptr<Session> session_ptr;
typedef list<session_ptr> session_list;

class SessionManager
{
private:
	session_list sessions;
public:
	SessionManager();
	virtual ~SessionManager();
};

#endif /* SESSIONMANAGER_H_ */
