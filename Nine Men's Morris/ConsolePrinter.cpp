#include "ConsolePrinter.h"

ConsolePrinter::ConsolePrinter() : hConsole(GetStdHandle(STD_OUTPUT_HANDLE))
{
}

void ConsolePrinter::Print(const std::string message) const
{
	cout << message;
}

void ConsolePrinter::PrintInNewLine(const std::string message) const
{
	NewLine();
	cout << message;
}

void ConsolePrinter::NewLine() const
{
	cout << endl;
}

void ConsolePrinter::NewSegment() const
{
	NewLine();
	cout << "-----------------------------------------------------------------";
	NewLine();
}

void ConsolePrinter::ChangeColor(const int colorCode) const
{
	SetConsoleTextAttribute(hConsole, colorCode);
}
