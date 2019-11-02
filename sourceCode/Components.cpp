#include "Components.h"
#include "Player.h"
#include "MyException.h"

#include <iostream>
#include <windows.h> // for Function: Sleep()
#include <conio.h> // for Function: _getch()
#include <fstream> // for Fuction: read()
#include <string> // for Fuction : getline(),  
#include <list>  // for LinkedList Players in Top Table

#include <time.h>  // for getting random number


#include <chrono> // for steady_clock::now() 
using namespace std::chrono; // for steady_clock::now()
using namespace std::literals::chrono_literals; // for steady_clock::now()

using namespace std;

void waitForRightKey(int rightKey) {

	int keyPress;

	while (true) {
		keyPress = _getch();
		if (keyPress == rightKey) { // when user presses ENTER
			break;
		}
	}
}

void moveCursor(int row, int column) {
	cout << "\033[" << row << ";" << column << "H";
}

bool displayFromFile(string path) {
	bool isGood = true;
	string lineData = ""; 

	ifstream read(path);
	try
	{
		if (read.is_open()) {
			while (getline(read, lineData)) {
				cout << lineData << endl;
			}
			read.close();
		}
		else{
			isGood = false;
			MyException myEx;
			throw myEx;
		}

	}
	catch (MyException ex )
	{
		moveCursor(4,0);

		drawALineMessageInFrame( "        ", true, false, "center");
		drawALineMessageInFrame(ex.what(), false, false, "center"); 
		string message = "File " + path + " was not found";
		drawALineMessageInFrame("---------------------------------------", false, false, "center");
		drawALineMessageInFrame(message, false, false, "center");
		 
		drawALineMessageInFrame("        ", false, false, "center");
		drawALineMessageInFrame("   ", true, false, "center");
		drawALineMessageInFrame("Try to put right path before starting the game.", false, false, "center");
		drawALineMessageInFrame("   ", false, true, "center"); 
		 
	}
	return isGood;
	 
}

void drawALineMessageInFrame(string message, bool topLine, bool bottomLine, string align) {
	const int LENGTH_OF_FRAME = 69;
	int i = 0;
	int sizeOfMessage = message.size();
	string strDrawLine = "";

	if (topLine) {
		string strDrawLine = "";
		for (i = 0; i<LENGTH_OF_FRAME; i++) {
			strDrawLine += "-";
		}
		strDrawLine = "+" + strDrawLine + "+";

		cout << strDrawLine << endl;
	}

	if (align == "center") {
		bool flag = true;
		for (i = sizeOfMessage; i < LENGTH_OF_FRAME; i++) {
			if (flag) {
				message = " " + message;
			}
			else {
				message = message + " ";
			}
			flag = !flag;
		}
	}
	else if (align == "left") {
		const int NUM_SPACE_LEFT = 6;
		for (i = 0; i < NUM_SPACE_LEFT; i++) {
			message = " " + message;
		}
		for (i = (NUM_SPACE_LEFT + sizeOfMessage); i < LENGTH_OF_FRAME; i++) {
			message = message + " ";
		}
	}

	message = "|" + message + "|";
	cout << message << endl;

	if (bottomLine) {
		string strDrawLine = "";
		for (i = 0; i<LENGTH_OF_FRAME; i++) {
			strDrawLine += "-";
		}
		strDrawLine = "+" + strDrawLine + "+";

		cout << strDrawLine << endl;
	}
}
void drawframePrintfromFile(string title, string path) {
	string lineData;
	ifstream read(path);
	try {

		if (read.is_open()) {
			drawALineMessageInFrame("   ", true, false, "center");
			drawALineMessageInFrame(title, false, false, "center");
			drawALineMessageInFrame("   ", false, true, "center");

			while (getline(read, lineData)) {
				drawALineMessageInFrame(lineData, false, false, "left");
			}
			read.close();

		}
		else {
			MyException MyEx;
			throw MyEx;
		}
	}
	catch (MyException ex) {

		moveCursor(4, 0);

		drawALineMessageInFrame("        ", true, false, "center");
		drawALineMessageInFrame(ex.what(), false, false, "center");
		drawALineMessageInFrame("----------------------------------------", false, false, "center");
		string message = "File " + path + " was not found";
		drawALineMessageInFrame(message, false, false, "center");

		drawALineMessageInFrame("        ", false, false, "center");
		drawALineMessageInFrame("   ", true, false, "center");
		drawALineMessageInFrame("Esc to back to the Menu", false, false, "center");
		drawALineMessageInFrame("   ", false, true, "center");
	}


	drawALineMessageInFrame("   ", false, false, "center");
	drawALineMessageInFrame("   ", true, false, "center");
	drawALineMessageInFrame("Esc to back to the Menu", false, false, "center");
	drawALineMessageInFrame("   ", false, true, "center"); 
	 

}


