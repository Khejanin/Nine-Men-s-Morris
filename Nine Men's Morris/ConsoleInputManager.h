#pragma once

#include "InputManager.h"

class ConsoleInputManager : public InputManager
{
public:
	virtual const string GetPosition() const;
};

