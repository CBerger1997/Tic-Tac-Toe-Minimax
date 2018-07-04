#ifndef _Main_
#define _Main_

#include <vector>
#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>

//all  SDL Includes
#include <SDL.h>
#include <SDL_ttf.h>

//all header files included
#include "Grid.h"
#include "Player.h"
#include "AITree.h"
#include "Enums.h"

//creates all identifiers for each function
bool InitialiseWindow(const char*, int, int, int, int, int);
bool InitialiseTTF();

Grid ReadingFile(Grid);

bool MenuUpdate(bool, Grid, bool, playerStates &pStateEnums);
int Update(bool, Grid, playerStates &pStateEnums);
bool EndUpdate(int, bool, playerStates &pStateEnums);

void MenuRender(Grid, int, Player);
void ProgramRender(Grid, Player, int, AITree);
void RenderText(std::string, SDL_Rect);

#endif // Defines _Main_