/*
 * DAO.h
 *
 *  Created on: Aug 8, 2013
 *      Author: nhsan
 */

#ifndef DAO_H_
#define DAO_H_

#define DAO_COMP "DAO"

#include "ocean.pb.h"
#include "comm.pb.h"
#include "type.pb.h"

#include "Exception.h"
#include "Utils.h"
#include "db/Database.h"
#include "Component.h"

#include <vector>
#include <list>
#include <queue>
#include "boost/thread.hpp"
#include <boost/thread/mutex.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <cppcms/http_request.h>
#include <cppcms/json.h>

using namespace db;
using namespace std;
using namespace ocean;


#define count_key(e,count, key, k)\
	_enc_declare_(e, 32)\
	_enc_put_fix32_(e, (0xEFFFFFFF - count));\
	_enc_put_buffer_(e, key, key.size());\
	string k((char*) _enc_data_(e), _enc_size_(e));

class DAO: public Component
{
private:
	Database* db;

public:
	DAO(Database* db);
	virtual ~DAO();
	Database* get_db();

	/* commons */
	entity_ptr get_entity(string id, uint32_t type);

	/*USER*/
	entity_ptr get_player(string uid);
	entity_ptr create_player(Player& data);

	/*SESSION*/
	entity_ptr create_session(Session& data);
	void update_session(string id, Session& data);
	void delete_session(string id);

	/*TICTACTOE*/
	void tictactoe_move(string player, string session,int row, int col, int value);
};

#endif /* DAO_H_ */


