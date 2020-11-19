#include "Position.h"

Position::Position(int row, int col)
{
	this->row = row;
	(*this).col = col;
}

Position::Position(const Position & other)
{
	row = other.Row();
	col = other.Col();
}

const int Position::Row() const
{
	return row;
}

const int Position::Col() const
{
	return col;
}

const char * Position::ToString() const
{
	return (row + '0') + " " + (col + '0');
}

double Position::Distance(Position p1, Position p2)
{
	return sqrt((p2.row - p1.row)^2 + (p2.col - p1.col)^2);
}

const bool Position::operator==(const Position other)
{
	return other.row == row && other.col == col;
}

const Position operator+(const Position pos, const Position other)
{
	return Position(pos.row + other.row,pos.col + other.col);
}

const Position operator-(const Position pos, const Position other)
{
	return Position(pos.row - other.row, pos.col - other.col);
}