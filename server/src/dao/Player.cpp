/*
 * Player.cpp
 *
 *  Created on: Mar 5, 2015
 *      Author: hongsan
 */

#include "DAO.h"

entity_ptr DAO::get_player(string id)
{
	auto ret = boost::make_shared<model::Entity>();
	int r = db->en_get(id, *ret.get());

	/* Check if index existed */
	if (r == db::OK)
	{
		if (ret->type() != EntityType::PLAYER) throw EXCEPTION(comm::ErrorType::ENTITY_INVALID);
		return ret;
	}
	if (r == db::IS_NOT_FOUND) throw EXCEPTION(comm::ErrorType::ENTITY_NOT_FOUND);
	else throw EXCEPTION(DB_ERROR);

}

entity_ptr DAO::get_player_by_uid(string uid)
{
	entity_ptr ret = boost::make_shared<model::Entity>();
	int r = db->index_get(IndexType::PLAYER, uid, *ret.get());

	/* Check if index existed */
	if (r == db::OK)
	{
		if (ret->type() != EntityType::PLAYER) throw EXCEPTION(comm::ErrorType::ENTITY_INVALID);
		return ret;
	}
	if (r == db::IS_NOT_FOUND) throw EXCEPTION(comm::ErrorType::ENTITY_NOT_FOUND);
	else throw EXCEPTION(DB_ERROR);
}

entity_ptr DAO::create_player(Player& data)
{

}
