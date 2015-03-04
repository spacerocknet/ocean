/*
 * DAO.cpp
 *
 *  Created on: Aug 8, 2013
 *      Author: nhsan
 */

#include "DAO.h"

DAO::DAO(Database* db) :
		Component(DAO_COMP), db(db)
{
}

DAO::~DAO()
{
}

Database* DAO::get_db()
{
	return db;
}

entity_ptr DAO::get_entity(string id, uint32_t type)
{
	entity_ptr ret = boost::make_shared<model::Entity>();
	int r = db->en_get(id, *ret.get());

	if (r == db::OK)
	{
		if (ret->type() != type) throw EXCEPTION(comm::ErrorType::ENTITY_INVALID);
		return ret;
	}

	if (r == db::IS_NOT_FOUND) throw EXCEPTION(comm::ErrorType::ENTITY_NOT_FOUND);
	else throw EXCEPTION(DB_ERROR);
}
