/*
 * Index.cpp
 *
 *  Created on: Nov 13, 2012
 *      Author: nhsan
 */

#include "db/Database.h"
#include <boost/make_shared.hpp>

#define index_key(type, key, out)\
	_enc_declare_(ik, key.size()+ 32);\
	_enc_put_var32_(ik, model::INDEX);\
	_enc_put_var64_(ik, type);\
	_enc_append_key_(ik, key, key.size());\
	leveldb::Slice out(_enc_data_(ik), _enc_size_(ik));\

namespace db
{

int Database::index_set(uint64_t type, string key, string entity)
{
	index_key(type, key, k);
	model::Index index;
	index.set_type(type);
	index.set_key(key);
	index.set_entity(entity);
	string v = index.SerializeAsString();
	leveldb::Status s = db->Put(leveldb::WriteOptions(), k, v);
	if (s.ok()) return db::OK;
	return db::DB_ERROR;
}

void Transaction::index_set(uint64_t type, string key, string entity)
{
	index_key(type, key, k);
	model::Index index;
	index.set_type(type);
	index.set_key(key);
	index.set_entity(entity);
	string v = index.SerializeAsString();
	batch.Put(k,v);
}

int Database::index_get(uint64_t type, string key, model::Entity& entity)
{
	index_key(type, key, k);
	string v;
	model::Index index;
	leveldb::Status s = db->Get(leveldb::ReadOptions(), k, &v);
	if (s.ok())
	{
		if (!index.ParseFromString(v)) return db::BAD_FORMAT;
		if (en_get(index.entity(), entity) != db::OK) return db::DB_ERROR;
		return db::OK;
	}
	return db::IS_NOT_FOUND;
}

bool Database::index_exist(uint64_t type, string key)
{
	index_key(type, key, k);
	string v;
	leveldb::Status s = db->Get(leveldb::ReadOptions(), k, &v);
	if (s.ok()) return true;
	return false;
}

int Database::index_del(uint64_t type, string key)
{
	index_key(type, key, k);
	leveldb::Status status = db->Delete(leveldb::WriteOptions(), k);
	if (status.ok()) return db::OK;
	if (status.IsNotFound()) return db::IS_NOT_FOUND;
	return db::DB_ERROR;
}

void Transaction::index_del(uint64_t type, string key)
{
	index_key(type, key, k);
	batch.Delete(k);
}

index_iter_ptr Database::index_iter(uint64_t type)
{
	string empty_key;
	index_key(type, empty_key, k);
	leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
	it->Seek(k);
	index_iter_ptr ret = boost::make_shared<index_iterator>(type, it, this);
	return ret;
}

index_iter_ptr Database::index_last(uint64_t type)
{
	string last_key((char*)LAST_EV_ID, 16);
	index_key(type, last_key, k);
	leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
	it->Seek(k);
	it->Prev();
	index_iter_ptr ret = boost::make_shared<index_iterator>(type, it, this);
	return ret;
}

index_iter_ptr Database::index_seek(uint64_t type, string from)
{
	index_key(type, from, k);
	leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
	it->Seek(k);
	index_iter_ptr ret = boost::make_shared<index_iterator>(type, it, this);
	return ret;
}

string index_iterator::next()
{
	uint32_t meta;
	uint64_t type;
	string key;
	if (!it->Valid()) return string();

	_dec_declare2_(k, it->key().data(), it->key().size());
	_dec_get_var32_(k, meta);
	_dec_get_var64_(k, type);
	_dec_get_key(k, key);

	if (!_dec_valid_(k)) return string();
	if ((meta != model::INDEX) || (type != this->type)) return string();
	it->Next();
	return key;
}

entity_ptr index_iterator::next2()
{
	uint32_t meta;
	uint64_t type;
	string key;
	if (!it->Valid()) return entity_ptr();

	_dec_declare2_(k, it->key().data(), it->key().size());
	_dec_get_var32_(k, meta);
	_dec_get_var64_(k, type);
	_dec_get_key(k, key);

	if (!_dec_valid_(k)) return entity_ptr();
	if ((meta != model::INDEX) || (type != this->type)) return entity_ptr();

	model::Index index;
	if (!index.ParseFromString(it->value().ToString())) return entity_ptr();
	it->Next();
	entity_ptr ret = boost::make_shared<model::Entity>();
	if (db->en_get(index.entity(), *ret.get()) != db::OK) return entity_ptr();
	return ret;

}

entity_ptr index_iterator::prev2()
{
	uint32_t meta;
	uint64_t type;
	string key;
	if (!it->Valid()) return entity_ptr();

	_dec_declare2_(k, it->key().data(), it->key().size());
	_dec_get_var32_(k, meta);
	_dec_get_var64_(k, type);
	_dec_get_key(k, key);

	if (!_dec_valid_(k)) return entity_ptr();
	if ((meta != model::INDEX) || (type != this->type)) return entity_ptr();

	model::Index index;
	if (!index.ParseFromString(it->value().ToString())) return entity_ptr();
	it->Prev();
	entity_ptr ret = boost::make_shared<model::Entity>();
	if (db->en_get(index.entity(), *ret.get()) != db::OK) return entity_ptr();
	return ret;

}


} //namespace

