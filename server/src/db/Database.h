/*
 * Database.h
 *
 *  Created on: Sep 9, 2012
 *      Author: nhsan
 */

#ifndef DATABASE_H_
#define DATABASE_H_
#include <string>
#include "leveldb/db.h"
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include "model.pb.h"
#include "commons/MessageUtil.h"
#include <uuid/uuid.h>
#include <glog/logging.h>
#include "leveldb/write_batch.h"
#include <google/dense_hash_set>
#include <list>
#include "Component.h"
#include "Utils.h"

#define DATABASE_COMP	"DB"

using namespace std;

namespace db
{

typedef boost::shared_ptr<model::Entity> entity_ptr;
typedef boost::shared_ptr<model::Relation> relation_ptr;
typedef boost::shared_ptr<model::Index> index_ptr;

const uuid_t LAST_EV_ID =
{ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

enum ErrorCode
{
	OK = 0, NO_MORE_VALUE = 1, DB_ERROR = 2, IS_NOT_FOUND = 3, EXISTED = 4, OUT_OF_RANGE = 5, BAD_FORMAT = 6, UNKNOWN = 100
};

class rel_iterator;
class act_iterator;
class index_iterator;
typedef boost::shared_ptr<rel_iterator> rel_iter_ptr;
typedef boost::shared_ptr<act_iterator> act_iter_ptr;
typedef boost::shared_ptr<index_iterator> index_iter_ptr;
typedef google::dense_hash_set<string> lock_set;

class Transaction;

class Database: public Component
{
private:
	leveldb::DB* db;
	boost::mutex en_mutex;

	uint64_t en_id;
	string en_meta_key;

	bool load_meta(uint32_t type, uint64_t& out, string& key);
	boost::mutex mutex;
	boost::condition cond;
	lock_set locks;
public:
	Database();
	virtual ~Database();
	leveldb::DB* get_db();

	void init();

	bool open(string dbpath);
	void close();

	void ClearDB();

	/* locks */
	void lock(list<string>& objs);
	void unlock(std::list<string>& objs);
	bool all_free(list<string>& objs);

	/* entity */
	int en_add(model::Entity& entity);
	int en_update(model::Entity& entity);
	int en_get(string id, model::Entity& entity);
	int en_del(string id);
	bool en_check(string id, uint32_t type);

	/* relation */
	int rel_put(string e1, uint64_t type, string e2);
	int rel_put(string e1, uint64_t type, string e2, model::Relation& relation);
	int rel_get(string e1, uint64_t type, string e2, model::Relation& relation);
	bool rel_exist(string e1, uint64_t type, string e2);
	int rel_del(string e1, uint64_t type, string e2);
	rel_iter_ptr rel_iter(string entity, uint64_t type);
	rel_iter_ptr rel_seek(string entity, uint64_t type, string from );

	/* index */
	int index_set(uint64_t type, string key, string entity);
	int index_get(uint64_t type, string key, model::Entity& entity);
	bool index_exist(uint64_t type, string key);
	int index_del(uint64_t type, string key);
	index_iter_ptr index_iter(uint64_t type);
	index_iter_ptr index_last(uint64_t type);
	index_iter_ptr index_seek(uint64_t type, string from );
};

class rel_iterator
{
private:
	string eid;
	uint64_t type;
	leveldb::Iterator* it;
	Database* db;
public:
	rel_iterator(string eid, uint64_t type, leveldb::Iterator* it, Database* db)
	{
		this->eid = eid;
		this->type = type;
		this->it = it;
		this->db = db;
	}

	virtual ~rel_iterator()
	{
		if (it) delete it;
	}

	string next();
	entity_ptr next2();
	relation_ptr next3();
};

class index_iterator
{
private:
	uint64_t type;
	leveldb::Iterator* it;
	Database* db;
public:
	index_iterator(uint64_t type, leveldb::Iterator* it, Database* db)
	{
		this->type = type;
		this->it = it;
		this->db = db;
	}

	virtual ~index_iterator()
	{
		if (it) delete it;
	}

	string next();
	entity_ptr next2();
	entity_ptr prev2();
};

class Transaction
{
public:
	Transaction(Database* db)
	{
		this->db = db;
	}

	virtual ~Transaction()
	{
		unlock();
	}

	void lock_entity(string id);
	void lock_relation(string e1, uint64_t type, string e2);
	bool commit(bool sync);
	void unlock();
	void acquire_lock();

	void en_add(model::Entity& entity);
	void en_update(model::Entity& entity);
	void en_del(string id);

	void rel_put(string e1, uint64_t type, string e2);
	void rel_put(string e1, uint64_t type, string e2, model::Relation& relation);
	void rel_del(string e1, uint64_t type, string e2);

	void index_set(uint64_t type, string key, string entity);
	void index_del(uint64_t type, string key);

private:
	leveldb::WriteBatch batch;
	std::list<string> lock_objects;
	Database* db;
};

} /* namespace db */
#endif /* DATABASE_H_ */
