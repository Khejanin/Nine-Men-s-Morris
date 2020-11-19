#pragma once

#include <vector>
#include <string>
#include "Piece.h"
#include "Position.h"

using namespace std;

class BoardSpace
{

public:
	//OLD
	//BoardSpace * neighbours;

	BoardSpace() { piece = nullptr; pos = nullptr; }
	~BoardSpace();


	std::vector<BoardSpace*> vneighbours;
	std::vector<BoardSpace*> hneighbours;

	Piece * piece;

	const char GetSymbol() const;

	Position * pos;

	bool isBlocked();
};

