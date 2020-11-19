#include "BoardSpace.h"

BoardSpace::~BoardSpace()
{
	delete pos;
	if (piece != nullptr) delete piece;
}

const char BoardSpace::GetSymbol() const
{
	if (piece != nullptr) return piece->playerColor->symbol;
	else return 'X';
}

bool BoardSpace::isBlocked()
{
	bool blocked = true;
	for (size_t i = 0; i < vneighbours.size() && blocked; i++) {
		if (vneighbours[i]->piece == nullptr) blocked = false;
	}
	for (size_t i = 0; i < hneighbours.size() && blocked; i++) {
		if (hneighbours[i]->piece == nullptr) blocked = false;
	}

	return blocked;
}
