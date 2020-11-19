#include "JumpingPlayerStrategy.h"

const bool JumpingPlayerStrategy::ValidateMove(const Board & board, const Position * const start, const Position * const dest) const
{
	return true;
}

const std::string JumpingPlayerStrategy::Message() const
{
	return "Because you only have three pieces left, you can jump to any space of the Board!";
}
