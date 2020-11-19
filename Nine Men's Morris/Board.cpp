#include "Board.h"
#include "Position.h"
#include <vector>
#include "BoardSpaceOccupiedException.h"

using namespace std;

//Initialization

void Board::InstantiateBoardSpaces()
{
	for (int i = 0; i < 7; i++)
	{
		if (i != 3) board[i] = new BoardSpace[3];
		else board[i] = new BoardSpace[6];
	}
}

void Board::InstantiateBoardSpacesWithPositions()
{
	for (int i = 0; i < 7; i++)
	{
		if (i != 3) {
			board[i] = new BoardSpace[3];
			for (int j = 0; j < 3; j++)
			{
				board[i][j].pos = new Position(i, j);
			}
		}
		else {
			board[i] = new BoardSpace[6];
			for (int j = 0; j < 6; j++)
			{
				board[i][j].pos = new Position(i, j);
			}
		}
	}
}

void Board::LinkBoardSpaces()
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			LinkBoardSpacesHorizontal(i, j);
			//The reason we only add the vertical neighbors and the horizontal neighbours gives me the possibility to show how the data structure can be used for Horizontal operations.
			LinkBoardSpacesVertical(i, j);
		}
	}
}

void Board::LinkBoardSpacesVertical(const int i,const int j)
{
	if (i != 3) {
		//Adds the vertical connections between everything that doesnt connect to D
		if (j == 1) {
			//Upper/Lower check to make it fit into the modulo 3. 0 is for when you only connect DOWN, 1 is for when you connect BOTH WAYS and 2 is if you only connect UP.
			int n = i;
			if (n > 3) n--;
			int help = n % 3;

			//These logic checks satisfy that 1 gets both connections.
			if (help != 0) board[i][j].vneighbours.push_back(&board[i - 1][j]); //We go down because we have either 1 or 2
			if (help != 2) board[i][j].vneighbours.push_back(&board[i + 1][j]); //We go up because we have either 0 or 1
		}

		//Adds the vertical Connections to the Row D of the board and vice versa
		if (i < 3) {
			//This is for the upper half, it goes down connecting to D
			if (j == 0) {
				board[i][j].vneighbours.push_back(&board[3][i]); //TO D
				board[3][i].vneighbours.push_back(&board[i][j]); //FROM D
			}
			if (j == 2) {
				board[i][j].vneighbours.push_back(&board[3][5 - i]); //TO D
				board[3][5 - i].vneighbours.push_back(&board[i][j]); //FROM D
			}
		}
		else {
			//This is for the lower half, it goes up connecting to D
			if (j == 0) {
				board[i][j].vneighbours.push_back(&board[3][6 - i]); //TO D
				board[3][6 - i].vneighbours.push_back(&board[i][j]); //FROM D
			}
			if (j == 2) {
				board[i][j].vneighbours.push_back(&board[3][i - 1]); //TO D
				board[3][i - 1].vneighbours.push_back(&board[i][j]); //FROM D
			}
		}
	}
}

void Board::LinkBoardSpacesHorizontal(const int i, const int j)
{
	//Adds 1 to 2 neighbours depending on horizontal placement this deals with ALL horizontal neighbours
	if (j < 2) board[i][j].hneighbours.push_back(&board[i][j + 1]);
	if (j > 0) board[i][j].hneighbours.push_back(&board[i][j - 1]);
}

void Board::Initialize()
{
	InstantiateBoardSpacesWithPositions();
	LinkBoardSpaces();
}

const bool Board::AreNeighbours(const Position * const  pos1, const Position * const pos2) const
{
	bool res = false;
	BoardSpace * boardSpace = &board[pos1->Row()][pos1->Col()];
	std::vector<BoardSpace *> neigh = board[pos2->Row()][pos2->Col()].vneighbours;

	for (size_t i = 0; i < neigh.size() && !res; i++)
	{
		if (boardSpace == neigh[i]) res = true;
	}

	//Special check without using hneightbours because I like to show both approaches, this is for horizontal
	if (!res) {
		//The addition check ONLY works because of the check beforehand and because of the board properties.
		if (pos1->Row() == pos2->Row() && abs(pos1->Col() - pos2->Col()) == 1 && pos1->Col() + pos2->Col() != 5) res = true;
	}

	return res;
}

//This handles that the pieces always point to the right position
void Board::Place(const Position * const pos, Piece * const piece)
{
	board[pos->Row()][pos->Col()].piece = piece;
	piece->pos = pos;
}

Board::~Board()
{
	for (int i = 0; i < 7; i++) {
		delete[] board[i];
	}
	delete[] board;
}

Piece * Board::PlaceNew(const Position * const pos, const PlayerColor * const color) noexcept(false)
{
	if (!IsOccupied(pos)) {
		Piece * res = new Piece(color);
		Place(pos, res);
		return res;
	}
	else throw BoardSpaceOccupiedException();
}

void Board::Move(const Position * const start, const Position * const dest)
{
	if (!IsOccupied(dest)) {
		Place(dest, Remove(start));
	}
	else throw BoardSpaceOccupiedException();
}

Piece * const Board::Remove(const Position * const pos)
{
	Piece * const targetPiece = board[pos->Row()][pos->Col()].piece;
	board[pos->Row()][pos->Col()].piece = nullptr;
	return targetPiece;
}
 
BoardSpace * Board::GetBoardSpaceAt(const Position * const pos) const
{
	return &(board[pos->Row()][pos->Col()]);
}

const bool Board::IsEmpty(const Position * const pos) const
{
	return board[pos->Row()][pos->Col()].piece == nullptr;
}

bool Board::IsOccupied(const Position * const pos) const
{
	return board[pos->Row()][pos->Col()].piece != nullptr;
}

const char Board::GetSymbolAtPosition(const int x,const int y) const
{
	return board[x][y].GetSymbol();
}

const string Board::GetStringSymbolAtPosition(const int x, const int y) const
{
	string s;
	s += GetSymbolAtPosition(x,y);
	return s;
}

const char Board::GetSymbolAtPosition(Position pos) const
{
	return GetSymbolAtPosition(pos.Row(), pos.Col());
}

const string Board::GetStringSymbolAtPosition(Position pos) const
{
	return GetStringSymbolAtPosition(pos.Row(), pos.Col());
}

const PlayerColor * Board::GetPlayerColorAtPosition(const Position * const pos) const
{
	return GetPlayerColorAtPosition(pos->Row(), pos->Col());
}

const PlayerColor * Board::GetPlayerColorAtPosition(const int x, const int y) const
{
	Piece * piece = board[x][y].piece;
	if (piece == nullptr) return nullptr;
	return (*piece).playerColor;
}

BoardSpace ** Board::GetBoard()
{
	return board;
}