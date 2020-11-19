#pragma once

#include "Printer.h"

class ExtendedPrinter : public Printer
{
public:
	virtual void NewLine() const = 0;

	virtual void NewSegment() const = 0;

	virtual void ChangeColor(const int colorCode) const = 0;
};

