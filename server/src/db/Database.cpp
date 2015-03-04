/*
 * Database.cpp
 *
 *  Created on: Sep 9, 2012
 *      Author: nhsan
 */

#include "db/Database.h"
#include "leveldb/write_batch.h"

#define ENID	1

namespace db
{

Database::Database(): Component(DATABASE_COMP)
{
	locks.set_empty_key("");
	locks.set_deleted_key(".");
}

Database::~Database()
{
}

void Database::init()
{
	DLOG(INFO)<<"Init database";
	if (!open("test.db"))
	{
		throw std::runtime_error("Cannot open database");
	}
	DLOG(INFO)<<"Database component initialized";
}

leveldb::DB* Database::get_db()
{
	return db;
}

bool Database::open(string dbpath)
{
	leveldb::Options options;
	options.create_if_missing = true;
	leveldb::Status status = leveldb::DB::Open(options, dbpath, &db);

	if (status.ok())
	{
		_enc_declare_(tmp, 32);
		_enc_append_key_(tmp, LAST_EV_ID,16);
		leveldb::Slice k(_enc_data_(tmp), _enc_size_(tmp));
		leveldb::Slice v;
		db->Put(leveldb::WriteOptions(), k, v);

		if (!load_meta(ENID, en_id, en_meta_key)) return false;
		return true;
	}
	return false;
}

bool Database::load_meta(uint32_t type, uint64_t& out, string& key)
{
	_enc_declare_(k, 32);
	_enc_put_fix32_(k, model::META);
	_enc_put_fix64_(k, type);
	key = string(_enc_data_(k), _enc_size_(k));

	string val;
	leveldb::Status status = db->Get(leveldb::ReadOptions(), key, &val);
	if (status.IsNotFound())
	{
		out = 1;
		_enc_declare_(e, 32);
		_enc_put_fix64_(e, out);
		leveldb::Slice tmp(_enc_data_(e), _enc_size_(e));
		status = db->Put(leveldb::WriteOptions(), key, tmp);
		if (!status.ok()) return false;
	}
	else if (status.ok())
	{
		_dec_declare1_(d, val);
		_dec_get_fix64_(d, out);
		if (!_dec_valid_(d)) return false;
	}
	else return false;
	return true;

}

void Database::close()
{
	delete db;
}

void Database::ClearDB()
{
	leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
	it->SeekToFirst();
	while (it->Valid())
	{
		db->Delete(leveldb::WriteOptions(), it->key());
		it->Next();
	}
}

bool Database::all_free(list<string>& objs)
{
	for (list<string>::iterator it = objs.begin(); it != objs.end(); it++)
	{
		if (locks.count(*it) > 0) return false;
	}
	return true;
}

void Database::lock(list<string>& objs)
{
	boost::mutex::scoped_lock lock(mutex);

	while (!all_free(objs))
	{
		cond.wait(lock);
	}

	for (list<string>::iterator it = objs.begin(); it != objs.end(); it++)
	{
		locks.insert(*it);
	}
}

void Database::unlock(list<string>& objs)
{
	boost::mutex::scoped_lock lock(mutex);

	for (list<string>::iterator it = objs.begin(); it != objs.end(); it++)
	{
		locks.erase(*it);
	}
	cond.notify_all();
}

void Transaction::lock_entity(string id)
{
	lock_objects.push_back(id);
}

void Transaction::lock_relation(string e1, uint64_t type, string e2)
{
	_enc_declare_(rk, 64);
	_enc_put_var32_(rk, model::RELATION);
	_enc_put_string_(rk, e1);
	_enc_put_var64_(rk, type);
	_enc_append_key_(rk, e2.c_str(), e2.size());
	string key(_enc_data_(rk), _enc_size_(rk));
	lock_objects.push_back(key);
}

bool Transaction::commit(bool sync)
{
	leveldb::WriteOptions write_options;
	write_options.sync = sync;
	leveldb::Status s = db->get_db()->Write(write_options, &batch);
	unlock();
	return s.ok();
}

void Transaction::unlock()
{
	db->unlock(lock_objects);
}

void Transaction::acquire_lock()
{
	db->lock(lock_objects);
}

} /* namespace db */
