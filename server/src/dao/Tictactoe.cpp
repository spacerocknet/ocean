/*
 * Session.cpp
 *
 *  Created on: Mar 5, 2015
 *      Author: hongsan
 */
#include "DAO.h"

entity_ptr DAO::ttt_create(string player_id)
{
	auto en = get_entity(player_id, EntityType::PLAYER);

	/* default */
	auto ret = boost::make_shared<model::Entity>();
	ret->set_type(EntityType::TICTACTOE);
	auto ttt = ret->MutableExtension(Tictactoe::TICTACTOE);
	ttt->set_player1(player_id);
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
	auto player = get_entity(player_id, EntityType::PLAYER);
	model::Entity ttt;

	if (db->index_get(IndexType::TICTACTOE, ttt_id, ttt) != db::OK) throw EXCEPTION(comm::ErrorType::ENTITY_INVALID);
	auto p = player->GetExtension(Player::PLAYER);
	auto t = ttt.MutableExtension(Tictactoe::TICTACTOE);

	/* check if player is creator */
	if (t->player1() == player_id) throw EXCEPTION(comm::ErrorType::INVALID_PLAYER);
	/* update Tictactoe data */
	t->set_player2(player_id);
	t->set_state(Tictactoe::STARTED);

	Transaction trans(db);
	trans.en_update(ttt);

	/* remove Tictactoe index */
	trans.index_del(IndexType::TICTACTOE, ttt_id);
	/* make relation to players */
	trans.rel_put(t->player1(), RelationType::HAS_TICTACTOE, ttt_id);
	trans.rel_put(t->player2(), RelationType::HAS_TICTACTOE, ttt_id);
	if (!trans.commit(true)) throw EXCEPTION(comm::ErrorType::COMMIT_ERROR);
}

void DAO::ttt_move(string player_id, string session, int row, int col, int value)
{
	/*TODO: TICTACTOE game logic here*/
}

void DAO::ttt_list(list<entity_ptr>& list)
{
	auto iter = db->index_iter(IndexType::TICTACTOE);
	entity_ptr entity;
	while ((entity = iter->next2()) != nullptr)
	{
		list.push_back(entity);
	}
}
