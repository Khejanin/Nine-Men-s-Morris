#include "Game.h"

void Game::Initialize()
{
	//Of course this should be instantiated out of Game scope and given to game upon Construction if more implementations of the IOManager would exist.
	mgr = new ConsoleIOManager();
	board.Initialize();
	InitializeGame();
	GameStatePlacing * state = new GameStatePlacing(this,new GameStateMain(this,nullptr));
	TransitionTo(state);
	Turn();
}

void Game::InitializeGame()
{
	currentPlayer = &black;
	currentEnemy = &white;
}

void Game::Turn()
{
	LoseCondition cond;
	const bool gameEnd = gameState->CheckLose(cond);

	if (gameEnd) {
		if (currentPlayer == &black) mgr->ShowWin(white, cond);
		else mgr->ShowWin(black, cond);
		mgr->EndMessage();
		return;
	}

	bool successfulTurn = false;

	while (!successfulTurn) {
		try {
			const Position * const placedPosition = gameState->Turn();

			 Mill(placedPosition);

			 successfulTurn = true;
		}
		catch (BoardSpaceOccupiedException& e) {
			mgr->PrintException(e);
		}
		catch (invalid_argument& e) {
			mgr->PrintException(e);
		}
	}

	NextTurn();
}

//We could give all the Mill Logic to another class (maybe called "Miller"), that class would access alot of references of the Game class though, and therefore needs a reference back (and some friend declaration). Or needs them assigned to himself.
//It's handled just fine here, but for bigger architectures a code refactor could be taken into consideration.
void Game::Mill(const Position * const placedPosition)
{
	int nrOfMills = CheckMills(placedPosition);

	for (int i = 1; i <= nrOfMills; i++) {
		//Usually I wouldn't have handled the displaying of a notice here, maybe I've overseen a design solution. But I don't want to send more params to the Mill function

		bool allInMill = CheckAllPiecesInMill(currentEnemy);

		mgr->ShowMillNotice(nrOfMills,allInMill);
		try {
			const Position * const millPosition = mgr->Mill(*currentPlayer, board, i);

			CheckSelectedPiece(millPosition, false);

			if(!allInMill) CheckValidPieceForRemoval(millPosition);

			//The deletion could also take place in the Board, but this approach lets more possibilities shine.
			Piece * removedPiece = board.Remove(millPosition);

			bool changeStrat = gameState->DoesMillInThisStateChangeStrategy();

			currentEnemy->RemovePiece(removedPiece,changeStrat);

			delete removedPiece;
		}
		//The catching has to happen at this level. The catch has to be where the loop is, and I don't want the loop to be in the Turn function.
		catch (invalid_argument e) {
			mgr->PrintException(e);
			i--;
		}
	}
}

//This is just a function that throws a tantrum if you've selected something wrong.
//It's also cool to parametrically decide if you want to check for the same color or not.
void Game::CheckSelectedPiece(const Position * const selectedPiecePosition, const bool colorSameAsCurrentPlayer) const noexcept(false)
{
	if (board.IsEmpty(selectedPiecePosition)) {
		throw invalid_argument("The Place you selected is not occupied by any piece!");
	}

	//Deleting this would not be good, don't ask yourself why you wouldnt delete this again Alex.
	const PlayerColor * selectedPieceColor = board.GetPlayerColorAtPosition(selectedPiecePosition);

	/*
		We check if the selected Piece is the Player's piece, 
		then we XOR  with if we want the currentPlayer
		so the possible results are TT : 0 TF : 1 FT : 1 FF : 0
		This is by no means a readable solution but I thought it's a handy boolean operation.
	*/
	if ((selectedPieceColor == currentPlayer->playerColor) ^ colorSameAsCurrentPlayer) {
		//The wording for this can't be more explicit without a further check, it's clear enough IMO.
		throw invalid_argument("Please be sure to select a Piece of the right color!");
	}
}

const bool Game::CheckAllPiecesInMill(const Player * const player) const
{
	bool allInMill = true;
	list<Piece *> playerPieces = player->GetPiecesIterator();
	for (list<Piece*>::const_iterator iter = playerPieces.cbegin(); iter != playerPieces.cend() && allInMill; ++iter) {
		
		if(CheckMills((*iter)->pos) == 0) allInMill = false;
	}
	return allInMill;
}

void Game::CheckValidPieceForRemoval(const Position * const pos) const
{
	if (CheckMills(pos) != 0) throw invalid_argument("The piece you selected is currently in a Mill! As long as your enemy has pieces which are not in a Mill you need to remove those first!");
}

const int Game::CheckMills(const Position * const placedPosition) const
{
	return CheckHorizontalMill(placedPosition) + CheckVerticalMill(placedPosition);
}

const bool Game::CheckHorizontalMill(const Position * const targetPos) const
{
	int i = targetPos->Row();
	int j = 0;
	if (i == 3 && targetPos->Col() > 2) j = 3;
	if (board.GetPlayerColorAtPosition(i, j) == board.GetPlayerColorAtPosition(i, j + 1)
		&& board.GetPlayerColorAtPosition(i, j) == board.GetPlayerColorAtPosition(i, j + 2))
	{
		return true;
	}
	return false;
}

const bool Game::CheckVerticalMill(const Position * const targetPos) const
{
	BoardSpace * selected = board.GetBoardSpaceAt(targetPos);
	//A little trick to always use the middle piece.
	if (selected->vneighbours.size() != 2) {
		return CheckVerticalMill(selected->vneighbours[0]->pos);
	}
	else {
		return board.GetPlayerColorAtPosition(selected->pos) == board.GetPlayerColorAtPosition(selected->vneighbours[0]->pos)
			&& board.GetPlayerColorAtPosition(selected->pos) == board.GetPlayerColorAtPosition(selected->vneighbours[1]->pos);
	}
}


void Game::NextTurn()
{
	Player * help = currentPlayer;
	currentPlayer = currentEnemy;
	currentEnemy = help;
	Turn();
}



void Game::TransitionTo(GameState * state)
{
	if (gameState != nullptr) delete gameState;
	gameState = state;
}



Game::Game()
{
	Initialize();
}

Game::~Game()
{
	delete mgr;
	delete gameState;
}
