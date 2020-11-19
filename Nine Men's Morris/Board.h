#pragma once

#include "Position.h"
#include "Pocket.h"

class Board
{

private:
	//OLD
	//Pocket horizontalPockets[8];
	//Pocket verticalPockets[8];

	BoardSpace ** board = new BoardSpace*[7];

	void InstantiateBoardSpaces();
	//Debug
	void InstantiateBoardSpacesWithPositions();

	void LinkBoardSpaces();
	void LinkBoardSpacesVertical(const int i,const int j);
	void LinkBoardSpacesHorizontal(const int i, const int j);

	bool IsOccupied(const Position * const pos) const;

	void Place(const Position * const  pos, Piece * const piece);
	

public:
	~Board();


	//Init
	void Initialize();

	//Game Flow
	Piece * PlaceNew(const Position * pos, const PlayerColor * const color);

	void Move(const Position * const start, const Position * const dest);

	Piece * const Remove(const Position * const pos);

	//Game Checks
	const bool AreNeighbours(const Position * const pos1, const Position * const pos2) const;
	
	//Board Checks
	const bool IsEmpty(const Position * const pos) const;
	
	//Board Getters

	//BoardSpace

	BoardSpace * GetBoardSpaceAt(const Position * const pos) const;

	//Symbols

	const char GetSymbolAtPosition(const int x, const int y) const;

	const char GetSymbolAtPosition(Position pos) const;

	const string GetStringSymbolAtPosition(const int x, const int y) const;

	const string GetStringSymbolAtPosition(Position pos) const;

	//PlayerColor

	const PlayerColor * GetPlayerColorAtPosition(const int x, const int y) const;

	const PlayerColor * GetPlayerColorAtPosition(const Position * const pos) const;

	//Board

	BoardSpace ** GetBoard();
};

