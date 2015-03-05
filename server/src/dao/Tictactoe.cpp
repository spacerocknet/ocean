/*
 * Session.cpp
 *
 *  Created on: Mar 5, 2015
 *      Author: hongsan
 */
#include "DAO.h"

entity_ptr DAO::ttt_create(string player)
{
	auto en = get_entity(player, EntityType::PLAYER);

	/* default */
	auto ret = boost::make_shared<model::Entity>();
	ret->set_type(EntityType::TICTACTOE);
	auto ttt = ret->MutableExtension(Tictactoe::TICTACTOE);
	ttt->set_player1(player);
	ttt->set_ip("127.0.0.1");
	ttt->set_state(Tictactoe::CREATED);

	for (int i = 0; i < 9; i++)
	{
		ttt->add_values(Tictactoe::E);
	}

	Transaction trans(db);
	trans.en_add(*ret.get());

	trans.index_set(IndexType::TICTACTOE, ret->id(), ret->id());
	if (!trans.commit(true)) throw EXCEPTION(comm::ErrorType::COMMIT_ERROR);
	return ret;
}

void DAO::ttt_join(string player_id, string ttt_id)
{
	auto p = get_entity(player_id, EntityType::PLAYER);
	model::Entity t;
	if (db->index_get(IndexType::TICTACTOE,ttt_id,t)!=db::OK)  throw EXCEPTION(comm::ErrorType::ENTITY_INVALID);
	/* check if player is creator */
	/* update Tictactoe data */
	/* remove Tictactoe index */
	/* make relation to players */
}

void DAO::ttt_move(string player, string session, int row, int col, int value)
{
}

void DAO::ttt_list(list<entity_ptr>& list)
{

}

