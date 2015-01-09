/*
 * Relation.cpp
 *
 *  Created on: Nov 13, 2012
 *      Author: nhsan
 */

#include "db/Database.h"
#include "leveldb/write_batch.h"
#include <boost/make_shared.hpp>

#define rel_key(e1, type, e2, slice, rk)\
	_enc_declare_(rk, 64);\
	_enc_put_var32_(rk, model::RELATION);\
	_enc_put_string_(rk, e1);\
	_enc_put_var64_(rk, type);\
	_enc_append_key_(rk, e2.c_str(), e2.size());\
	leveldb::Slice slice(_enc_data_(rk), _enc_size_(rk));

namespace db
{

int Database::rel_put(string e1, uint64_t type, string e2)
{
	rel_key(e1, type, e2, k, rk);
	leveldb::Slice v;
	leveldb::Status s = db->Put(leveldb::WriteOptions(), k, v);
	if (s.ok()) return db::OK;
	return db::DB_ERROR;
}

void Transaction::rel_put(string e1, uint64_t type, string e2)
{
	rel_key(e1, type, e2, k, rk);
	leveldb::Slice v;
	batch.Put(k, v);
}

int Database::rel_put(string e1, uint64_t type, string e2, model::Relation& relation)
{
	rel_key(e1, type, e2, k, rk);
	string v = relation.SerializeAsString();
	leveldb::Status s = db->Put(leveldb::WriteOptions(), k, v);
	if (s.ok()) return db::OK;
	return db::DB_ERROR;
}

void Transaction::rel_put(string e1, uint64_t type, string e2, model::Relation& relation)
{
	rel_key(e1, type, e2, k, rk);
	string v = relation.SerializeAsString();
	batch.Put(k,v);
}

int Database::rel_get(string e1, uint64_t type, string e2, model::Relation& relation)
{
	rel_key(e1, type, e2, k, rk);
	string v;

	leveldb::Status s = db->Get(leveldb::ReadOptions(), k, &v);
	if (s.ok())
	{
		if (!relation.ParseFromString(v)) return db::BAD_FORMAT;
		return db::OK;
	}
	return db::IS_NOT_FOUND;
}

bool Database::rel_exist(string e1, uint64_t type, string e2)
{
	rel_key(e1, type, e2, k, rk);
	string v;

	leveldb::Status s = db->Get(leveldb::ReadOptions(), k, &v);
	if (s.ok()) return true;
	return false;
}

int Database::rel_del(string e1, uint64_t type, string e2)
{
	rel_key(e1, type, e2, k, rk);
	leveldb::Status s = db->Delete(leveldb::WriteOptions(), k);
	if (s.ok()) return db::OK;
	if (s.IsNotFound()) return db::IS_NOT_FOUND;
	return db::DB_ERROR;
}

void Transaction::rel_del(string e1, uint64_t type, string e2)
{
	rel_key(e1, type, e2, k, rk);
	batch.Delete(k);
}

rel_iter_ptr Database::rel_iter(string entity, uint64_t type)
{
	string empty_key;
	rel_key(entity, type, empty_key, k, rk);
	leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
	it->Seek(k);
	rel_iter_ptr ret = boost::make_shared<rel_iterator>(entity, type, it, this);
	return ret;
}

rel_iter_ptr Database::rel_seek(string entity, uint64_t type, string from )
{
	rel_key(entity, type, from, k, rk);
	leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
	it->Seek(k);
	rel_iter_ptr ret = boost::make_shared<rel_iterator>(entity, type, it, this);
	return ret;
}

string rel_iterator::next()
{
	uint32_t meta;
	string source;
	uint64_t type;
	string target;

	if (!it->Valid()) return string();
	_dec_declare2_(k, it->key().data(), it->key().size());
	_dec_get_var32_(k, meta);
	_dec_get_string_(k, source);
	_dec_get_var64_(k, type);
	_dec_get_key(k, target);

	if (!_dec_valid_(k)) return string();
	if ((meta != model::RELATION) || (source != eid) || (type != this->type)) return string();
	it->Next();
	return target;
}

entity_ptr rel_iterator::next2()
{
	string target = next();
	if (target == "") return entity_ptr();
	entity_ptr ret = boost::make_shared<model::Entity>();
	int r = db->en_get(target, *ret.get());
	if (r == db::OK) return ret;
	return entity_ptr();
}

} //namespace