bool askReplayScreen() {

	moveCursor(5, 0);

	drawALineMessageInFrame("    ", true, false, "center");
	drawALineMessageInFrame("    ", false, false, "center");
	drawALineMessageInFrame("    ", false, false, "center");
	drawALineMessageInFrame("    ", false, false, "center");
	drawALineMessageInFrame("*****************************************", false, false, "center");
	drawALineMessageInFrame("*                                       *", false, false, "center");
	drawALineMessageInFrame("*                                       *", false, false, "center");
	drawALineMessageInFrame("*                                       *", false, false, "center");
	drawALineMessageInFrame("*****************************************", false, false, "center");
	drawALineMessageInFrame("    ", false, false, "center");
	drawALineMessageInFrame("    ", false, false, "center");
	drawALineMessageInFrame("    ", false, false, "center");
	drawALineMessageInFrame("    ", false, false, "center");
	drawALineMessageInFrame("    ", false, true, "center");


	moveCursor(12, 20);
	cout << "Do you want to try again? (Y/N)";
	moveCursor(12, 51);

	int userChoice;


	while (true) {
		userChoice = _getch();
		if (userChoice == 78     // when user presses 'N'
			|| userChoice == 110  // when user presses 'n'
			|| userChoice == 89  // when user presses 'Y'
			|| userChoice == 121  // when user presses 'y'
			)
		{
			break;
		}
	}

	if (userChoice == 89 || userChoice == 121)      // when user Press 'Y' or 'y'
		return true;
	else
		return false;
}


//-- Play screen elements methods -----------------------------------------------------------------


string getStatusBar(int level, int point, int chance) {
	string strStatus = "";

	strStatus = "LEVEL ";
	strStatus += to_string(level);
	strStatus += "                    ";
	strStatus += "POINT: ";
	strStatus += to_string(point);
	strStatus += "                    ";

	for (int i = 0; i< chance; i++) {
		strStatus += "O  ";
	}
	return strStatus;
}

