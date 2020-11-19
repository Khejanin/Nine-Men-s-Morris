#include "InputToPositionConverter.h"

#include <exception>

const Position InputToPositionConverter::ConvertStringToAbsolutePosition(string pos) const
{
	string s = pos;
	int row;
	int col;
	//We check if the first one is a numeric, if it is we reverse the string. We know that the string length is only 2 characters.
	if (s[0] <= '9') reverse(s.begin(), s.end());
	if (s[0] > 'Z') row = s[0] - 'a';
	else row = s[0] - 'A';
	col = s[1] - '1';

	return Position(row, col);
}

const Position * const InputToPositionConverter::ConvertAbsolutePositionToInternalPosition(const Position & pos) const noexcept(false)
{
	if (pos.Row() >= 0 && pos.Row() <= 6 && pos.Col() >= 0 && pos.Col() <= 6) {
		int resCol;
		const invalid_argument invalidBoardPos = invalid_argument("That position does not exist on the board! Please do not use coordinates that are not occupied by a BoardSpace!");
		//You could use a strategy design pattern to change how you handle the column depending on what row you have. But that would be alot of overengineering.
		//As validation of the input goes hand in hand with the actual result there's not much incentive to seperate the two.

		//We check for 0 or 6, first or last row. Floating point errors cannot happen because our range is between 0 and 6, so comparison can safely be used.
		if (pos.Row() % 6 == 0) {
			float div = pos.Col() / 3.0f;
			float rest = div - (int)div;
			if (rest == 0) resCol = (int)div;
			else throw invalidBoardPos;
		}
		//We check for 2 or 4, third or fifth row. We do the more general resCol condition here because it would conflict with the middle row if we did it at last 
		//and each if already handles it's own condition so we only need it for this case.
		else if (pos.Row() % 2 == 0) {
			resCol = pos.Col() - 2;
			if (!(resCol >= 0 && resCol <= 2)) throw invalidBoardPos;
		}
		//We check for the middle
		else if (pos.Row() == 3) {
			if (pos.Col() == 3) throw invalidBoardPos;
			resCol = pos.Col() < 3 ? pos.Col() : pos.Col() - 1;
		}
		//The rest is the Second and Sixth row. Same as the first condition just the divisor is 2 this time.
		else {
			int help = pos.Col() - 1;
			float div = help / 2.0f;
			float rest = div - (int)div;
			if (rest == 0) resCol = (int)div;
			else throw invalidBoardPos;
		}
		return new Position(pos.Row(), resCol);
	}
	else throw invalid_argument("Your Position Arguments are out of Range! Please choose a Position between a and g, and 1 and 7!");
}

InputToPositionConverter::InputToPositionConverter(const ConsoleInputManager & iMgr) : inputSanitizer(iMgr)
{
}

const Position * const InputToPositionConverter::GetBoardPosition(const Player & p, const Board & board) const noexcept(false)
{
	const string sanitizedInput = inputSanitizer.GetPosition();
	try {
		if (sanitizedInput.length() != 2) throw invalid_argument("Your Move needs exactly two Coordinates to work!");
		const Position absPos = ConvertStringToAbsolutePosition(sanitizedInput);
		return ConvertAbsolutePositionToInternalPosition(absPos);
	}
	catch (invalid_argument e) {
		throw e;
	}
}


