#pragma once

#include <string>
#include "Position.h"

using namespace std;

class InputManager
{

public:
	virtual const string GetPosition() const = 0;
};

