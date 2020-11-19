#include "ConsoleIOManager.h"

void ConsoleIOManager::ShowBoard(const Board &board) const
{
	out.PrintInNewLine("Current Board State :");
	out.ShowBoard(board);
}

void ConsoleIOManager::ShowPositionInputInfo() const
{
	PositionInputNotice();
	PositionInputPrompt();
}

void ConsoleIOManager::PositionInputNotice() const
{
	out.PrintInNewLine("Note: Use the board coordinates to input your choice! Example : D3, spaces will be ignored but if you have more than 2 characters your input will be invalid!");
}

void ConsoleIOManager::ShowMillNotice(const int amount, const bool specialCase) const
{
	out.PrintInNewLine("You have successfully formed " + to_string(amount) + " mills!");
	out.PrintInNewLine("You can now choose " + to_string(amount) + " distinct enemy pieces that you want to destroy!");

	if(specialCase) out.PrintInNewLine("Due to all of your opponent's pieces being in a Mill, you are allowed to take any piece you want.");
	else out.PrintInNewLine("Note: You can only remove enemy pieces that are not in a mill!");
}

void ConsoleIOManager::PositionInputPrompt() const
{
	out.PrintInNewLine("");
	out.Print("Pawn Coordinates : ");
}

ConsoleIOManager::ConsoleIOManager()
{
}

const Position * const ConsoleIOManager::Turn(const Player  &p, const Board &board, const GameState * const state) const noexcept(false)
{
	out.ChangeColor(p.playerColor->consoleColorCode);
	out.ShowTurn(p.name);

	ShowBoard(board);

	out.PrintInNewLine(state->StateMessage());
	
	ShowPositionInputInfo();
	
	const Position * const pos = posToIndex.GetBoardPosition(p, board);
	return pos;
}

const Position * const ConsoleIOManager::Move(const Player  &p, const Board & board) const
{
	out.PrintInNewLine("\n" + p.Message() + "\n");
	const Position * const targetPos = posToIndex.GetBoardPosition(p, board);
	return targetPos;
}

void ConsoleIOManager::PrintException(const std::exception e) const
{
	out.PrintError(e.what());
}
const Position * const ConsoleIOManager::Mill(const Player & p,const Board & board,const int millIndex) const
{
	out.ChangeColor(p.playerColor->consoleColorCode);
	ShowBoard(board);
	out.PrintInNewLine("Select Piece Number " + to_string(millIndex) + " that you want to destroy :");
	out.PrintInNewLine("");
	return posToIndex.GetBoardPosition(p, board);
}

void ConsoleIOManager::ShowWin(const Player & wonPlayer, const LoseCondition & winReason) const
{
	out.PrintInNewLine("");
	string reason;
	if (winReason == NOTENOUGHPIECES) reason = "taking all your opponent's pieces until only 2 were left!";
	else reason = "leaving your opponent with no legal moves!";
	out.PrintInNewLine("CONGRATULATIONS " + wonPlayer.name + " you've won the game by " + reason);
}

void ConsoleIOManager::EndMessage() const
{
	out.PrintInNewLine("The program ends now, if you want to play again you must start the program again!");
}

