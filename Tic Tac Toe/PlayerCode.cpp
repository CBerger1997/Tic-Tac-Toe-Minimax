//  PlayerCode.cpp
//  Holds all function code for the Player class
// \author Callum Berger

#include "Player.h"

//Constructor for the Grid Class
Player::Player()
{

	m_playerPosition.x = 250;
	m_playerPosition.y = 300;
	m_playerPosition.h = 150;
	m_playerPosition.w = 150;

	m_playerX = 1;
	m_playerY = 1;

}

//Deconstructor for the Grid Class
Player::~Player()
{

}

//All Set and Get functions for the Player Class private variables
void Player::SetplayerPositionX(int const x)
{
	m_playerPosition.x = x;
}

void Player::SetplayerPositionY(int const y)
{
	m_playerPosition.y = y;
}

SDL_Rect Player::GetplayerPosition() const
{
	return m_playerPosition;
}

void Player::SetplayerX(int const x)
{
	m_playerX = x;
}

int Player::GetplayerX() const
{
	return m_playerX;
}

void Player::SetplayerY(int const y)
{
	m_playerY = y;
}

int Player::GetplayerY() const
{
	return m_playerY;
}

//Function used to check whether the player marker is still within the bounds of the grid
Player Player::CheckPlayerLocation(Player p)
{
	//moves the player marker back into the boundaries of the grid if it is outside of the grid boundaries
	if (p.GetplayerPosition().x > 450)
	{
		p.SetplayerPositionX(450);
		p.SetplayerX(p.GetplayerX() - 1);
	}
	if (p.GetplayerPosition().x < 50)
	{
		p.SetplayerPositionX(50);
		p.SetplayerX(p.GetplayerX() + 1);
	}
	//checks the y value of the player marker to check it is in the boundaries of the grid
	switch (p.GetplayerPosition().y)
	{
		//moves the player marker back into the boundaries of the grid if it is outside of the grid boundaries
	case 700:
	{
		p.SetplayerPositionY(500);
		p.SetplayerY(p.GetplayerY() - 1);
		break;
	}
	case -100:
	{
		p.SetplayerPositionY(100);
		p.SetplayerY(p.GetplayerY() + 1);
		break;
	}
	}

	return p;

}

//Function used to set the players move
Grid Player::PlayerMove(Grid tileMap, Player p, playerStates &pStateEnums, int player)
{
	if (pStateEnums.players == 2 && player == pStateEnums.aiTurn)
	{
		//sets the current player location on the grid to the value of the player ('X' = 1 or 'O' = 2)
		tileMap.SetticTacToegrid(p.GetplayerY(), p.GetplayerX(), pStateEnums.aiFilled);
	}
	else
	{
		//sets the current player location on the grid to the value of the player ('X' = 1 or 'O' = 2)
		tileMap.SetticTacToegrid(p.GetplayerY(), p.GetplayerX(), pStateEnums.playerFilled);
	}

	return tileMap;
}