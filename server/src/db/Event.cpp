/*
 * Event.cpp
 *
 *  Created on: Nov 13, 2012
 *      Author: nhsan
 */

#include "db/Database.h"
#include "leveldb/write_batch.h"

#define event_key(id, slice)\
	_enc_declare_(ek, 32);\
	_enc_put_var32_(ek, model::EVENT);\
	_enc_append_key_(ek, id.c_str(), id.size());\
	leveldb::Slice slice(_enc_data_(ek), _enc_size_(ek));

namespace db
{

int Database::ev_add(model::Event& event)
{
	uuid_t uuid;
	uuid_generate_time(uuid);
	string ev_id = Utils::pack_uuid(uuid);
	event_key(ev_id, k);
	event.set_id(ev_id);
	event.set_time(time(NULL));
	string v = event.SerializeAsString();
	leveldb::Status s = db->Put(leveldb::WriteOptions(), k, v);
	if (s.ok()) return db::OK;
	return db::DB_ERROR;
}

void Transaction::ev_add(model::Event& event)
{
	uuid_t uuid;
	uuid_generate_time(uuid);
	string ev_id = Utils::pack_uuid(uuid);
	event_key(ev_id, k);
	event.set_id(ev_id);
	event.set_time(time(NULL));
	string v = event.SerializeAsString();
	batch.Put(k, v);
}

int Database::ev_update(model::Event& event)
{
	event_key(event.id(), k);

	string v;
	leveldb::Status s = db->Get(leveldb::ReadOptions(), k, &v);
	if (s.ok())
	{
		string v = event.SerializeAsString();
		leveldb::Status s = db->Put(leveldb::WriteOptions(), k, v);
		if (s.ok()) return db::OK;
		return db::DB_ERROR;
	}
	return db::IS_NOT_FOUND;
}

void Transaction::ev_update(model::Event& event)
{
	event_key(event.id(), k);
	string v = event.SerializeAsString();
	batch.Put(k, v);
}

int Database::ev_get(string eid, model::Event& event)
{
	event_key(eid, k);
	string v;

	leveldb::Status s = db->Get(leveldb::ReadOptions(), k, &v);
	if (s.ok())
	{
		if (!event.ParseFromString(v)) return db::BAD_FORMAT;
		return db::OK;
	}
	return db::IS_NOT_FOUND;
}

int Database::ev_del(string eid)
{
	event_key(eid, k);
	leveldb::Status status = db->Delete(leveldb::WriteOptions(), k);
	if (status.ok()) return db::OK;
	if (status.IsNotFound()) return db::IS_NOT_FOUND;
	return db::DB_ERROR;
}

void Transaction::ev_del(string id)
{
	event_key(id, k);
	batch.Delete(k);
}

} //namespace

