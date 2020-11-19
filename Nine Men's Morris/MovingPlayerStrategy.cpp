#include "MovingPlayerStrategy.h"


const bool MovingPlayerStrategy::ValidateMove(const Board & board, const Position * const start, const Position * const dest) const
{
	return board.AreNeighbours(start, dest);
}

const std::string MovingPlayerStrategy::Message() const
{
	return "You may only move your pieces to adjacent (and empty) places!";
}
