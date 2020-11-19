#pragma once

#include "InputSanitizerProxy.h"
#include "ConsoleInputManager.h"
#include "Player.h"
#include "Board.h"

class InputToPositionConverter
{

private:
	const InputSanitizerProxy inputSanitizer;

	const Position ConvertStringToAbsolutePosition(const string pos) const;
	const Position * const ConvertAbsolutePositionToInternalPosition(const Position & pos) const;

public:
	InputToPositionConverter(const ConsoleInputManager & iMgr);

	const Position * const GetBoardPosition(const Player & p, const Board & board) const;
};

