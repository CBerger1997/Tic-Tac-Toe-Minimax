// \file Enums.h
// \header file containing all enums used
// \author Callum Berger

#ifndef _Enums_
#define _Enums_

typedef int gameEnums;

struct playerStates
{
	gameEnums players = 1;

	gameEnums playerTurn = 1;
	gameEnums playerWin = 1;
	gameEnums playerFilled = 1;

	gameEnums aiTurn = 2;
	gameEnums aiPlayerWin = 2;
	gameEnums aiFilled = 2;

};

enum winStates
{

	draw = 0,
	spacesRemaining = -1

};

enum gridValues
{

	empty = 0

};

enum menuStates
{

	playerNumSelect = 1,
	playerCharSelect = 2

};

#endif //Defines _Enums_