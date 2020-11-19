#pragma once

#include "OutputManager.h"
#include "ConsolePrinter.h"

class ConsoleOutputManager : public OutputManager, Printer
{

private:
	const ConsolePrinter p;

	const int normalColor = 15;
	const int errorColor = FOREGROUND_RED;
	
	void BoardDrawBig(const string symbols,const bool upper) const;
	void BoardDrawMedium(const string symbols,const bool upper) const;
	void BoardDrawSmall(const string symbols,const bool upper) const;
	void BoardDrawMiddle(const string symbols) const;
	void BoardDrawBigConnection() const;
	void BoardDrawMediumConnection() const;
	void BoardDrawSmallConnection() const;

public:
	ConsoleOutputManager();

	virtual void ShowTurn(const string player) const;

	virtual void ShowBoard(const Board & board) const;

	virtual void ShowWon(const string player) const;

	virtual void NonLegalMove() const;

	virtual void Print(const string message) const;

	virtual void PrintError(const char * e) const;

	virtual void PrintInNewLine(const string message) const;

	void ChangeColor(const int colorCode) const;
};

