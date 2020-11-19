#pragma once

#include "Board.h"
#include "Printer.h"
#include <string>

using namespace std;

class OutputManager
{

public:

	virtual void ShowTurn(const string player) const = 0;

	virtual void ShowBoard(const Board & board) const = 0;

	virtual void ShowWon(const string player) const = 0;

	virtual void NonLegalMove() const = 0;

	virtual void Print(const string message) const = 0;

	virtual void PrintError(const char * e) const = 0;

	virtual void ChangeColor(const int colorCode) const = 0;

};

