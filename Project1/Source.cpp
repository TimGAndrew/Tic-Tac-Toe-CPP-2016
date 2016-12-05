#include <iostream>
#include <string>
#include <conio.h>										//for _getch
#include <chrono>										//for timer ("AI is thinking ...")
#include <thread>										   //this is also required for ^
using namespace std;

/*----PROTOTYPES-----*/									//These functions are better explained in their respective code (under main)
void ShowTitle();
void ClearScreen();
void SetHumanMark(char &humanMark);
void SetAiMark(char &aiMark, char &playerMark);
void IsHumanNext(bool &humanNext);
void PlayAgain(bool &playTheGame);

/*----CLASSES-----*/
class AI												//This is the AI class
{
private:
	char humanMark;										//needed to tell what mark opponent
	bool aiFirst;
	int opponentCount;

	bool SpotTaken(int index, char board[9])			//Method to check and see if a spot is taken.
	{
		if (board[index] != 'X' && board[index] != 'O')
		{
			return false;
		}
		else
		{
			return true;
		}

	}

	int WhatDoINeedToBlock(char board[9])				//Method to check if the AI needs to block the next move.
	{
		int count = 0;									//initialize counter
		int boardCheck[8][3] = { { 0,1,2 },				//Initialize a 2D array as a board checker containing the possible win combinations
		{ 3,4,5 },
		{ 6,7,8 },
		{ 0,3,6 },
		{ 1,4,7 },
		{ 2,5,8 },
		{ 0,4,8 },
		{ 2,4,6 } };

		for (int i = 0; i < 8; i++)						//iterate through possible solutions
		{
			count = 0;									//reset counter on each solution

			for (int j = 0; j < 3; j++)					//iterate through each solution
			{
				if (board[boardCheck[i][j]] == humanMark) //sum the total of opponent marks for each solution
				{
					count++;
				}
			}
			if (count == 2)								//if opponent has any solution full of 2 marks
			{
				for (int k = 0; k < 3; k++)				//iterate through that solution again
				{
					if (board[boardCheck[i][k]] != humanMark && board[boardCheck[i][k]] != aiMark) //find out what spot is open
					{
						return boardCheck[i][k];			//set that as the spot to block
					}
				}
			}
		}
		return -1;										//what to return if there is nothing to block
	}

	int CanIWinWithThisMove(char board[9])				//method to check if the AI can win with the current move.
	{
		int count = 0;									//initialize counter
		int boardCheck[8][3] = { { 0,1,2 },				//Initialize a 2D array as a board checker containing the possible win combinations
		{ 3,4,5 },
		{ 6,7,8 },
		{ 0,3,6 },
		{ 1,4,7 },
		{ 2,5,8 },
		{ 0,4,8 },
		{ 2,4,6 } };

		for (int i = 0; i < 8; i++)						//iterate through possible solutions
		{
			count = 0;									//reset counter on each solution

			for (int j = 0; j < 3; j++)					//iterate through each solution
			{
				if (board[boardCheck[i][j]] == aiMark) //sum the total of AI marks for each solution
				{
					count++;
				}
			}
			if (count == 2)								//if AI has any solution full of 2 marks
			{
				for (int k = 0; k < 3; k++)				//iterate through that solution again
				{
					if (board[boardCheck[i][k]] != humanMark && board[boardCheck[i][k]] != aiMark) //find out if there is an open spot
					{
						return boardCheck[i][k];			//set that as the spot to win
					}
				}
			}
		}
		return -1;										//what to return if nothing can win
	}

	int WhatIsMyBestMove(char board[9])		//method to check what the AI's best move is
	{
		int count = 0;									//initialize counter
		int countEmpty = 0;
		int boardCheck[8][3] = { { 0,1,2 },				//Initialize a 2D array as a board checker containing the possible win combinations
		{ 3,4,5 },
		{ 6,7,8 },
		{ 0,3,6 },
		{ 1,4,7 },
		{ 2,5,8 },
		{ 0,4,8 },
		{ 2,4,6 } };

		for (int i = 0; i < 8; i++)							//iterate through possible solutions
		{
			count = 0;									 //reset counter on each solution
			countEmpty = 0;

			for (int j = 0; j < 3; j++)						//iterate through each solution
			{
				if (board[boardCheck[i][j]] == aiMark)		//sum the total of AI marks for each solution
				{
					count++;
				}
				if (board[boardCheck[i][j]] != humanMark && board[boardCheck[i][j]] != aiMark)
				{
					countEmpty++;
				}
			}
			if (count == 1 && countEmpty == 2)					//if AI has one space in the solution, and the solution also has 2 open spaces
			{
				for (int k = 0; k < 3; k++)				//iterate through that solution again
				{
					if (board[boardCheck[i][k]] != humanMark && board[boardCheck[i][k]] != aiMark) //find out what spot is open
					{
						return boardCheck[i][k];			//set that as the best spot
					}
				}
			}
		}
		return -1;			//what to return if there is no best moves
	}

