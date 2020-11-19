#pragma once

#include <math.h>
#include <string>

using namespace std;

class Position
{
private:

	int row,col;

public:
	
	Position(int row, int col);
	Position(const Position & other);

	const int Row() const;
	const int Col() const;

	const char * ToString() const;

	static double Distance(Position p1, Position p2);

	const bool operator==(const Position other);

	friend const Position operator+(const Position pos, const Position other);
	friend const Position operator-(const Position pos, const Position other);

};

const Position operator+(const Position pos, const Position other);
const Position operator-(const Position pos, const Position other);
