#include "Main.h"

//Struct used to contain all vital SDL variables including additional SDL_tff variables
struct InitStruct
{

	SDL_Window* OOTWindow;
	SDL_Renderer* OOTRenderer;
	TTF_Font* OOTFont;
	SDL_Color OOTColour;
	SDL_Surface* OOTTicTacToeTextSurface;
	SDL_Texture* OOTTicTacToeTextTexture;

}SDLvars;

// Function main
int main(int argc, char* argv[])
{
	//Sets values for the SDL_Window and SDL_Render variables for window display
	SDLvars.OOTWindow = 0;
	SDLvars.OOTRenderer = 0;

	//initialises game looping variables
	bool gameRunLoop = false;
	bool menuRunLoop = false;
	bool endRunLoop = false;
	bool programRunLoop = true;
	bool exit = false;

	//initialises the grid variable used to display and store all grid values
	Grid tileMap;

	//If statement used to check that initialisation has worked correctly, ending the program if something was incorrect
	if (InitialiseWindow("Tic Tac Toe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, tileMap.GetwindowSizeX() * 50, (tileMap.GetwindowSizeY() + 1) * 50, SDL_WINDOW_SHOWN))
	{

		menuRunLoop = true;

	}
	else
	{

		return 1;

	}

	//Initialises SDL_tff if it can be initialised, ending the program if not
	if (InitialiseTTF() == -1)
	{

		return 1;

	}

	playerStates pStateEnums;

	//Runs the program till the user decides to exit
	while (programRunLoop)
	{

		exit = false;

		exit = MenuUpdate(menuRunLoop, tileMap, exit, pStateEnums);

		if (exit == false)
		{

			gameRunLoop = true;

		}
		else
		{

			programRunLoop = false;
			gameRunLoop = false;

		}

		//Function containing constant loop, which causes the program to run until the program is finished or the user exits
		int winner = Update(gameRunLoop, tileMap, pStateEnums);

		endRunLoop = true;

		programRunLoop = EndUpdate(winner, endRunLoop, pStateEnums);

	}

	//Closes the SDL_tff font used and Quits from SDL_tff and SDL
	TTF_CloseFont(SDLvars.OOTFont);
	TTF_Quit();
	SDL_Quit();

	//stops the program
	return 0;

};


// Function used to initialise SDL2
bool InitialiseWindow(const char* header, int x, int y, int h, int w, int flags)
{

	// initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)

	{

		// If SDL initialises, the if statement is run and sets the variables for aiWindow
		SDLvars.OOTWindow = SDL_CreateWindow(header, x, y,
			h, w, flags);

		// If the window creation succeeded, create our renderer
		if (SDLvars.OOTWindow != 0)

		{

			SDLvars.OOTRenderer = SDL_CreateRenderer(SDLvars.OOTWindow, -1, 0);

		}

	}

	else

	{

		// Means SDL failed to initialise
		return false;

	}

	// Means SDL initialised correctly
	return true;

};

// Function used to initialise SDL_tff
bool InitialiseTTF()
{
	// Checks for SDL_tff initialisation
	if (TTF_Init() == -1)
	{
		// Returns false if SDL_tff didn't initialise correctly
		return false;
	}
	else
	{
		// Inisialies SDL_tff
		TTF_Init();
	};

	// Sets the colour of the text to be displayed
	SDLvars.OOTColour = { 255, 255, 255 };

	// Loads the font for the text
	SDLvars.OOTFont = TTF_OpenFont("Times New Roman.ttf", 32);

	// Initialises the text
	SDLvars.OOTTicTacToeTextSurface = TTF_RenderText_Solid(SDLvars.OOTFont, "Tic Tac Toe", SDLvars.OOTColour);

	// Creates the OOTTextTexture from the OOTTextSurface
	SDLvars.OOTTicTacToeTextTexture = SDL_CreateTextureFromSurface(SDLvars.OOTRenderer, SDLvars.OOTTicTacToeTextSurface);

	// returns true if SDL_tff initialised correctly
	return true;

};


// Function used to read the grid values from a text file
Grid ReadingFile(Grid tileMap)
{
	//string used to store the location of the file
	std::string filepath;

	//initialises the variable file from the ifstream class
	std::ifstream file;

	//sets the file path
	filepath = "TileMap.txt";

	//opens the file basedupon the filepath given
	file.open(filepath.c_str());

	//checks if the file open correctly
	if (!file.fail())
	{
		//creates 2 int variables, fileNums stores the numbers read in from the file opened and fileCount iterates through the each number
		int fileNums;
		int fileCount = 0;

		//vector used to store all numbers in the file
		std::vector<int> tileMapNums;

		//pushes back all numbers within the file opened onto the tileMapNums vactor
		while (file >> fileNums)

		{

			tileMapNums.push_back(fileNums);

		};

		//Loops through all the numbers in the vector and sets them to the tileMap grid
		for (int i = 0; i < 13; i++)

		{

			for (int j = 0; j < 13; j++)
			{

				tileMap.Setgrid(i, j, tileMapNums[fileCount]);
				fileCount++;

			};

		};

		//closes the file
		file.close();

	}

	//produces an error if the file opened incorrectly
	else
	{

		std::cout << "Error loading Map File\n";
		std::cin.get();

	}

	//returns the updated tileMap variable
	return tileMap;

};


// Function used to run through the game loop and constantly update the game and window
bool MenuUpdate(bool menuRunLoop, Grid tileMap, bool exit, playerStates &pStateEnums)
{
	int curMenuState = playerNumSelect;
	Player p;
	p.SetplayerPositionX(50);
	p.SetplayerPositionY(200);

	//starts the constant program loop for the menu
	while (menuRunLoop)
	{
		//creates the SDL_Event variable used to handle events
		SDL_Event event;

		//loops through while an event is happening
		while (SDL_PollEvent(&event))

		{

			//Switch case used to check for events
			switch (event.type)
			{

				//ends the program loop if SDL_QUIT event is true
			case SDL_QUIT:
			{

				return true;
				break;

			}

			//checks for keydown events
			case SDL_KEYDOWN:
			{

				switch (event.key.keysym.sym)
				{

					//ends the program if the user presses escape
				case SDLK_ESCAPE:
				{

					return true;
					break;

				}

				//Moves the player position left if the LEFT key is pressed down
				case SDLK_LEFT:
				{

					p.SetplayerPositionX(p.GetplayerPosition().x - 400);
					p.SetplayerX(p.GetplayerX() - 1);
					break;

				}
				//Moves the player position right if the RIGHT key is pressed down
				case SDLK_RIGHT:
				{

					p.SetplayerPositionX(p.GetplayerPosition().x + 400);
					p.SetplayerX(p.GetplayerX() + 1);
					break;

				}

				//Continues the program to the game
				case SDLK_SPACE:
				{

					switch (curMenuState)
					{

					case playerNumSelect:
					{

						switch (p.GetplayerPosition().x)
						{

						case 50:
						{

							pStateEnums.players = 1;

							break;

						}

						case 450:
						{

							pStateEnums.players = 2;

							break;

						}

						}
						curMenuState = playerCharSelect;

						break;

					}

					case playerCharSelect:
					{

						switch (p.GetplayerPosition().x)
						{

						case 50:
						{

							pStateEnums.playerTurn = 1;
							pStateEnums.playerWin = 1;
							pStateEnums.playerFilled = 1;

							pStateEnums.aiTurn = 2;
							pStateEnums.aiPlayerWin = 2;
							pStateEnums.aiFilled = 2;

							break;

						}

						case 450:
						{

							pStateEnums.playerTurn = 2;
							pStateEnums.playerWin = 2;
							pStateEnums.playerFilled = 2;

							pStateEnums.aiTurn = 1;
							pStateEnums.aiPlayerWin = 1;
							pStateEnums.aiFilled = 1;

							break;

						}

						}

						menuRunLoop = false;

						break;

					}

					break;

					};

				};

				}

			};

			//Checks to make sure the player is still on the grid
			p = p.CheckPlayerLocation(p);

			};

		}

		MenuRender(tileMap, curMenuState, p);

	}

	return exit;

};

// Function used to run through the game loop and constantly update the game and window
int Update(bool gameRunLoop, Grid tileMap, playerStates &pStateEnums)
{
	//sets the current player and win state
	int curPlayer = 1;
	int win = -1;
	//Creates the player and ai variables
	Player p;
	Player p2;
	AITree ai;

	//Sets the values for the tileMap used to display the grid
	tileMap = ReadingFile(tileMap);

	//starts the constant program loop
	while (gameRunLoop)
	{
		//creates the SDL_Event variable used to handle events
		SDL_Event event;

		//loops through while an event is happening
		while (SDL_PollEvent(&event))

		{

			//Switch case used to check for events
			switch (event.type)
			{

				//ends the program loop if SDL_QUIT event is true
			case SDL_QUIT:
			{

				gameRunLoop = false;
				break;

			}

			//checks for keydown events
			case SDL_KEYDOWN:
			{

				switch (event.key.keysym.sym)
				{

					//ends the program if the user presses escape
				case SDLK_ESCAPE:
				{

					gameRunLoop = false;
					break;

				}

				//Moves the player position up if the UP key is pressed down
				case SDLK_UP:
				{

					if (curPlayer == pStateEnums.aiTurn && pStateEnums.players == 2)
					{

						p2.SetplayerPositionY(p2.GetplayerPosition().y - 200);
						p2.SetplayerY(p2.GetplayerY() - 1);

					}

					else

					{

						p.SetplayerPositionY(p.GetplayerPosition().y - 200);
						p.SetplayerY(p.GetplayerY() - 1);

					}

					break;

				}

				//Moves the player position down if the DOWN key is pressed down
				case SDLK_DOWN:
				{

					if (curPlayer == pStateEnums.aiTurn && pStateEnums.players == 2)
					{

						p2.SetplayerPositionY(p2.GetplayerPosition().y + 200);
						p2.SetplayerY(p2.GetplayerY() + 1);

					}

					else

					{

						p.SetplayerPositionY(p.GetplayerPosition().y + 200);
						p.SetplayerY(p.GetplayerY() + 1);

					}

					break;

				}
				//Moves the player position left if the LEFT key is pressed down
				case SDLK_LEFT:
				{

					if (curPlayer == pStateEnums.aiTurn && pStateEnums.players == 2)
					{

						p2.SetplayerPositionX(p2.GetplayerPosition().x - 200);
						p2.SetplayerX(p2.GetplayerX() - 1);

					}

					else

					{

						p.SetplayerPositionX(p.GetplayerPosition().x - 200);
						p.SetplayerX(p.GetplayerX() - 1);



					}

					break;
				}
				//Moves the player position right if the RIGHT key is pressed down
				case SDLK_RIGHT:
				{
					if (curPlayer == pStateEnums.aiTurn && pStateEnums.players == 2)
					{

						p2.SetplayerPositionX(p2.GetplayerPosition().x + 200);
						p2.SetplayerX(p2.GetplayerX() + 1);

					}

					else

					{

						p.SetplayerPositionX(p.GetplayerPosition().x + 200);
						p.SetplayerX(p.GetplayerX() + 1);

					}

					break;

				}
				//Selects the current player position for the players move if the SPACE key is pressed down
				case SDLK_SPACE:
				{

					//checks whether it's the players turn then places the corresponding symbol 'X' or 'O' on the player's position
					if (curPlayer == pStateEnums.playerTurn)
					{
						//checks if the current space is empty
						switch (tileMap.GetticTacToegrid(p.GetplayerY(), p.GetplayerX()))
						{

						case 0:
						{
							tileMap = p.PlayerMove(tileMap, p, pStateEnums, curPlayer);
							win = tileMap.CheckForWin(tileMap, pStateEnums);
							//Changes the turn to the ai's turn
							curPlayer = pStateEnums.aiTurn;
							//Pauses the program briefly
							Sleep(250);
							break;

						}

						}
					}
					else if (curPlayer == pStateEnums.aiTurn && pStateEnums.players == 2)
					{
						//checks if the current space is empty
						switch (tileMap.GetticTacToegrid(p2.GetplayerY(), p2.GetplayerX()))
						{

						case 0:
						{
							tileMap = p2.PlayerMove(tileMap, p2, pStateEnums, curPlayer);
							win = tileMap.CheckForWin(tileMap, pStateEnums);
							//Changes the turn to the ai's turn
							curPlayer = pStateEnums.playerTurn;
							//Pauses the program briefly
							Sleep(250);
							break;

						}

						}
					}

					

				}


				};

				//Checks to make sure the player is still on the grid
				p = p.CheckPlayerLocation(p);

				if (pStateEnums.players == 2)
				{
					//Checks to make sure the second player is still on the grid
					p2 = p2.CheckPlayerLocation(p2);
				}

			};

			}

		};

		if (curPlayer == pStateEnums.aiTurn && pStateEnums.players == 2)
		{
			//Renders the grid and everything displayed on the grid before the ai's turn			
			ProgramRender(tileMap, p2, curPlayer, ai);
		}
		else
		{
			//Renders the grid and everything displayed on the grid before the ai's turn			
			ProgramRender(tileMap, p, curPlayer, ai);
		}

		//checks whether a win state has been reached
		if (win != spacesRemaining)
		{
			//ends the program loop
			gameRunLoop = false;
		}
		//Checks whether it's the ai's turn
		else if (curPlayer == pStateEnums.aiTurn && pStateEnums.players == 1)
		{
			//performs the tree search and chooses the best move for the ai
			tileMap = ai.performAImove(tileMap, pStateEnums);
			win = tileMap.CheckForWin(tileMap, pStateEnums);
			//pauses the program briefly
			Sleep(250);
			//changes the current player to the player
			curPlayer = pStateEnums.playerTurn;

			//Renders the grid and everything displayed on the grid after the ai's turn
			ProgramRender(tileMap, p, curPlayer, ai);

		}

	};

	return win;

};

bool EndUpdate(int winner, bool endRunLoop, playerStates &pStateEnums)
{

	while (endRunLoop)
	{
		//creates the SDL_Event variable used to handle events
		SDL_Event event;

		//loops through while an event is happening
		while (SDL_PollEvent(&event))

		{

			//Switch case used to check for events
			switch (event.type)
			{

			//ends the program loop if SDL_QUIT event is true
			case SDL_QUIT:
			{

				return false;
				break;

			}

			//checks for keydown events
			case SDL_KEYDOWN:
			{

				switch (event.key.keysym.sym)
				{

				//ends the program if the user presses the ESCAPE key
				case SDLK_ESCAPE:
				{

					return false;
					break;

				}


				//Closes the program if the user presses the SPACE key
				case SDLK_SPACE:
				{

					return true;
					break;

				}

				}

			};


			};

		}

		std::string winnerText;

		std::string menuText;
		SDL_Rect menuTextRect = { 50, 550, 550, 50 };

		SDL_SetRenderDrawColor(SDLvars.OOTRenderer, 0, 0, 0, 0);

		SDL_RenderClear(SDLvars.OOTRenderer);

		SDL_Rect winnerTextRect = { 50, 200, 550, 50 };

		if (winner == 1)
		{
			winnerText = "The winner is: X";
		}
		else if (winner == 2)
		{
			winnerText = "The winner is: O";
		}
		else if (winner == 0)
		{
			winnerText = "The game is a DRAW";
		}
		else
		{
			winnerText = "Game was closed";
		}

		RenderText(winnerText, winnerTextRect);

		menuText = "Press SPACE to restart";
		menuTextRect = { 50, 550, 550, 50 };

		RenderText(menuText, menuTextRect);

		SDL_RenderPresent(SDLvars.OOTRenderer);

	}

	return false;

}

// Function used to render the window for the program menu
void MenuRender(Grid tileMap, int menuState, Player p)
{
	//string variable used to display text based on the current player
	std::string menuText;
	std::string leftOptionText;
	std::string rightOptionText;

	//Sets the initial render colour to black
	SDL_SetRenderDrawColor(SDLvars.OOTRenderer, 0, 0, 0, 0);

	// Clear the window to set Colour
	SDL_RenderClear(SDLvars.OOTRenderer);

	SDL_Rect menuRect1 = { 50, 200, 150, 150 };

	SDL_Rect leftTextRect = { 50, 350, 150, 150 };

	SDL_Rect menuRect2 = { 450, 200, 150, 150 };

	SDL_Rect rightTextRect = { 450, 350, 150, 150 };

	SDL_Rect menuTextRect = { 50, 50, 550, 50 };

	if (menuState == playerNumSelect)
	{

		menuText = "Select Number of Players";
		leftOptionText = "1";
		rightOptionText = "2";

	}
	else if (menuState == playerCharSelect)
	{

		menuText = "Select the Player for player 1";
		leftOptionText = "X";
		rightOptionText = "O";
	}

	SDL_SetRenderDrawColor(SDLvars.OOTRenderer, 255, 255, 255, 0);
	SDL_RenderFillRect(SDLvars.OOTRenderer, &menuRect1);
	SDL_RenderFillRect(SDLvars.OOTRenderer, &menuRect2);



	//Sets the render colour to green and shows the players current grid position
	SDL_SetRenderDrawColor(SDLvars.OOTRenderer, 0, 255, 0, 0);
	SDL_RenderFillRect(SDLvars.OOTRenderer, &p.GetplayerPosition());

	RenderText(menuText, menuTextRect);
	RenderText(leftOptionText, leftTextRect);
	RenderText(rightOptionText, rightTextRect);

	menuText = "Press SPACE to select";
	menuTextRect = { 50, 550, 550, 50 };

	RenderText(menuText, menuTextRect);


	// Display the Window
	SDL_RenderPresent(SDLvars.OOTRenderer);

};

// Function used to render the window for the program main code
void ProgramRender(Grid tileMap, Player p, int curPlayer, AITree ai)
{
	//creates the SDL_Rect variable used to display each tile of the grid
	SDL_Rect tile = { 0, 50, 50, 50 };

	//string variable used to display text based on the current player
	std::string PlayerText;

	//Sets the initial render colour to black
	SDL_SetRenderDrawColor(SDLvars.OOTRenderer, 0, 0, 0, 0);

	// Clear the window to set Colour
	SDL_RenderClear(SDLvars.OOTRenderer);

	//loops used to display the whole grid using the tile variable and grid variable
	for (int i = 0; i < 13; i++)

	{

		for (int j = 0; j < 13; j++)

		{

			if (tileMap.Getgrid(i, j) == 1)

			{

				// Set Render Colour to Black
				SDL_SetRenderDrawColor(SDLvars.OOTRenderer, 0, 0, 0, 0);

			}

			else if (tileMap.Getgrid(i, j) == 0)

			{

				// Set Render Colour to White
				SDL_SetRenderDrawColor(SDLvars.OOTRenderer, 255, 255, 255, 0);

			}

			// Render the Tile 
			SDL_RenderFillRect(SDLvars.OOTRenderer, &tile);

			tile.x += 50;

			if (tile.x >= tileMap.GetwindowSizeX() * 50)

			{

				tile.x = 0;
				tile.y += 50;

			};

		};

	};

	//Sets the render colour to green and shows the players current grid position
	SDL_SetRenderDrawColor(SDLvars.OOTRenderer, 0, 255, 0, 0);
	SDL_RenderFillRect(SDLvars.OOTRenderer, &p.GetplayerPosition());

	//Loop used to display the Noughts and Crosses based on player and ai placements
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			switch (tileMap.GetticTacToegrid(y, x))
			{
			case 1:
			case 2:
			{
				int x2;
				int y2;

				SDL_SetRenderDrawColor(SDLvars.OOTRenderer, 0, 0, 0, 0);

				switch (y)
				{
				case 0:
				{
					y2 = 100;
					break;
				}
				case 1:
				{
					y2 = 300;
					break;
				}
				case 2:
				{
					y2 = 500;
					break;
				}
				}

				switch (x)
				{
				case 0:
				{
					x2 = 50;
					break;
				}
				case 1:
				{
					x2 = 250;
					break;
				}
				case 2:
				{
					x2 = 450;
					break;
				}
				}

				if (tileMap.GetticTacToegrid(y, x) == 1)
				{
					SDL_RenderDrawLine(SDLvars.OOTRenderer, x2, y2, x2 + 150, y2 + 150);
					SDL_RenderDrawLine(SDLvars.OOTRenderer, x2 + 150, y2, x2, y2 + 150);
				}
				else if (tileMap.GetticTacToegrid(y, x) == 2)
				{
					SDL_RenderDrawLine(SDLvars.OOTRenderer, x2 + 75, y2, x2, y2 + 75);
					SDL_RenderDrawLine(SDLvars.OOTRenderer, x2, y2 + 75, x2 + 75, y2 + 150);
					SDL_RenderDrawLine(SDLvars.OOTRenderer, x2 + 75, y2 + 150, x2 + 150, y2 + 75);
					SDL_RenderDrawLine(SDLvars.OOTRenderer, x2 + 150, y2 + 75, x2 + 75, y2);
				}

				break;
			}
			}
		}
	}

	//SDL_Rects used to display the game text and current player text 
	SDL_Rect PlayerTextRect = { 50, 50, 550, 50 };
	SDL_Rect TextRect = { 50, 0, 550, 50 };

	//copys part of the OOTTicTacToeTextTexture to the OOTRenderer
	SDL_RenderCopy(SDLvars.OOTRenderer, SDLvars.OOTTicTacToeTextTexture, NULL, &TextRect);

	//checks for the current player and displays who's turn it is accordingly
	if (curPlayer == 1)
	{
		PlayerText = "Current Player: Player X";
	}
	else
	{
		PlayerText = "Current Player: Player O";
	}


	//Calls function to render the player text
	RenderText(PlayerText, PlayerTextRect);

	// Display the Window
	SDL_RenderPresent(SDLvars.OOTRenderer);

};

// Function used to render text
void RenderText(std::string Text, SDL_Rect TextRect)
{

	SDL_Surface* textSurface;
	SDL_Texture* textTexture;

	// Initialises the text
	textSurface = TTF_RenderText_Solid(SDLvars.OOTFont, Text.c_str(), SDLvars.OOTColour);

	// Creates the OOTTextTexture from the OOTTextSurface
	textTexture = SDL_CreateTextureFromSurface(SDLvars.OOTRenderer, textSurface);

	//copys part of the OOTTicTacToeTextTexture to the OOTRenderer
	SDL_RenderCopy(SDLvars.OOTRenderer, textTexture, NULL, &TextRect);

	//Frees the OOTPlayerTextSurface and destroys the OOTPlayerTextTexture as to not use up unneeded memory
	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);

}