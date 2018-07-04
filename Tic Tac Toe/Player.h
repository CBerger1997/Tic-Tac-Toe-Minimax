// \file Player.h
// \Class used to create the Player object
// \author Callum Berger

#ifndef _Player_
#define _Player_

#include <SDL.h>
#include "Grid.h"
#include "Enums.h"

class Player
{
public:
	Player();
	~Player();

	void SetplayerPositionX(const int);
	void SetplayerPositionY(const int);

	SDL_Rect GetplayerPosition() const;

	void SetplayerX(const int);
	int GetplayerX() const;

	void SetplayerY(const int);
	int GetplayerY() const;

	Player CheckPlayerLocation(Player);

	Grid PlayerMove(Grid, Player, playerStates &pStateEnums, int);

private:
	SDL_Rect m_playerPosition;
	int m_playerX;
	int m_playerY;
};

#endif //Defines _Player_