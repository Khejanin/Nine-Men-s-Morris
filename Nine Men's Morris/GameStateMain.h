#pragma once

#include "Game.h"

class Game;

class GameStateMain : public GameState
{

private:
	const bool CheckNotEnoughPiecesLose() const;
	const bool CheckPieceCantMoveLose() const;

public:
	GameStateMain(Game * game, GameState * next) : GameState(game, next) {};

	virtual const Position * const Turn();

	// Inherited via GameState
	virtual const bool DoesMillInThisStateChangeStrategy() const override;

	virtual const bool CheckLose(LoseCondition & cond) const override;

	// Inherited via GameState
	virtual const std::string StateMessage() const override;
};

