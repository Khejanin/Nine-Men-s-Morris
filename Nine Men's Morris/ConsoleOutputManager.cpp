#include "ConsoleOutputManager.h"

ConsoleOutputManager::ConsoleOutputManager()
{
	ChangeColor(normalColor);
}

void ConsoleOutputManager::ShowTurn(const string player)const
{
	p.NewSegment();
	p.PrintInNewLine("It is " + player + "'s turn now!");
	p.NewLine();
}

void ConsoleOutputManager::ShowBoard(const Board & board)const
{
	p.PrintInNewLine("  1   2   3   4   5   6   7");

	for (int i = 0; i < 7; i++)
	{
		string s = board.GetStringSymbolAtPosition(i, 0) + board.GetStringSymbolAtPosition(i, 1) + board.GetStringSymbolAtPosition(i, 2);
		if(i == 3) s+= board.GetStringSymbolAtPosition(i, 3) + board.GetStringSymbolAtPosition(i, 4) + board.GetStringSymbolAtPosition(i, 5);
		bool upper = i < 3;
		if (i == 0 || i == 6) { 
			BoardDrawBig(s, upper);
			if (i == 0) BoardDrawBigConnection();
		}
		else if (i == 1 || i == 5) {
			BoardDrawMedium(s, upper);
			if (i == 1) BoardDrawMediumConnection();
			else BoardDrawBigConnection();
		}
		else if (i == 2 || i == 4) {
			BoardDrawSmall(s, upper);
			if (i == 2) BoardDrawSmallConnection();
			else BoardDrawMediumConnection();
		}
		else {
			BoardDrawMiddle(s);
			BoardDrawSmallConnection();
		}
	}
}

void ConsoleOutputManager::ShowWon(const string player)const
{
	p.NewSegment();
	p.PrintInNewLine("Congratulations " + player + "! You've won the game!");
	p.NewLine();
}

void ConsoleOutputManager::NonLegalMove() const
{
	p.PrintInNewLine("The Move you just attempted is a non-legal move!");
}

void ConsoleOutputManager::Print(const string message) const
{
	p.Print(message);
}

void ConsoleOutputManager::PrintError(const char * msg) const
{
	p.ChangeColor(errorColor);
	p.PrintInNewLine("\a");
	p.PrintInNewLine(msg);
	p.PrintInNewLine("As your turn was invalid, you will need to try again.");
	p.PrintInNewLine("");
	p.ChangeColor(normalColor);
}

void ConsoleOutputManager::PrintInNewLine(const string message) const
{
	p.PrintInNewLine(message);
}

void ConsoleOutputManager::ChangeColor(const int colorCode) const
{
	p.ChangeColor(colorCode);
}

void ConsoleOutputManager::BoardDrawBig(const string symbols, const bool upper) const
{
	string res;
	res += upper ? "a " : "g ";
	res += symbols[0];
	res += "  -  -  -  ";
	res += symbols[1];
	res += "  -  -  -  ";
	res += symbols[2];
	p.PrintInNewLine(res);
}

void ConsoleOutputManager::BoardDrawMedium(const string symbols, const bool upper) const
{
	string res;
	res += upper ? "b " : "f ";
	res += "|   ";
	res += symbols[0];
	res += "  - -  ";
	res += symbols[1];
	res += "  - -  ";
	res += symbols[2];
	res += "   |";
	p.PrintInNewLine(res);
}

void ConsoleOutputManager::BoardDrawSmall(const string symbols, const bool upper) const
{
	string res;
	res += upper ? "c " : "e ";
	res += "|   |   ";
	res += symbols[0];
	res += " - ";
	res += symbols[1];
	res += " - ";
	res += symbols[2];
	res += "   |   |";
	p.PrintInNewLine(res);
}

void ConsoleOutputManager::BoardDrawMiddle(const string symbols) const
{
	string res;
	res = "d ";
	res += symbols[0];
	res += " - ";
	res += symbols[1];
	res += " - ";
	res += symbols[2];
	res += "       ";
	res += symbols[3];
	res += " - ";
	res += symbols[4];
	res += " - ";
	res += symbols[5];
	p.PrintInNewLine(res);
}

void ConsoleOutputManager::BoardDrawBigConnection() const 
{
	p.PrintInNewLine("  |           |           |");
}

void ConsoleOutputManager::BoardDrawMediumConnection() const
{
	p.PrintInNewLine("  |   |       |       |   |");
}

void ConsoleOutputManager::BoardDrawSmallConnection() const
{
	p.PrintInNewLine("  |   |   |       |   |   |");
}