	int PickARandomSpot(char board[9])		//a last ditch effort to pick a spot (will pick the first available spot)
	{
		for (int i = 0; i < 9; i++)
		{
			if (board[i] != humanMark && board[i] != aiMark) //find out what spot is open
			{
				return i;
			}
		}
	}

public:
	char aiMark;

	AI(char aiMark, char humanMark, bool humanNext)						//AI constructor
		:aiMark(aiMark), humanMark(humanMark), aiFirst(!humanNext) {}		//Constructor initialization values

	int MakeMove(char board[9])
	{
		int returnValue = -1;

		opponentCount = 0;                               //board counter to check # of opponent moves

		for (int i = 0; i < 9; i++)						//determine how many opponent marks there are
		{
			if (board[i] == humanMark)
			{
				opponentCount++;
			}
		}


		if (aiFirst)									//code for if AI plays first
		{
			if (opponentCount == 0)
			{
				int choices[4] = { 0, 2, 6, 8 };
				int randomChoice = rand() % 4;
				returnValue = (choices[randomChoice]);
			}
			
			if (opponentCount == 1)
			{
				//Human went to center:
				if (board[4] == humanMark)			
				{
					if (board[0] == aiMark)
					{
						returnValue = 8;
					}
					else if (board[2] == aiMark)
					{
						returnValue = 6;
					}
					else if (board[6] == aiMark)
					{
						returnValue = 2;
					}
					else
					{
						returnValue = 0;
					}
				}
			
				//Human went to corner:
				if (board[0] == humanMark || board[2] == humanMark || board[6] == humanMark || board[8] == humanMark)
				{
					do
					{
						int choices[4] = { 0, 2, 6, 8 };
						int randomChoice = rand() % 4;
						returnValue = (choices[randomChoice]);
					} while (SpotTaken(returnValue, board));
				}
			
				//Human went to the edge:
				if (board[1] == humanMark || board[3] == humanMark || board[5] == humanMark || board[7] == humanMark)
				{
					returnValue = 4;
				}
			}

			//human has 2+ moves
			if (opponentCount >= 2)
			{
				if (CanIWinWithThisMove(board) != -1)
				{
					returnValue = CanIWinWithThisMove(board);
				}
				else if (WhatDoINeedToBlock(board) != -1)
				{
					returnValue = WhatDoINeedToBlock(board);
				}
				else if (WhatIsMyBestMove(board) != -1)
				{
					returnValue = WhatIsMyBestMove(board);
				}
				else
				{
					returnValue = PickARandomSpot(board);
				}
			}
		}
		/*===================================================================*/
		else														//AI Plays second
		{
			//AI's first move
			if (opponentCount == 1)
			{
				//pick center square if opponent didnt pick it:
				if (board[4] != humanMark) 
				{
					returnValue = 4;
				}
				//or else pick corner square :
				else
				{
					do
					{
						int choices[4] = { 0, 2, 6, 8 };
						int randomChoice = rand() % 4;
						returnValue = (choices[randomChoice]);
					} while (SpotTaken(returnValue, board));
				}

			}

			//AI's second move
			if (opponentCount >= 2)
			{
				if (CanIWinWithThisMove(board) != -1)
				{
					returnValue = CanIWinWithThisMove(board);
				}
				else if (WhatDoINeedToBlock(board) != -1)
				{
					returnValue = WhatDoINeedToBlock(board);
				}
				else if (WhatIsMyBestMove(board) != -1)
				{
					returnValue = WhatIsMyBestMove(board);
				}
				else
				{
					returnValue = PickARandomSpot(board);
				}

			}

		}

		return returnValue;

	}


};

class Game												//This is the game class
{
private:
	char board[9];										//An array to hold the board chars
	char humanMark;										//Mark human will use
	char aiMark;										//Mark AI will use
	AI ai;												//The AI object
	int totalMoves;										//The total number of moves in the game
	bool humanNext;										//Boolean to determine if human is the next player
	bool winnerFound;									//Boolean to store if winner is found

