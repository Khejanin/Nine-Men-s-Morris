#pragma once

#include "PlayerStrategy.h"

class JumpingPlayerStrategy : public PlayerStrategy
{
public:

	virtual const bool ValidateMove(const Board & board, const Position * const start, const Position * const dest) const override;
	virtual const std::string Message() const override;
};

