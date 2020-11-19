#include "GameStateMain.h"

const Position * const  GameStateMain::Turn() noexcept(false)
{
	const Position * const selectedPiecePosition = game->mgr->Turn(*(game->currentPlayer), game->board, this);

	game->CheckSelectedPiece(selectedPiecePosition);

	const Position * const targetPosition = game->mgr->Move(*(game->currentPlayer), game->board);

	if (!game->currentPlayer->ValidateMove(game->board,selectedPiecePosition, targetPosition)) {
		throw invalid_argument("The move you specified is invalid! Please remember that you can only move by steps of one!");
	}

	game->board.Move(selectedPiecePosition, targetPosition);
	delete selectedPiecePosition;
	return targetPosition;
}

const bool GameStateMain::DoesMillInThisStateChangeStrategy() const
{
	return true;
}

const bool GameStateMain::CheckLose(LoseCondition & cond) const
{
	bool res = false;
	if (res = CheckNotEnoughPiecesLose()) cond = NOTENOUGHPIECES;
	else if (res = CheckPieceCantMoveLose()) cond = PIECESCANTMOVE;
	return res;
}

const std::string GameStateMain::StateMessage() const
{
	return "You are currently in the MAIN Game state, please first select your piece of choice";
}

const bool GameStateMain::CheckNotEnoughPiecesLose() const
{
	return game->currentPlayer->HasNotEnoughPieces();
}

//Of course the player could just store the Board Spaces that he occupies, then this would've been easier, but I prefer the pieces approach.
const bool GameStateMain::CheckPieceCantMoveLose() const
{
	list<Piece *> playerPieces = game->currentPlayer->GetPiecesIterator();
	for (list<Piece*>::const_iterator iter = playerPieces.cbegin(); iter != playerPieces.cend(); ++iter) {
		if (!game->board.GetBoardSpaceAt((*iter)->pos)->isBlocked()) return false;
	}
	return true;
}