	void PrintBoard()									//a method to print the board
	{
		//ascii source: http://patorjk.com/software/taag/#p=display&f=Bigfig&t=%201%20%7C%202%20%7C%203%0A---%2B---%2B---%0A%20X%20%7C%20O%20%7C%206%0A---%2B---%2B---%0A%207%20%7C%208%20%7C%209
															//digit arrays: --- abandoned for now - it's a bit of work,
		/*string vertPadding = "       |       |       ";
		string sidePadding = "  ";
		string horizLine = "-------+-------+-------";
		string one[3] = { { "   " },
						  { "/| " },
						  { " | " } };

		string two[3] = { { "__ " },
						  { " _)" },
						  { "/__" } };

		string three[3] = { { "__ " },
						    { "__)" },
							{ "__)" } };

		string four[3] = { { "   " },
						   { "|_|" },
						   { "  |" } };

		string five[3] = { { " __" },
						   { "|_ " },
						   { "__)" } };

		string six[3] = { { " _ " },
						  { "|_ " },
						  { "|_)" } };

		string seven[3] = { { "__ " },
						    { " / " },
						    { "/  " } };

		string eight[3] = { { " _ " },
						    { "(_)" },
							{ "(_)" } };

		string nine[3] = { { " _ " },
						   { "(_|" },
						   { " _|" } };

		string x[3] = { { "\\ /" },
						{ " X " },
						{ "/ \\"}};

		string o[3] = { { " _ " },
						{ "/ \\"},
						{"\\_/"} }; */
		
		cout << string(9, '\n');
		cout << string(55, ' ');
		cout << "   |   |   " << endl;
		cout << string(55, ' ');
		for (int i = 0; i <= 2; i++) // print top line
		{
			//if (board[i] == 'X')   ///// i tried to add colours with this but it sucked so i uncommented it.
			//{
			//	system("Color 04");
			//	cout << board[i];
			//	system("Color 07");
			//}
			//else if (board[i] == 'O')
			//{
			//	system("Color 02");
			//	cout << board[i];
			//	system("Color 07");
			//}
			//else
			//{
			//	cout << board[i];
			//}

			cout << " " << board[i];
			if (i < 2)
			{
				cout << " |";
			}
			else
			{
				cout << endl;
			}
		}
		cout << string(55, ' ');
		cout << "   |   |   " << endl;
		cout << string(55, ' ');
		cout << "---+---+---" << endl;
		cout << string(55, ' ');
		cout << "   |   |   " << endl;
		cout << string(55, ' ');
		for (int i = 3; i <= 5; i++) // print middle line
		{
			cout << " " << board[i];
			if (i < 5)
			{
				cout << " |";
			}
			else
			{
				cout << endl;
			}
		}
		cout << string(55, ' ');
		cout << "   |   |   " << endl;
		cout << string(55, ' ');
		cout << "---+---+---" << endl;
		cout << string(55, ' ');
		cout << "   |   |   " << endl;
		cout << string(55, ' ');
		for (int i = 6; i <= 8; i++) // print bottom line
		{
			cout << " " << board[i];
			if (i < 8)
			{
				cout << " |";
			}
			else
			{
				cout << endl;
			}

		}
		cout << string(55, ' ');
		cout << "   |   |   " << endl<< endl;
	}

	bool PlayerWin()									//a method to check if a player has won
	{
		int boardCheck[8][3] = { { 0,1,2 },				//Initialize a 2D array as a board checker containing the possible win combinations
		{ 3,4,5 },
		{ 6,7,8 },
		{ 0,3,6 },
		{ 1,4,7 },
		{ 2,5,8 },
		{ 0,4,8 },
		{ 2,4,6 } };

		for (int i = 0; i < 8; i++)						//Check possibilities against board
		{
			if ((board[boardCheck[i][0]] == board[boardCheck[i][1]]) && (board[boardCheck[i][1]] == board[boardCheck[i][2]]))
			{
				return true;							//Player won
			}
		}
		return false;									//No winner yet
	}

public:
	Game(char humanMark, AI ai, bool humanNext)			//Game constructor
		:humanMark(humanMark), ai(ai), humanNext(humanNext) //initiailze constructor variables.
	{
		aiMark = ai.aiMark;
		winnerFound = false;							//Initialize winnerFound to false;

		totalMoves = 0;									//Initialize total moves to 0 - used to verify if board filled

		for (int i = 0; i < 9; i++)						//Loop to initialize board by casting each i as char into board array
		{
			char aChar = '0' + (i+1);
			board[i] = aChar;
		}
	}

