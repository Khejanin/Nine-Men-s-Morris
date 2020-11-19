#pragma once

#include "ExtendedPrinter.h"
#include <iostream>
#include <windows.h>

using namespace std;

class ConsolePrinter : public ExtendedPrinter
{
private:
	const HANDLE hConsole;
public:

	ConsolePrinter();

	virtual void Print(const std::string message) const;

	virtual void PrintInNewLine(const std::string message) const;

	virtual void NewLine() const;

	virtual void NewSegment() const;
	 
	virtual void ChangeColor(const int colorCode) const;
};

