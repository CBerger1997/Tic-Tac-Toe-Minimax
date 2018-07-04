//  AITreeCode.cpp
//  Holds all function code for the AITree class
// \author Callum Berger

#include "AITree.h"

//Constructor for the Grid Class
AITree::AITree()
{
}

//Deconstructor for the Grid Class
AITree::~AITree()
{
}

//Function used to call the minimax algorithm and then set the ai's move
Grid AITree::performAImove(Grid tileMap, playerStates &pStateEnums)
{
	Move bestMove = Minimax(tileMap, pStateEnums.aiTurn, pStateEnums, 0);
	tileMap.SetticTacToegrid(bestMove.yIndex, bestMove.xIndex, pStateEnums.aiFilled);

	return tileMap;
}

//Function used to perform the minimax algorithm and produce the most efficient move for the ai
Move AITree::Minimax(Grid tileMap, int curPlayer, playerStates &pStateEnums, int depth)
{

	//Checks the tileMap for whether an end state has been found, returning a score accordingly or no score if there is no end state yet
	int win = tileMap.CheckForWin(tileMap, pStateEnums);

	if (win == pStateEnums.aiPlayerWin)
	{
		return Move(10 - depth);
	}
	else if (win == pStateEnums.playerWin)
	{
		return Move(depth - 10);
	}
	else if (win == draw)
	{
		return Move(0);
	}

	//Creates a vector which is used to store possible moves
	std::vector<Move> moves;

	depth += 1;

	/*Performs the recursive part of the algorithm
	which searches the tree for all possible moves available
	and stores them in the moves vector*/
	for (int y = 0; y < 3; y++)
	{

		for (int x = 0; x < 3; x++)
		{

			if (tileMap.GetticTacToegrid(y, x) == empty)
			{
				//sets the empty grid node to a node of the current player's value
				Move move;
				move.xIndex = x;
				move.yIndex = y;
				tileMap.SetticTacToegrid(y, x, curPlayer);

				//Recursion
				if (curPlayer == pStateEnums.aiTurn)
				{

					move.score = Minimax(tileMap, pStateEnums.playerFilled, pStateEnums, depth).score;

				}
				else
				{

					move.score = Minimax(tileMap, pStateEnums.aiFilled, pStateEnums, depth).score;

				}

				//empties nodes that have previously been filled through recursion
				moves.push_back(move);
				tileMap.SetticTacToegrid(y, x, empty);

			}

		}

	}

	//sets variables used for checking scores and moves
	int bestMove = 0;
	int maxScore = -1000;
	int minScore = 1000;

	//Loops through all moves available and finds the best move for each player
	for (int i = 0; i < moves.size(); i++)
	{
		//checks for curPlayer's turn
		if (curPlayer == pStateEnums.aiTurn)
		{
			//checks whether the current maxScore is less than the current score within the moves vector
			if (maxScore < moves[i].score)
			{
				//sets the new bestMove and maxScore
				bestMove = i;
				maxScore = moves[i].score;
			}
		}
		else
		{
			//checks whether the current minScore is greater than the current score within the moves vector
			if (minScore > moves[i].score)
			{
				//sets the new bestMove and minScore
				bestMove = i;
				minScore = moves[i].score;
			}
		}
	}

	//returns the best move available
	return moves[bestMove];
}
