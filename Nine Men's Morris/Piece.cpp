#include "Piece.h"

Piece::Piece(const Piece & other)
{
	pos = other.pos;
	playerColor = other.playerColor;
}

Piece & Piece::operator=(const Piece & other)
{
	if (this == &other)
		return *this;
	playerColor = other.playerColor;
	pos = other.pos;
	return *this;
}
