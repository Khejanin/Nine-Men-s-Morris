#pragma once

#include "ConsoleInputManager.h"
#include "Player.h"
#include "Board.h"

class InputSanitizerProxy : public InputManager
{
private:
	const ConsoleInputManager iMgr;

	const string SanitizeInput(const string in) const;

	const string GetSanitizedBoardInput() const;

public:
	InputSanitizerProxy(const ConsoleInputManager & ioManager);

	// Inherited via InputManager
	virtual const string GetPosition() const override;
};