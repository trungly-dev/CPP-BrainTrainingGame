#include "Player.h"
#include "Components.h"

#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

void registerName(Player *_player) {

	system("cls");

	drawALineMessageInFrame("   ", true, false, "center");
	drawALineMessageInFrame("TRAIN YOUR BRAIN", false, false, "center");
	drawALineMessageInFrame("   ", false, true, "center");
	drawALineMessageInFrame("   ", false, false, "center");
	drawALineMessageInFrame("Please enter your name ", false, false, "center");
	drawALineMessageInFrame("+-----------------------------+", false, false, "center");
	drawALineMessageInFrame("|                             |", false, false, "center");
	drawALineMessageInFrame("|                             |", false, false, "center");
	drawALineMessageInFrame("|                             |", false, false, "center");
	drawALineMessageInFrame("+-----------------------------+", false, false, "center");
	drawALineMessageInFrame("   ", false, false, "center");
	drawALineMessageInFrame("   ", false, false, "center");
	drawALineMessageInFrame("   ", false, false, "center");
	drawALineMessageInFrame("   ", false, true, "center");

	string name = "";
	do {
		moveCursor(10, 26);
		getline(cin, name); // allow user inputting the blank (" ") between first name and last name and store it. 
	} while (name == "" || name==" " || name == "  " || name == "   " || name == "    " || name == "     " || name == "      ");
	_player->setName(name);

	/*------Done Registering name---------------------------*/


}


void startPlay(Player *player) {

	do{

		system("cls");

		/*--- Draw box of Game's name in the top ------------------------*/
		drawALineMessageInFrame("   ", true, false, "center");
		drawALineMessageInFrame("-= BRAIN TRAINING GAME =-", false, false, "center");
		drawALineMessageInFrame("   ", false, true, "center");
		drawALineMessageInFrame("   ", false, false, "center");
		/*----------------------------------------------------*/


		 /*--- Countdown in starting ------------------------*/
		moveCursor(7, 0);
		updateStatusBar(player);
		 
		countDown(8, 0); 
		/*----------------------------------------------------*/
		
		/*--- Draw Main Playing frame ------------------------*/

		string message = "";
		int *challengeArray;
		challengeArray = createARandomArray(); // create a random challenge array from 1 to 9 (elimitate 0) to challenge player


		showMainPlayFrame(player, challengeArray); //draw the frame in user interface  
		
		int pointBeforePlaying = player->point; 

		int resultOneRound = playing(player, challengeArray);	// player are typing.



		switch (resultOneRound) {
		case 0: // complete finish 


			player->setLevel(player->getLevel() + 1);
			resultOneRound = -1;

			message = "WELL DONE, ";
			message = message + player->getName();
			message = message + "!";

			// Move cursor to row:8 column:0 and draw a frame with message in center
			showMessagesWithBigFrame(message, 8, 0);
			Sleep(1000);

			message = "You've just got ";
			moveCursor(14, 29); cout << message; 
			moveCursor(15, 34); cout << (player->point - pointBeforePlaying);
			Sleep(2000);

			message = "Your level now is up to ";
			message = message + to_string(player->getLevel());
			moveCursor(17, 23); cout << message;
			Sleep(2000);

			break;

		case 1: // Fail but enter to try again
			player->setChance(player->getChance() - 1);

			if (player->getChance() == 0)  // when player have not any chances to continue playing.
			{ 
				// Move cursor to row:8 column:0 and draw a frame with message in center
				showMessagesWithBigFrame("Unfortunately, Game is over! ", 8, 0);
				moveCursor(13, 50);
				Sleep(3000);
				break;
			}
			else {// when player has a chance to continue playing. 
				resultOneRound = -1;
			}
			break;

		case 2:  // when press ESC to end the game
			player->point = 0;
			player->setChance(0);
			break;
		}
		
	} while (player->getChance() != 0);


	 
	

}