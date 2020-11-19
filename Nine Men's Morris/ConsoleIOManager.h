#pragma once

#include "IOManager.h"
#include "ConsoleInputManager.h"
#include "ConsoleOutputManager.h"
#include "InputToPositionConverter.h"
#include "GameState.h"
#include "LoseCondition.h"

class ConsoleIOManager : public IOManager
{
private:
	//Sometimes you don't only want sanitized or converted input.
	const ConsoleInputManager in;
	const ConsoleOutputManager out;
	const InputToPositionConverter posToIndex = InputToPositionConverter(in);

	void ShowBoard(const Board & board) const;
	
	void ShowPositionInputInfo() const;
	void PositionInputPrompt() const;
	void PositionInputNotice() const;

public:

	ConsoleIOManager();

	//Overrides
	virtual const Position * const Turn(const Player & p, const Board & board, const GameState * const state) const override;

	virtual const Position * const Move(const Player  &p, const Board &board) const override;

	virtual const Position * const Mill(const Player & p, const  Board & board, const int amount) const override;

	//Other
	virtual void PrintException(const std::exception e) const;

	void ShowWin(const Player & wonPlayer, const LoseCondition & winReason) const;

	void EndMessage() const;

	void ShowMillNotice(const int amount, const bool allInMillCase) const;
};

