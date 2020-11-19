#pragma once

#include <string>
#include <list>
#include "Piece.h"
#include "PlayerStrategy.h"
#include "MovingPlayerStrategy.h"
#include "JumpingPlayerStrategy.h"

using namespace std;

class Player : public PlayerStrategy
{
private:
	PlayerStrategy * strategy;
	//Pieces were counted initially, that would save some space (int value instead of multiple pointers)
	//But the convenience of accessing them for lose checks is too good to pass up
	//int nrOfPieces = 0;

	list<Piece *> piecesList;

public:
	const PlayerColor * playerColor;
	string name;

	Player(PlayerColor * c);
	~Player();

	virtual const bool ValidateMove(const Board & board, const Position * const start, const Position * const dest) const override;

	virtual const std::string Message() const override;

	void AddPiece(Piece * piece);
	void RemovePiece(Piece * piece,bool placing);

	list<Piece *> GetPiecesIterator() const;
	const bool HasNotEnoughPieces() const;

};

