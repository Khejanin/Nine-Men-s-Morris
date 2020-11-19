#pragma once

#include <string>

class Printer
{
public:
	virtual void Print(const std::string message) const = 0;

	virtual void PrintInNewLine(const std::string message) const = 0;
};