void showMatric(int cellAddress[], int *cellValue, int level) {
	 
	if (level == 3){ 
		showMessagesWithBigFrame("More challenge! Now all number will be cover after 3.5 second", 8, 0);
		moveCursor(20, 0);
		drawALineMessageInFrame("  ", true, true, "center"); Sleep(5000); 
	}
	else if (level == 10)	{ 
		showMessagesWithBigFrame("More challenge! Now all number will be cover after 2.5 second", 8, 0); Sleep(5000);
		moveCursor(20, 0);
		drawALineMessageInFrame("  ", true, true, "center"); Sleep(5000);
	}
	else if (level == 15)	{ 
		showMessagesWithBigFrame("More challenge! Now all number will be cover after 1.5 second", 8, 0); Sleep(5000);
		moveCursor(20, 0);
		drawALineMessageInFrame("  ", true, true, "center"); Sleep(5000);
	}
	else if (level == 20)	{ 
		showMessagesWithBigFrame("More challenge! Now all number will be cover after 1 second", 8, 0); Sleep(5000);
		moveCursor(20, 0);
		drawALineMessageInFrame("  ", true, true, "center"); Sleep(5000);
	}
	else if (level == 25)	{ 
		showMessagesWithBigFrame("More challenge! Now all number will be cover after 0.5 second", 8, 0); Sleep(5000);
		moveCursor(20, 0);
		drawALineMessageInFrame("  ", true, true, "center"); Sleep(5000);
	}

	

	const int SIZE_OF_ROW = 5, SIZE_OF_COL = 5;

	int memoryArray[SIZE_OF_ROW][SIZE_OF_COL];
	int row = 0, column = 0;  


	//assigning 2D memoryArray[][] with all element is 0 except in cellAddress[i] will be given a value in cellValue[i];
	for (column = 0; column < SIZE_OF_COL; column++) {
		for (row = 0; row < SIZE_OF_ROW; row++) {
			memoryArray[column][row] = 0;
			if (row == cellAddress[column]) {
				memoryArray[column][row] = cellValue[column];
			}
		}
	}

	// show the table, 
	// If the element of memoryArray = 0 , this cell will empty.
	// and they will print out right the certain address a value of element of memoryArray

	moveCursor(9, 0);
	cout << "|             |             |             |             |             |" << endl;
	for (row = 0; row < SIZE_OF_ROW; row++) {
		for (column = 0; column < SIZE_OF_COL; column++) {
			if (memoryArray[column][row])
				cout << "|      " << memoryArray[column][row] << "      ";
			else
				cout << "|      " << " " << "      ";

			if (column == SIZE_OF_COL - 1) {
				cout << "|" << endl;
				cout << "|             |             |             |             |             |" << endl;
			}
		}
	}


	// When Level < 3, no cover.
	// 5 =< Level < 10,  the Challenge Array will be covered after  3.5s
	// 10 =< Level < 15,  the Challenge Array will be covered after 2.5s
	// 15 =< Level < 20,  the Challenge Array will be covered after 1.5s
	// 20 =< Level < 25,  the Challenge Array will be covered after 1s
	// when Level >= 25,  the Challenge Array will be covered after 0.5s

	string message="";
	if (level >= 3) {
		moveCursor(20, 0);
		if (level < 10)		 { drawALineMessageInFrame("Number will be covered after 3.5 second!", true, true, "center");  Sleep(3500); }
		else if (level < 15) { drawALineMessageInFrame("Number will be covered after 2.5 second!", true, true, "center");  Sleep(2500); }
		else if (level < 20) { drawALineMessageInFrame("Number will be covered after 1.5 second!", true, true, "center"); Sleep(1500); }
		else if (level < 25) { drawALineMessageInFrame("Number will be covered after 1 second!", true, true, "center"); Sleep(1000); }
		else				 { drawALineMessageInFrame("Number will be covered after 0.5 second!", true, true, "center"); Sleep(500); }
		
		moveCursor(10, 0); 
		
		for (row = 0; row < SIZE_OF_ROW; row++) {
			for (column = 0; column < SIZE_OF_COL; column++) {
				if (memoryArray[column][row])
					cout << "|*************";
				else
					cout << "|      " << " " << "      ";

				if (column == SIZE_OF_COL - 1) {
					cout << "|" << endl;
					cout << "|             |             |             |             |             |" << endl;
				}
			}
		}

	}

}

int * createARandomArray() {
	int* arrayPointer = new int[5]; 
	int randNumber = 0;
	
	// build a random arrays for arrayPointer from 1 to 9 (elimitate 0)
	srand((int)time(0));
	for (int i = 0; i < 5; i++) {
		randNumber = rand() % 10;
		if (randNumber == 0) {
			randNumber = 1;
		}
		arrayPointer[i] = randNumber;
	}

	return arrayPointer;
}


void showMessagesWithBigFrame(string message, int cursorX, int cursorY) {

	moveCursor(cursorX, cursorY);
	drawALineMessageInFrame("   ", true, false, "center");
	drawALineMessageInFrame("   ", false, false, "center");
	drawALineMessageInFrame("   ", false, false, "center");
	drawALineMessageInFrame("   ", false, false, "center");
	drawALineMessageInFrame(message, false, false, "center");
	drawALineMessageInFrame("   ", false, false, "center");
	drawALineMessageInFrame("   ", false, false, "center");
	drawALineMessageInFrame("   ", false, false, "center");
	drawALineMessageInFrame("   ", false, false, "center");
	drawALineMessageInFrame("   ", false, false, "center");
	drawALineMessageInFrame("   ", false, true, "center");

}

void updateStatusBar(Player *playerPtr) {

	//string statusBar = getStatusBar(player->getLevel(), 30, player->getChance()); //level 1, time 0:30,  life:3
	drawALineMessageInFrame("Level:                   Point:                                 ", false, true, "center");
	moveCursor(7, 12); 	cout << playerPtr->getLevel();
	moveCursor(7, 37); 	cout << playerPtr->point;
	for (int i = 0; i < playerPtr->getChance(); i++) {
		moveCursor(7, 60 +i*2 ); 	cout << "O";
	} 

}
void showMainPlayFrame(Player *player, int *challengeArray) { 
	moveCursor(8, 0); 
	const int SIZE_OF_LEVEL = 5;
	const int CURSOR_DISTANCE = 10;

	int index = 0, jumpStep = 6;
	 
	int cellAddress[SIZE_OF_LEVEL] = { 0 };

	// build a random arrays for cellAddress from 1 to 4 (elimitate 0)
	srand((int)time(0));
	int randNumber = 0;
	for (index = 0; index < SIZE_OF_LEVEL; index++) {
		randNumber = rand() % SIZE_OF_LEVEL;
		if (randNumber == 0) {
			randNumber = 1;
		}
		cellAddress[index] = randNumber;
	}
	 
	moveCursor(9, 0);
	showMatric(cellAddress, challengeArray, player->getLevel());

	drawALineMessageInFrame("    >_      |     >_      |     >_      |     >_      |     >_     ", true, true, "center");
	
} 


