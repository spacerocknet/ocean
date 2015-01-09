/*
 * Entity.cpp
 *
 *  Created on: Nov 13, 2012
 *      Author: nhsan
 */

#include "db/Database.h"
#include "leveldb/write_batch.h"

#define entity_key(id, slice)\
	_enc_declare_(ek, 32);\
	_enc_put_var32_(ek, model::ENTITY);\
	_enc_append_key_(ek, id.c_str(), id.size());\
	leveldb::Slice slice(_enc_data_(ek), _enc_size_(ek));

namespace db
{

int Database::en_add(model::Entity& entity)
{
	uuid_t uuid;
	uuid_generate_time(uuid);
	//string eid((char*) uuid, 16);
	string eid = Utils::pack_uuid(uuid);
	entity_key(eid, k);
	entity.set_id(eid);
	string v = entity.SerializeAsString();

	leveldb::Status s = db->Put(leveldb::WriteOptions(), k, v);
	if (s.ok()) return db::OK;
	return db::DB_ERROR;
}

void Transaction::en_add(model::Entity& entity)
{
	uuid_t uuid;
	uuid_generate_time(uuid);
	string eid = Utils::pack_uuid(uuid);
	entity_key(eid, k);
	entity.set_id(eid);
	string v = entity.SerializeAsString();
	batch.Put(k, v);
}

int Database::en_update(model::Entity& entity)
{
	entity_key(entity.id(), k);
	string v;

	leveldb::Status s = db->Get(leveldb::ReadOptions(), k, &v);
	if (s.ok())
	{
		string v = entity.SerializeAsString();
		leveldb::Status s = db->Put(leveldb::WriteOptions(), k, v);
		if (s.ok()) return db::OK;
		return db::DB_ERROR;
	}
	return db::IS_NOT_FOUND;
}

void Transaction::en_update(model::Entity& entity)
{
	entity_key(entity.id(), k);
	string v = entity.SerializeAsString();
	batch.Put(k, v);
}

int Database::en_get(string id, model::Entity& entity)
{
	entity_key(id, k);
	string v;

	leveldb::Status s = db->Get(leveldb::ReadOptions(), k, &v);
	if (s.ok())
	{
		if (!entity.ParseFromString(v)) return db::BAD_FORMAT;
		return db::OK;
	}
	if (s.IsNotFound()) return db::IS_NOT_FOUND;
	return db::DB_ERROR;
}

bool Database::en_check(string id, uint32_t type)
{
	entity_key(id, k);
	string v;
	model::Entity entity;

	leveldb::Status s = db->Get(leveldb::ReadOptions(), k, &v);
	if (s.ok())
	{
		if (!entity.ParseFromString(v)) return false;
		if (entity.type() == type) return true;
	}
	return false;
}

int Database::en_del(string id)
{
	entity_key(id, k);

	leveldb::Status status = db->Delete(leveldb::WriteOptions(), k);
	if (status.ok()) return db::OK;
	if (status.IsNotFound()) return db::IS_NOT_FOUND;
	return db::DB_ERROR;
}

void Transaction::en_del(string id)
{
	entity_key(id, k);
	batch.Delete(k);
}

} //namespace
