// \file AITree.h
// \Class used to create the AI
// \author Callum Berger

#ifndef _AITree_
#define _AITree_

#include <vector>

#include "Grid.h"
#include "Enums.h"

struct Move
{
	Move() {};

	Move(int Score)
	{
		score = Score;
	}

	int xIndex;
	int yIndex;
	int score;
};


class AITree
{
public:
	AITree();
	~AITree();

	Grid performAImove(Grid, playerStates &pStateEnums);
	Move Minimax(Grid, int, playerStates &pStateEnums, int);

private:
};

#endif //Defines _AITree_