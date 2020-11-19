#include "Player.h"

Player::Player(PlayerColor * c) : playerColor(c)
{
	if (c->color == BLACK) {
		name = "Black";
	}
	else name = "White";
	strategy = new MovingPlayerStrategy();
}

Player::~Player()
{
	delete strategy;
}

const bool Player::ValidateMove(const Board & board, const Position * const  start, const Position * const dest) const
{
	return strategy->ValidateMove(board,start, dest);
}

const std::string Player::Message() const
{
	return strategy->Message();
}

void Player::AddPiece(Piece * piece)
{
	piecesList.push_back(piece);
}

void Player::RemovePiece(Piece * piece,const bool changeStrat)
{
	piecesList.remove(piece);
	if (changeStrat && piecesList.size() == 3) {
		delete strategy;
		strategy = new JumpingPlayerStrategy();
	}
}

list<Piece*> Player::GetPiecesIterator() const
{
	return piecesList;
}


const bool Player::HasNotEnoughPieces() const
{
	return piecesList.size() < 3;
}