	void PlayGame()										//This plays the game
	{
		
		do												//The actual gameplay loop
		{
			if (humanNext)								//Human player
			{
				char selection; 
				bool validData = false;
				do
				{
					ClearScreen();
					PrintBoard();
					cout << string(25, ' ');
					cout << "It's your go! Select a valid spot to place an " << humanMark << " (1 to 9): ";
					cin >> selection;
					//validate if selection is 1,2,3,4,5,6,7,8,9
					if (selection == '1' || selection == '2' || selection == '3' || selection == '4' || selection == '5' || selection == '6' || selection == '7' || selection == '8' || selection == '9')
					{
						//Then convert selection to int, subtract 1, and validate if selection is an unchosen spot on the board:
						int selectionInt = selection - '0';
						selectionInt--;
						if (board[selectionInt] != 'X' && board[selectionInt] != 'O')
						{
							board[selectionInt] = humanMark;
							validData = true;
						}
					}
				} while (!validData);
			}
			else										//AI Player
			{ 
				int selection = -1;
				ClearScreen();
				PrintBoard();

				cout << string(25, ' ');
				cout << "The AI is thinking...";
				std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 4500 + 500));  //makes it look like the AI is thinking for 0.5-5s

				selection = ai.MakeMove(board);				//This is where the AI is called to choose a valid int on the board.
				board[selection] = aiMark;					//This is where selection is updated in board array.

				ClearScreen();
				PrintBoard();
				cout << string(25, ' ');
				cout << "The AI has made its choice!";
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));				//provides a 1 second delay to let user know 

			}

			if (humanNext)								//After player turn, switch player
			{
				humanNext = false;
			}
			else
			{
				humanNext = true;
			}

			if (PlayerWin())							//Checks to see if someone won
			{
				winnerFound = true;
			}

			totalMoves++;

		} while ((totalMoves <= 8) && (winnerFound == false));  //game loop breakout conditions

		ClearScreen();
		PrintBoard();

		if (totalMoves == 9 && winnerFound == true)				//if statement to determine who has won or if it was a tie.
		{
			if (!humanNext)
			{
				cout << string(25, ' ');
				cout << "Human has won!" << endl << endl;
			}
			else
				cout << string(25, ' ');
				cout << "The AI has won!" << endl << endl;
		}
		else if (totalMoves == 9)
		{
			cout << string(25, ' ');
			cout << "The game is a draw!" << endl << endl;
		}
		else
		{
			if (!humanNext)
			{
				cout << string(25, ' ');
				cout << "Human has won!" << endl << endl;
			}
			else
				cout << string(25, ' ');
				cout << "The AI has won!" << endl << endl;
		}
	
		cout << endl << string(25, ' ') << "Press any key to continue...";
		_getch();
		ClearScreen();

	}
};

/*-----MAIN PROGRAM-----*/
int main()
{
	char humanMark = '-';				//Temporary chars to initialize the Marks to use
	char aiMark = '-';
	bool humanNext = true;				//To determine if human goes first
	bool playAgain = true;			//To play or end the game (initialize to true) 

	ShowTitle();

	do									//This is the primary game loop													
	{
		ClearScreen();
		
		//First gather data:
		SetHumanMark(humanMark);
		SetAiMark(aiMark, humanMark);
		IsHumanNext(humanNext);

		//Then create a new AI player, and play the game:
		AI ai(aiMark, humanMark, humanNext);
		Game game(humanMark, ai, humanNext);
		game.PlayGame();
		
		//Find out if the user would like to play again:
		PlayAgain(playAgain);

	} while (playAgain);				//primary game loop end conditions


	//End the program:
	cout << string(15, '\n')
		<< "                                Thanks for playing Tim Andrew's Tic-Tac-Toe!" << endl << endl <<
		   "                                           Press any key to exit!" << endl <<
		   "                                                      ";
	_getch();

	return 0;
}

