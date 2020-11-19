#pragma once

#include "GameState.h"
#include "GameStatePlacing.h"
#include "GameStateMain.h"
#include "Board.h"
#include "ConsoleIOManager.h"
#include "Player.h"
#include "BoardSpaceOccupiedException.h"
#include "Position.h"
#include "LoseCondition.h"

class Game
{
	friend class GameState;
	friend class GameStatePlacing;
	friend class GameStateMain;
private:
	PlayerColor blackColor = PlayerColor(BLACK, 'B', 15);
	PlayerColor whiteColor = PlayerColor(WHITE, 'W', 240);
	Player black = Player(&blackColor);
	Player white = Player(&whiteColor);

	

	//Game
	Board board;
	GameState * gameState;
	Player * currentPlayer;
	Player * currentEnemy;

	//I/O
	IOManager * mgr;

	//INIT
	void Initialize();
	void InitializeGame();
	
	//Helper
	void CheckSelectedPiece(const Position * const selectedPiecePosition, const bool colorSameAsCurrentPlayer = true) const;

	const int CheckMills(const Position * const placedPosition) const;
	const bool CheckHorizontalMill(const Position * const targetPos) const;
	const bool CheckVerticalMill(const Position * const targetPos) const;
	const bool CheckAllPiecesInMill(const Player * const player) const;
	void CheckValidPieceForRemoval(const Position * const pos) const;

	//Game Flow
	void Turn();
	void Mill(const Position * const placedPosition);
	void NextTurn();


	//State
	void TransitionTo(GameState * state);

public:
	Game();
	~Game();
};


