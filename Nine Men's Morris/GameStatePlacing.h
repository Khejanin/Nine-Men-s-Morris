#pragma once



#ifndef gamestatemain_h
#define gamestatemain_h
#include "GameStateMain.h"
#endif

class GameStatePlacing : public GameState
{
private:
	const int placingRounds = 18;
	int round = 1;
public:
	GameStatePlacing(Game * game, GameState * next) : GameState(game, next) {};

	const Position * const Turn();

	// Inherited via GameState
	virtual const bool DoesMillInThisStateChangeStrategy() const override;


	// Inherited via GameState
	virtual const bool CheckLose(LoseCondition & cond) const;


	// Inherited via GameState
	virtual const std::string StateMessage() const override;

};

