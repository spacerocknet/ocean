/*
 * Activity.cpp
 *
 *  Created on: Nov 13, 2012
 *      Author: nhsan
 */

#include "db/Database.h"
#include "leveldb/write_batch.h"
#include <boost/make_shared.hpp>

#define act_key(entity, type, event, slice)\
	_enc_declare_(ak, 64);\
	_enc_put_var32_(ak, model::ACTIVITY);\
	_enc_put_string_(ak, entity);\
	_enc_put_var64_(ak, type);\
	_enc_append_key_(ak, event.c_str(), event.size());\
	leveldb::Slice slice(_enc_data_(ak), _enc_size_(ak));

namespace db
{

int Database::act_put(string entity, uint64_t type, string event)
{
	act_key(entity, type, event, k);
	leveldb::Slice v;
	leveldb::Status s = db->Put(leveldb::WriteOptions(), k, v);
	if (s.ok()) return db::OK;
	return db::DB_ERROR;
}

void Transaction::act_put(string entity, uint64_t type, string event)
{
	act_key(entity, type, event, k);
	leveldb::Slice v;
	batch.Put(k,v);
}

bool Database::act_exist(string entity, uint64_t type, string event)
{
	act_key(entity, type, event, k);
	string v;

	leveldb::Status s = db->Get(leveldb::ReadOptions(), k, &v);
	if (s.ok()) return true;
	return false;
}

int Database::act_del(string entity, uint64_t type, string event)
{
	act_key(entity, type, event, k);
	leveldb::Status status = db->Delete(leveldb::WriteOptions(), k);
	if (status.ok()) return db::OK;
	if (status.IsNotFound()) return db::IS_NOT_FOUND;
	return db::DB_ERROR;
}

void Transaction::act_del(string entity, uint64_t type, string event)
{
	act_key(entity, type, event, k);
	batch.Delete(k);
}

act_iter_ptr Database::act_first(string entity, uint64_t type)
{
	_enc_declare_(ak, 64);
	_enc_put_var32_(ak, model::ACTIVITY);
	_enc_put_string_(ak, entity);
	_enc_put_var64_(ak, type);
	leveldb::Slice k(_enc_data_(ak), _enc_size_(ak));
	leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
	it->Seek(k);
	act_iter_ptr ret = boost::make_shared<act_iterator>(entity, type, it, this);
	return ret;
}

act_iter_ptr Database::act_last(string entity, uint64_t type)
{
	_enc_declare_(ak, 64);
	_enc_put_var32_(ak, model::ACTIVITY);
	_enc_put_string_(ak, entity);
	_enc_put_var64_(ak, type);
	_enc_append_key_(ak, LAST_EV_ID, 16);
	leveldb::Slice k(_enc_data_(ak), _enc_size_(ak));
	leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
	it->Seek(k);
	it->Prev();
	act_iter_ptr ret = boost::make_shared<act_iterator>(entity, type, it, this);
	return ret;
}

act_iter_ptr Database::act_seek(string entity, uint64_t type, string from)
{
	_enc_declare_(ak, 64);
	_enc_put_var32_(ak, model::ACTIVITY);
	_enc_put_string_(ak, entity);
	_enc_put_var64_(ak, type);
	_enc_append_key_(ak, from, 16);
	leveldb::Slice k(_enc_data_(ak), _enc_size_(ak));
	leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
	it->Seek(k);
	act_iter_ptr ret = boost::make_shared<act_iterator>(entity, type, it, this);
	return ret;
}

string act_iterator::next()
{
	uint32_t meta;
	string entity;
	uint64_t type;
	string event;
	if (!it->Valid()) return string();

	_dec_declare2_(k, it->key().data(), it->key().size());
	_dec_get_var32_(k, meta);
	_dec_get_string_(k, entity);
	_dec_get_var64_(k, type);
	_dec_get_key(k, event);

	if (!_dec_valid_(k)) return string();
	if ((meta != model::ACTIVITY) || (entity != eid) || (type != this->type)) return string();
	it->Next();
	return event;
}

string act_iterator::prev()
{
	uint32_t meta;
	string entity;
	uint64_t type;
	string event;
	if (!it->Valid()) return string();

	_dec_declare2_(k, it->key().data(), it->key().size());
	_dec_get_var32_(k, meta);
	_dec_get_string_(k, entity);
	_dec_get_var64_(k, type);
	_dec_get_key(k, event);

	if (!_dec_valid_(k)) return string();
	if ((meta != model::ACTIVITY) || (entity != eid) || (type != this->type)) return string();
	it->Prev();
	return event;
}

event_ptr act_iterator::next2()
{
	string event = next();
	if (event.empty()) return event_ptr();
	event_ptr ret = boost::make_shared<model::Event>();
	int r = db->ev_get(event, *ret.get());
	if (r == db::OK) return ret;
	return event_ptr();
}

event_ptr act_iterator::prev2()
{
	string event = prev();
	if (event.empty()) return event_ptr();
	event_ptr ret = boost::make_shared<model::Event>();
	int r = db->ev_get(event, *ret.get());
	if (r == db::OK) return ret;
	return event_ptr();
}

} //namespace

