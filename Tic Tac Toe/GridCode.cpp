//  GridCode.cpp
//  Holds all function code for the Grid class
// \author Callum Berger

#include "Grid.h"

//Constructor for the Grid Class
Grid::Grid()
{

	m_windowSizeX = 13;
	m_windowSizeY = 13;

	for (int i = 0; i < 3; i++)
	{

		for (int j = 0; j < 3; j++)
		{

			m_ticTacToegrid[i][j] = 0;

		}

	}

}

//Deconstructor for the Grid Class
Grid::~Grid()
{

}

//All Set and Get functions for the Grid Class private variables
void Grid::Setgrid(int const arrayX, int const arrayY, int const z)
{

	m_grid[arrayX][arrayY] = z;

}

int Grid::Getgrid(int const arrayX, int const arrayY) const
{

	return m_grid[arrayX][arrayY];

}

void Grid::SetticTacToegrid(int const arrayY, int const arrayX, int const z)
{

	m_ticTacToegrid[arrayY][arrayX] = z;

}

int Grid::GetticTacToegrid(int const arrayY, int const arrayX) const
{

	return m_ticTacToegrid[arrayY][arrayX];

}

int Grid::GetwindowSizeX() const
{

	return m_windowSizeX;

}

int Grid::GetwindowSizeY() const
{

	return m_windowSizeY;

}

// Function used to check if Player or AI has won
int Grid::CheckForWin(Grid tileMap, playerStates &pStateEnums)
{
	//Variable stores the 3 possible tiles that can create a winning state
	int winNode[3];

	//Loops used to check whether each horizontal row is a win
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			winNode[x] = tileMap.m_ticTacToegrid[y][x];
		}

		if ((winNode[0] + winNode[1] + winNode[2]) != empty &&
			winNode[0] == winNode[1] && winNode[1] == winNode[2])
		{
			//returns a value corresponding to a player or ai win
			if( winNode[0] == pStateEnums.playerFilled)
			{

					return pStateEnums.playerWin;

			}
			else
			{

					return pStateEnums.aiPlayerWin;

			}

		}

	}

	//Loops used to check whether each vertical row is a win
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			winNode[y] = tileMap.m_ticTacToegrid[y][x];
		}

		if ((winNode[0] + winNode[1] + winNode[2]) != empty && 
			winNode[0] == winNode[1] && winNode[1] == winNode[2])
		{
			//returns a value corresponding to a player or ai win
			if (winNode[0] == pStateEnums.playerFilled)
			{

				return pStateEnums.playerWin;

			}
			else
			{

				return pStateEnums.aiPlayerWin;

			}
		}

	}

	//checks for a diagonal win
	winNode[0] = tileMap.m_ticTacToegrid[0][0];
	winNode[1] = tileMap.m_ticTacToegrid[1][1];
	winNode[2] = tileMap.m_ticTacToegrid[2][2];

	if ((winNode[0] + winNode[1] + winNode[2]) != empty && 
		winNode[0] == winNode[1] && winNode[1] == winNode[2])
	{
		//returns a value corresponding to a player or ai win
		if (winNode[0] == pStateEnums.playerFilled)
		{

			return pStateEnums.playerWin;

		}
		else
		{

			return pStateEnums.aiPlayerWin;

		}
	}

	//checks for a diagonal win
	winNode[0] = tileMap.m_ticTacToegrid[0][2];
	winNode[1] = tileMap.m_ticTacToegrid[1][1];
	winNode[2] = tileMap.m_ticTacToegrid[2][0];

	if ((winNode[0] + winNode[1] + winNode[2]) != empty && 
		winNode[0] == winNode[1] && winNode[1] == winNode[2])
	{
		//returns a value corresponding to a player or ai win
		if (winNode[0] == pStateEnums.playerFilled)
		{

			return pStateEnums.playerWin;

		}
		else
		{

			return pStateEnums.aiPlayerWin;

		}
	}

	//variable used to store the value of how many spaces are left on the grid
 	int spacesLeft = 0;

	//loops used to check the grid for any free move spaces left
	for (int y = 0; y < 3; y++)
	{
  		for (int x = 0; x < 3; x++)
		{
			if (tileMap.m_ticTacToegrid[y][x] == empty)
			{
				spacesLeft++;
			}
		}
	}

	//returns a draw value if there are no spaces left and a winner has not been found
	if (spacesLeft == empty)
	{
		return draw;
	}

	//returns a value indicating that there are spaces left on the grid
	return spacesRemaining;
}