#pragma once

#include <string>
#include "Position.h"
class Board;
class Position;

class PlayerStrategy {

public:

	virtual const bool ValidateMove(const Board & board, const Position * const start, const Position * const dest) const = 0;

	virtual const std::string Message() const = 0;

};