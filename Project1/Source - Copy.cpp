#include <iostream>
#include <string>
#include <conio.h>				// for _getch

using namespace std;

/*----PROTOTYPES-----*/
void ShowTitle();
void ClearScreen();	
void SetPlayerMark(char &playerMark);
void SetAiMark(char &aiMark, char &playerMark);
void HumanFirstOrSecond(bool &humanFirst);
void PlayTheGame(char playerMark, char aiMark, bool humanFirst, char &gameArray); // needs to be built
void PrintBoard(int board[][3]);  // needs to be reworked
void AILogic(int board[][3]); // needs to be built
void PlayAgain(bool &playTheGame);

/*-----MAIN PROGRAM-----*/
int main()
{
	bool playTheGame = true;	//To play or end the game
	bool humanFirst = true;		//To determine if human goes first
	char playerMark = '-';		//Temporary chars to initialize the Marks to use
	char aiMark = '-';

	ShowTitle();				//Title Screen

	do							//This is the primary game loop													
	{
		char gameArray[3][3] = { {'1','2','3'},
								 {'4','5','6'},
								 {'7','8','9'} }; // initialze/reset game array
		ClearScreen();
		
		//First gather data:
		SetPlayerMark(playerMark);
		SetAiMark(aiMark, playerMark);
		HumanFirstOrSecond(humanFirst);
		
		//Then play the game:
		PlayTheGame(playerMark, aiMark, humanFirst, gameArray[3][3]);

		//Find out if the user would like to play again:
		PlayAgain(playTheGame);

	} while (playTheGame);

	//End the program:
	cout << "Thanks for playing Tim Andrew's Tic-Tac-Toe! (Press any key to quit)" << endl;
	_getch();

	return 0;
}

/*-----PROGRAM FUNCTIONS-----*/
void ShowTitle()  //  prints the main title
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

void ClearScreen() //clears the screen (security hole && OS specific (less portable) - but it works for now)
{
	system("cls"); 
}

void SetPlayerMark(char &playerMark) //player chooses their mark
{
	char ans = '-';  //local variable to handle various chars in this function

	if (playerMark != '-') // See if player wants to use the same mark they previously used
	{
		while (ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N')
		{
			cout << "Would you like to continue using " << playerMark << " in the next game? (Y or N): ";
			cin >> ans;
			ClearScreen();
		}
		if (ans == 'y' || ans == 'Y')
		{
			ans = playerMark;
		}
		else
		{
			if (playerMark == 'X')
			{
				ans = 'O';
			}
			else
			{
				ans = 'X';
			}
		}
	}

	while (ans != 'x' && ans != 'X' && ans != 'o' && ans != 'O') //Player selects mark
	{
		cout << "What mark would you like to use? (X or O): ";
		cin >> ans;
		ClearScreen();
	}

	if (ans == 'x' || ans == 'X')
	{
		playerMark = 'X';
	}
	else
	{
		playerMark = 'O';
	}
}

void SetAiMark(char &aiMark, char &playerMark) //set the AI's mark.
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

void HumanFirstOrSecond(bool &humanFirst)  // find out if the player wants to play first or second.
{
	char ans = '-';  //local variable to handle various chars in this function

	while (ans != '1' && ans != '2')
		{
			cout << "Would you like to go first or second? (1 or 2): ";
			cin >> ans;
			ClearScreen();
		}

	if (ans == '1')
		{
			humanFirst = true;
		}
	else
		{
			humanFirst = false;
		}
}

void PlayTheGame(char playerMark, char aiMark, bool humanFirst, char &gameArray) //The Game 
{
	do
	{
		PrintBoard(gameArray);
		_getch();
	} while (//no one has won)
}

void PrintBoard(int board[][])  // needs to be reworked
{
	// possible print board: http://patorjk.com/software/taag/#p=display&f=Bigfig&t=%201%20%7C%202%20%7C%203%0A---%2B---%2B---%0A%20X%20%7C%20O%20%7C%206%0A---%2B---%2B---%0A%207%20%7C%208%20%7C%209
	//another possibiilty: http://patorjk.com/software/taag/#p=display&f=Bright&t=%201%20%7C%202%20%7C%203%0A---%2B---%2B---%0A%20X%20%7C%20O%20%7C%206%0A---%2B---%2B---%0A%207%20%7C%208%20%7C%209
	//another: http://patorjk.com/software/taag/#p=display&f=3x5&t=%201%20%7C%202%20%7C%203%0A---%2B---%2B---%0A%20X%20%7C%20O%20%7C%206%0A---%2B---%2B---%0A%207%20%7C%208%20%7C%209
	for (int i = 0; i <= 2; i++) // print top line
	{
		cout << moves[i];
		if (i < 2)
		{
			cout << "|";
		}
		else
		{
			cout << endl;
		}
	}
	cout << "-+-+-" << endl;

	for (int i = 3; i <= 5; i++) // print middle line
	{
		cout << moves[i];
		if (i < 5)
		{
			cout << "|";
		}
		else
		{
			cout << endl;
		}
	}
	cout << "-+-+-" << endl;
	for (int i = 6; i <= 8; i++) // print bottom line
	{
		cout << moves[i];
		if (i < 8)
		{
			cout << "|";
		}
		else
		{
			cout << endl;
		}
	}
}

void AILogic(int board[][])
{

}

void PlayAgain(bool &playTheGame)
{
	char ans = '-';

	while (ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N')
	{
		cout << "Would you like to play again? (Y or N): ";
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