int askMessageChoosing(string message, bool back, bool next, int cursor_row, int cursor_column ) {
	if (next) {
		if (back) {
			drawALineMessageInFrame("   ", true, false, "center");
			drawALineMessageInFrame("   ", false, false, "center");
			drawALineMessageInFrame("   ", false, false, "center");
			drawALineMessageInFrame("   ", false, false, "center");
			drawALineMessageInFrame(message, false, false, "center");
			drawALineMessageInFrame("   ", false, false, "center");
			drawALineMessageInFrame("   ", false, false, "center");
			drawALineMessageInFrame("   ", false, false, "center");
			drawALineMessageInFrame("   ", false, false, "center");
			drawALineMessageInFrame("   ", false, false, "center");
			drawALineMessageInFrame("   ", false, false, "center");
			drawALineMessageInFrame("   ", true, false, "center");

			drawALineMessageInFrame("ESC = Back     |    ENTER = try again", false, false, "center");

			drawALineMessageInFrame("   ", false, true, "center");  
		}
		else {
			drawALineMessageInFrame("   ", true, false, "center");
			drawALineMessageInFrame("   ", false, false, "center");
			drawALineMessageInFrame("   ", false, false, "center");
			drawALineMessageInFrame("   ", false, false, "center");

			drawALineMessageInFrame(message, false, false, "center");
			drawALineMessageInFrame("   ", false, false, "center");
			drawALineMessageInFrame("   ", false, false, "center");
			drawALineMessageInFrame("   ", false, false, "center");
			drawALineMessageInFrame("   ", false, false, "center");
			drawALineMessageInFrame("   ", false, false, "center");
			drawALineMessageInFrame("   ", true, false, "center");

			drawALineMessageInFrame("ENTER = Continue", false, false, "center");

			drawALineMessageInFrame("   ", false, false, "center");
			drawALineMessageInFrame("   ", false, true, "center");
		}
	}

	moveCursor(cursor_row, cursor_column);
	int keyPress = 0;

	while (1) {
		keyPress = _getch();
		if (keyPress == 27) { // when user presses ESC
			break;
		}
		if (keyPress == 13) { // when user presses ENTER
			break;
		}
	}

	return keyPress;
}

void countDown(int cursor_row, int cursor_column){

	// Move cursor to row:8 column:0 and draw a frame with message in center
	showMessagesWithBigFrame("ARE YOU READY? 3 ", cursor_row, cursor_column); moveCursor(cursor_row+5, cursor_column+44);
	moveCursor(20, 0);
	drawALineMessageInFrame("    >_      |     >_      |     >_      |     >_      |     >_     ", true, true, "center");

	Sleep(300); moveCursor(cursor_row + 5, cursor_column + 45); cout << ".";
	Sleep(300); moveCursor(cursor_row + 5, cursor_column + 46); cout << ".";
	Sleep(300); moveCursor(cursor_row + 5, cursor_column + 47); cout << ".";

	Sleep(300); moveCursor(cursor_row + 5, cursor_column + 43); cout << "2     "; moveCursor(cursor_row + 5, cursor_column + 44);
	Sleep(300); moveCursor(cursor_row + 5, cursor_column + 45); cout << ".";
	Sleep(300); moveCursor(cursor_row + 5, cursor_column + 46); cout << ".";
	Sleep(300); moveCursor(cursor_row + 5, cursor_column + 47); cout << ".";

	Sleep(300); moveCursor(cursor_row + 5, cursor_column + 43); cout << "1     "; moveCursor(cursor_row + 5, cursor_column + 44);
	Sleep(300); moveCursor(cursor_row + 5, cursor_column + 45); cout << ".";
	Sleep(300); moveCursor(cursor_row + 5, cursor_column + 46); cout << ".";
	Sleep(300); moveCursor(cursor_row + 5, cursor_column + 47); cout << ".";
	Sleep(500);
	showMessagesWithBigFrame(" ... GO ... ", cursor_row, cursor_column); moveCursor(cursor_row + 5, cursor_column+42);
	Sleep(500);
}


