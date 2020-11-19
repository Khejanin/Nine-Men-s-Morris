#pragma once

#include "Color.h"

class Position;

struct Piece
{
public:
	Piece(const PlayerColor * c, const Position * p = nullptr) : playerColor(c), pos(p)
	{
	}

	Piece(const Piece & other);

	Piece & operator=(const Piece &other);

	const Position * pos;
	
	const PlayerColor * playerColor;
};
