/*
 * Player.cpp
 *
 *  Created on: Mar 5, 2015
 *      Author: hongsan
 */

#include "DAO.h"
using namespace comm;


entity_ptr DAO::get_player(string uid)
{
	entity_ptr ret = boost::make_shared<model::Entity>();
	int r = db->index_get(IndexType::PLAYER, uid, *ret.get());

	/* Check if index existed */
	if (r == db::OK)
	{
		if (ret->type() != EntityType::PLAYER) throw EXCEPTION(ErrorType::ENTITY_INVALID);
		return ret;
	}
	if (r == db::IS_NOT_FOUND) throw EXCEPTION(ErrorType::ENTITY_NOT_FOUND);
	else throw EXCEPTION(ErrorType::DB_ERROR);
}

entity_ptr DAO::create_player(Player& data)
{
	/* check input */
	if (!Utils::normalize_string(*data.mutable_uid())) throw EXCEPTION(UID_INVALID);
	if (db->index_exist(IndexType::PLAYER, data.uid())) throw EXCEPTION(UID_DUPLICATED);

	/* default */
	data.set_state(Player::ACTIVE);
	data.clear_session();

	Transaction trans(db);

	/* entity */
	auto u = boost::make_shared<model::Entity>();
	u->set_type(EntityType::PLAYER);
	u->MutableExtension(Player::PLAYER)->CopyFrom(data);
	trans.en_add(*u.get());

	trans.index_set(IndexType::PLAYER, data.uid(), u->id());
	if (!trans.commit(true)) throw EXCEPTION(ErrorType::COMMIT_ERROR);
	return u;
}
