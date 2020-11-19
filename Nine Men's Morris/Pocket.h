#pragma once

#include "BoardSpace.h"

class Board;

class Pocket
{

private:

	Pocket * neighbourA, * neighbourB, * neighbourC;


public:

	Pocket(Pocket * neightbourA = nullptr, Pocket * neightbourB = nullptr, Pocket * neightbourC = nullptr);

	BoardSpace GetVerticalPartner(int index);

	friend class Board;

};