/*-----MAIN PROGRAM FUNCTIONS-----*/
void ShowTitle()								//Prints the main title
{
	//source:  http://patorjk.com/software/taag/#p=display&f=Larry%203D&t=Tim%20Andrew%27s%0ATic-Tac-Toe
	cout << endl;
	cout << endl;
	cout << "           ______                    ______              __                            __" << endl;
	cout << "          /\\__  _\\__                /\\  _  \\            /\\ \\                          /\\ \\" << endl;
	cout << "          \\/_/\\ \\/\\_\\    ___ ___    \\ \\ \\L\\ \\    ___    \\_\\ \\  _ __    __   __  __  __\\ \\/      ____" << endl;
	cout << "             \\ \\ \\/\\ \\ /' __` __`\\   \\ \\  __ \\ /' _ `\\  /'_` \\/\\`'__\\/'__`\\/\\ \\/\\ \\/\\ \\\\/      /',__\\" << endl;
	cout << "              \\ \\ \\ \\ \\/\\ \\/\\ \\/\\ \\   \\ \\ \\/\\ \\/\\ \\/\\ \\/\\ \\L\\ \\ \\ \\//\\  __/\\ \\ \\_/ \\_/ \\      /\\__, `\\" << endl;
	cout << "               \\ \\_\\ \\_\\ \\_\\ \\_\\ \\_\\   \\ \\_\\ \\_\\ \\_\\ \\_\\ \\___,_\\ \\_\\\\ \\____\\\\ \\___x___/'      \\/\\____/" << endl;
	cout << "                \\/_/\\/_/\\/_/\\/_/\\/_/    \\/_/\\/_/\\/_/\\/_/\\/__,_ /\\/_/ \\/____/ \\/__//__/         \\/___/" << endl;
	cout << endl;
	cout << endl;
	cout << "           ______                   ______                        ______" << endl;
	cout << "          /\\__  _\\__               /\\__  _\\                      /\\__  _\\" << endl;
	cout << "          \\/_/\\ \\/\\_\\    ___       \\/_/\\ \\/    __      ___       \\/_/\\ \\/   ___      __" << endl;
	cout << "             \\ \\ \\/\\ \\  /'___\\ _______\\ \\ \\  /'__`\\   /'___\\ _______\\ \\ \\  / __`\\  /'__`\\" << endl;
	cout << "              \\ \\ \\ \\ \\/\\ \\__//\\______\\\\ \\ \\/\\ \\L\\.\\_/\\ \\__//\\______\\\\ \\ \\/\\ \\L\\ \\/\\  __/" << endl;
	cout << "               \\ \\_\\ \\_\\ \\____\\/______/ \\ \\_\\ \\__/.\\_\\ \\____\\/______/ \\ \\_\\ \\____/\\ \\____\\" << endl;
	cout << "                \\/_/\\/_/\\/____/          \\/_/\\/__/\\/_/\\/____/          \\/_/\\/___/  \\/____/" << endl;
	cout << endl;
	cout << endl;
	cout << "                                            PRESS ANY KEY TO BEGIN" << endl;
	cout << "                                                        ";
	_getch();
}

void ClearScreen()								//clears the screen (security hole && OS specific (less portable) - but it works for now)
{
	system("cls"); 
}

void SetHumanMark(char &humanMark)				//player chooses their mark
{
	char ans = '-';								//local variable to handle various chars in this function

	if (humanMark != '-')						//On game reset, does player want to use the same mark?
	{
		while (ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N')
		{
			cout << string(15, '\n')
				<< "                        Would you like to continue using " << humanMark << " in the next game? (Y or N): ";
			cin >> ans;
			ClearScreen();
		}
		if (ans == 'y' || ans == 'Y')
		{
			ans = humanMark;
		}
		else
		{
			if (humanMark == 'X')
			{
				ans = 'O';
			}
			else
			{
				ans = 'X';
			}
		}
	}

	while (ans != 'x' && ans != 'X' && ans != 'o' && ans != 'O')	//Player selects mark on game start (is skipped if player already chose)
	{
		cout << string(15, '\n')
			<<"                                   What mark would you like to use? (X or O): ";
		cin >> ans;
		ClearScreen();
	}

	if (ans == 'x' || ans == 'X')
	{
		humanMark = 'X';
	}
	else
	{
		humanMark = 'O';
	}
}

void SetAiMark(char &aiMark, char &playerMark)			//Set the AI's mark.
{
	if (playerMark == 'X')
	{
		aiMark = 'O';
	}
	else
	{
		aiMark = 'X';
	}
}

void IsHumanNext(bool &humanNext)						//Find out if the player wants to play first or second
{
	char ans = '-';										//Local variable initialized to handle various chars in this function

	while (ans != '1' && ans != '2')
		{
			cout << string(15, '\n')
				<< "                                Would you like to go first or second? (1 or 2): ";
			cin >> ans;
			ClearScreen();
		}

	if (ans == '1')
		{
			humanNext = true;
		}
	else
		{
			humanNext = false;
		}
}

void PlayAgain(bool &playTheGame)						//function to determine if they player wants to play again.
{
	char ans = '-';

	while (ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N')
	{
		cout << string(15, '\n')
			<< "                                   Would you like to play again? (Y or N): ";
		cin >> ans;
		ClearScreen();
	}

	if (ans == 'y' || ans == 'Y')
	{
		playTheGame = true;
	}
	else
	{
		playTheGame = false;
	}
}