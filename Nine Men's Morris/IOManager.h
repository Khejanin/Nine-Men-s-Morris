#pragma once

#include "Position.h"
#include "Player.h"
#include "Board.h"
#include "LoseCondition.h"

class GameState;

class IOManager
{
public:
	virtual const Position * const Turn(const Player & p, const Board &board, const GameState * const state) const = 0;

	virtual const Position * const Move(const Player & p, const Board &board) const = 0;

	virtual const Position * const Mill(const Player & p, const Board & board, const int amount) const = 0;

	virtual void PrintException(const std::exception e) const = 0;

	virtual void ShowWin(const Player & wonPlayer, const LoseCondition & winReason) const = 0;

	virtual void EndMessage() const = 0;

	virtual void ShowMillNotice(const int amount, const bool allInMillCase) const = 0;

};

