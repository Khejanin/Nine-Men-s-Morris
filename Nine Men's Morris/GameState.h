#pragma once

#include <string>
#include "Position.h"

class Game;
enum LoseCondition;

class GameState
{
protected:
	Game * game;
	GameState * next;
public:

	GameState(Game * g, GameState * n) : game(g), next(n) {};

	~GameState();

	virtual const Position * const Turn() = 0;

	virtual const std::string StateMessage() const = 0;

	virtual const bool DoesMillInThisStateChangeStrategy() const = 0;

	virtual const bool CheckLose(LoseCondition & cond) const = 0;

};