int playing(Player *player, int * challengeArray) {

	int keyPress = 0;
	int jumpStep = 8;
	const int CURSOR_DISTANCE = 14;

	int playerType[5] = { 0 };
	char letter;
	int statusPlayer = 0;

	// getting the start time;
	auto start = steady_clock::now();

	for (int i = 0; i < 5; i++) { // from 1 - 5
		moveCursor(21, jumpStep);


		do {
			keyPress = _getch();
		} while (!(keyPress > 48 && keyPress < 58));
		//compare keyPress variable would be accepted only pressing number 1-9 button keys.

		playerType[i] = keyPress - 48; // convert to number 1 

		if (playerType[i] == challengeArray[i]) { 

			cout << playerType[i];
			jumpStep += CURSOR_DISTANCE;
		}
		else {
			//show Message choosing back or continue
			if (player->getChance() > 1) {
				cout << "x";
				moveCursor(8, 0);
				keyPress = askMessageChoosing("Oops! you failed...", true, true ,13,46); 

				if (keyPress == 27) { //   Esc to end Game
					statusPlayer = 2;
					break;
				}
				else if (keyPress == 13) { // Fail but Enter to continue
					statusPlayer = 1;
					break;
				}
			}
			else {
				statusPlayer = 1;
				break;
			}

		}

	}

	// getting the finish time;

	const int MULTIBLE_NUMBER = 1000000;
	int bonus = 0;
	auto end = steady_clock::now();
	duration<double, std::milli> distanceTime = end - start;
	if (statusPlayer!=1) {
		bonus = (int)(MULTIBLE_NUMBER * player->getLevel() / distanceTime.count());
		player->point = player->point + bonus;
	}
	

	return statusPlayer; //  = 0 : Complete finish

}

void analysisShow(Player *playerPtr) {

	string message;
	system("cls");
	drawALineMessageInFrame("   ", true, false, "center");
	drawALineMessageInFrame("ADVICE & ANALYSIS", false, false, "center");
	drawALineMessageInFrame("   ", false, true, "center");

	drawALineMessageInFrame("   ", false, false, "center");
	drawALineMessageInFrame("   ", false, false, "center");

	message = "Fantastic ";
	message += playerPtr->getName();
	message += " !";
	drawALineMessageInFrame(message, false, false, "center");

	message = "Level: " + to_string(playerPtr->getLevel());
	message += ", Point: " + to_string(playerPtr->getPoint());
	drawALineMessageInFrame(message, false, false, "center");
	

	if (playerPtr->getLevel() < 15) {
		drawALineMessageInFrame("You have a pretty good memory.", false, false, "center");
		drawALineMessageInFrame("There are about 45% of the world's population", false, false, "center");
		drawALineMessageInFrame("is practicing every day to maintain brainpower.", false, false, "center");
		drawALineMessageInFrame("Keep practicing every day intensively, ", false, false, "center");
		drawALineMessageInFrame("you will have a more satisfying life!", false, false, "center");
	}
	else if (playerPtr->getLevel() < 20) {
		drawALineMessageInFrame("Wow! You are in 18% of people in the world ", false, false, "center");
		drawALineMessageInFrame("who use from 2% to 5% of the brain's power.", false, false, "center");
		drawALineMessageInFrame("Please practice regularly to improve ", false, false, "center");
		drawALineMessageInFrame("your ability to remember!", false, false, "center");
	}

	else if (playerPtr->getLevel() < 25) {
		drawALineMessageInFrame("Congratulations!", false, false, "center");
		drawALineMessageInFrame("You are one of the top of 2% of people in the world ", false, false, "center");
		drawALineMessageInFrame("Keep practicing regularly to keep your good form!", false, false, "center"); 
	}

	drawALineMessageInFrame("   ", false, false, "center");
	drawALineMessageInFrame("   ", false, false, "center");
	drawALineMessageInFrame("   ", true, false, "center");
	drawALineMessageInFrame("Esc to close.", false, false, "center");
	drawALineMessageInFrame("   ", false, true, "center");

	waitForRightKey(27);	 // waiting until press 'Esc' (with Ascii value is 27)

}