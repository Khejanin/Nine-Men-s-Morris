#pragma once

using namespace std;

enum Color {
	WHITE,
	BLACK
};

struct PlayerColor {

	PlayerColor(Color const c, char const s, int const colorCode) : color(c), symbol(s), consoleColorCode(colorCode)
	{
	}

	Color const color;
	char const symbol;
	int const consoleColorCode;

	virtual bool operator==(const PlayerColor & other) const
	{
		return color == other.color;
	}

};

