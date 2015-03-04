/*
 * Property.cpp
 *
 *  Created on: Nov 15, 2012
 *      Author: nhsan
 */
#include "db/Database.h"
#include "leveldb/write_batch.h"

#define property_key(eid, type, slice)\
	_enc_declare_(pk, 32);\
	_enc_put_var32_(pk, model::PROPERTY);\
	_enc_append_key_(pk, eid.c_str(), eid.size());\
	_enc_put_var64_(pk, type);\
	leveldb::Slice slice(_enc_data_(pk), _enc_size_(pk));

namespace db
{

//int Database::prop_put(string entity, uint64_t type, model::Property& prop)
//{
//
//	property_key(entity, type, k);
//	string v = prop.SerializeAsString();
//	leveldb::Status s = db->Put(leveldb::WriteOptions(), k, v);
//	if (s.ok()) return db::OK;
//	return db::DB_ERROR;
//}
//
//int Database::prop_get(string entity, uint64_t type, model::Property& prop)
//{
//	property_key(entity, type, k);
//	string v;
//	leveldb::Status s = db->Get(leveldb::ReadOptions(), k, &v);
//	if (s.ok())
//	{
//		if (!prop.ParseFromString(v)) return db::BAD_FORMAT;
//		return db::OK;
//	}
//	return db::IS_NOT_FOUND;
//}
//
//bool Database::prop_exist(string entity, uint64_t type)
//{
//	property_key(entity, type, k);
//	string v;
//	leveldb::Status s = db->Get(leveldb::ReadOptions(), k, &v);
//	if (s.ok()) return true;
//	return false;
//}
//
//int Database::prop_del(string entity, uint64_t type)
//{
//	property_key(entity, type, k);
//	leveldb::Status status = db->Delete(leveldb::WriteOptions(), k);
//	if (status.ok()) return db::OK;
//	if (status.IsNotFound()) return db::IS_NOT_FOUND;
//	return db::DB_ERROR;
//}

} //namespace

