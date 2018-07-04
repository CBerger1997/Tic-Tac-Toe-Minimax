// \file Grid.h
// \Class used to create Grid System
// \author Callum Berger

#ifndef _Grid_
#define _Grid_

#include "Enums.h"

class Grid
{
public:

	Grid();
	~Grid();

	void Setgrid(int const, int const, int const);
	int Getgrid(int, int) const;

	void SetticTacToegrid(int const, int const, int const);
	int GetticTacToegrid(int, int) const;

	int GetwindowSizeX() const;
	int GetwindowSizeY() const;

	int CheckForWin(Grid, playerStates &pStateEnums);

private:

	int m_windowSizeX;
	int m_windowSizeY;

	int m_grid[13][13];

	int m_ticTacToegrid[3][3];

};

#endif //Defines _Grid_