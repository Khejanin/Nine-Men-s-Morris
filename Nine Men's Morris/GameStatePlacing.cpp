#include "GameStatePlacing.h"

const Position * const GameStatePlacing::Turn() noexcept(false)
{
	const Position * const placingPosition = game->mgr->Turn(*(game->currentPlayer), game->board, this);
	Piece * placedPiece = game->board.PlaceNew(placingPosition, game->currentPlayer->playerColor);
	game->currentPlayer->AddPiece(placedPiece);
	round++;
	if (round > placingRounds) {
		game->TransitionTo(next);
	}
	return placingPosition;
}

const bool GameStatePlacing::DoesMillInThisStateChangeStrategy() const
{
	return false;
}

const bool GameStatePlacing::CheckLose(LoseCondition & cond) const
{
	return false;
}

const std::string GameStatePlacing::StateMessage() const
{
	return "You are currently in PLACING state, what coordinates would you like to place your piece ?";
}
