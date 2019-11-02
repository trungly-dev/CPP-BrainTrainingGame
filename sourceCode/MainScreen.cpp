#include "MainScreen.h"
#include "Components.h"
#include "PlayScreen.h"
#include "Player.h"
#include "MyException.h"

#include <list>  // for LinkedList Players in Top Table
#include <windows.h> // for Function: Sleep()
#include <conio.h> // for Function: _getch()
#include <fstream> // for Fuction: read()
#include <string> // for Fuction : getline(),  


void MainScreen::update()
{
	finished = false;

	// Checking If the program cannot open these files: introScreen.txt, it will stop here.	 
	if (!introSreen()) {
		finished = true;
	}

	while (!finished)
	{
		system("cls");
		showManuOptions();
		int userChoice;
		 

		while (true) {
			userChoice = _getch();
			if (userChoice == 49     // when user presses '1'
				|| userChoice == 50  // when user presses '2'
				|| userChoice == 51  // when user presses '3'
				|| userChoice == 52  // when user presses '4'
				|| userChoice == 53  // when user presses '5' 
				)
			{ 
				break;
			}
		}

		if (userChoice == 49)      // when user presses '1'
			introSreen();
		else if (userChoice == 50)  // when user presses '2'
			howToPlayScreen();
		else if (userChoice == 51)  // when user presses '3'
			playScreen();
		else if (userChoice == 52)  // when user presses '4'
			recordScreen();
		else {  // when user presses '5'
			exit();
		}
	}
}

void MainScreen::showManuOptions()
{
	drawALineMessageInFrame("   ", true, false, "center");
	drawALineMessageInFrame("MENU", false, false, "center");
	drawALineMessageInFrame("   ", false, true, "center");
	drawALineMessageInFrame("   ", false, false, "center");
	drawALineMessageInFrame("1. Introduction Screen.", false, false, "left");
	drawALineMessageInFrame("   ", false, false, "center");
	drawALineMessageInFrame("2. How to play.", false, false, "left"); 
	drawALineMessageInFrame("   ", false, false, "center");
	drawALineMessageInFrame("3. Play now.", false, false, "left");
	drawALineMessageInFrame("   ", false, false, "center");
	drawALineMessageInFrame("4. Top Player Table.", false, false, "left");
	drawALineMessageInFrame("   ", false, false, "center");
	drawALineMessageInFrame("5. Exit.", false, false, "left");
	drawALineMessageInFrame("   ", false, false, "center");
	drawALineMessageInFrame("   ", true, false, "center");
	drawALineMessageInFrame("Enter in your choice (1-5) >> ", false, false, "center");
	drawALineMessageInFrame("   ", false, true, "center");

	moveCursor(19, 52);
}

bool MainScreen::introSreen()
{
	bool isGood = true;
	system("cls");
	if (displayFromFile("introScreen.txt")) {
		moveCursor(20, 66);
	}
	else {
		moveCursor(12, 60);
		isGood = false;
	}
	waitForRightKey(13);	 // waiting until press 'Enter' (with Ascii value is 13)

	return isGood;
}

void MainScreen::howToPlayScreen()
{
	system("cls"); 
	drawframePrintfromFile("How To Play","howToPlay.txt");
	moveCursor(3, 43);
	waitForRightKey(27); // waiting until press 'Esc'(with Ascii value is 27)

}

void MainScreen::playScreen()
{
	Player *playerPtr = new Player{ "Default_Name", 1, 0, 3, 0 };



	/*----- Checking the Top Table File Exist ---------
	------- If topFile.txt not exist Program will stop and move out to the menu
	---------------------------------------------------*/
	registerName(playerPtr);

	bool replay = false;
	do {
		playerPtr->setChance(3);
		playerPtr->point = 0;
		playerPtr->setLevel(1);

		/*---------------------------------------------------------------*/
		/*----------------                             ------------------*/
		startPlay(playerPtr);  // PLAYING HERE         ------------------*/
		/*----------------                             ------------------*/ 
		/*---------------------------------------------------------------*/

		replay = askReplayScreen();



	} while (replay);


	//************************* write Achievement of the Player to Top Table**************************************

	const string TOP_FILE_PATH = "topTable.txt";

	list<Player> playerList;
	Player playerTmp;

	string lineData, s1 = "", s2 = "", s3 = "", s4 = "";

	int i = 0, flag = 0;

	ifstream read(TOP_FILE_PATH);

	try {
		if (read.is_open()) {
			while (getline(read, lineData)) {
				for (int i = 0; i < lineData.size(); i++) {
					if (lineData[i] == 9) {   // number 9 is ascii value of a TAB
						flag++;
					}
					else {
						if (flag == 0) {    //get Rank
							s1 = s1 + lineData[i];
						}
						else if (flag == 1) {    // get Name
							s2 = s2 + lineData[i];
						}
						else if (flag == 2) {    // get Point
							s3 = s3 + lineData[i];
						}
						else {   //  get level
							s4 = s4 + lineData[i];
						}
					}
				}

				playerTmp.setRank(atoi(s1.c_str()));
				playerTmp.setName(s2);
				playerTmp.setPoint(atoi(s3.c_str()));
				playerTmp.setLevel(atoi(s4.c_str()));

				playerList.push_front(playerTmp);

				s1 = s2 = s3 = s4 = "";
				flag = 0;

			}
			read.close();
		}
		else {
			MyException MyEx;
			throw MyEx;
		}

	}
	catch( MyException ex){

		moveCursor(4, 0);

		drawALineMessageInFrame("        ", true, false, "center");
		drawALineMessageInFrame(ex.what(), false, false, "center");
		string message = "File " + TOP_FILE_PATH + " was not found";
		drawALineMessageInFrame(message, false, false, "center");

		drawALineMessageInFrame("        ", false, false, "center");
		drawALineMessageInFrame("   ", true, false, "center");
		drawALineMessageInFrame("Esc to continue.", false, false, "center");
		drawALineMessageInFrame("   ", false, true, "center");
	}
	 

	playerList.push_front(*playerPtr);
	playerList.sort(sortPlayerByPoint);

	int rankInOrder = 1;
	for (list<Player>::iterator it = playerList.begin();
		it != playerList.end();
		it++)
	{	
		it->setRank(rankInOrder);
		rankInOrder++;
		
	}

	//----- write to file  ------------------------
	ofstream fileOutput(TOP_FILE_PATH);
	try {
		if (fileOutput.fail())
		{
			MyException MyEx;
			throw MyEx;
		}
		else {

			for (list<Player>::iterator it = playerList.begin();
				it != playerList.end();
				it++)
			{
				fileOutput << it->getRank() << "\t";
				fileOutput << it->getName() << "\t";
				fileOutput << it->point << "\t";
				fileOutput << it->getLevel() << endl;
			}
			fileOutput.close();
		}

	}
	catch (MyException ex){

		moveCursor(4, 0);

		drawALineMessageInFrame("        ", true, false, "center");
		drawALineMessageInFrame(ex.what(), false, false, "center");
		string message = "File " + TOP_FILE_PATH + " was not found";
		drawALineMessageInFrame(message, false, false, "center");

		drawALineMessageInFrame("        ", false, false, "center");
		drawALineMessageInFrame("   ", true, false, "center");
		drawALineMessageInFrame("Enter to continue.", false, false, "center");
		drawALineMessageInFrame("   ", false, true, "center");
	}
	// ********** End of write Achievement of the Player to Top Table *******************************
	 
	analysisShow(playerPtr);

	delete playerPtr;

	 
}

void MainScreen::recordScreen()
{
	system("cls"); 

	list<Player> playerList;
	Player playerTmp;

	string lineData, s1="", s2="", s3="", s4="";
	string topfilePath = "topTable.txt";
	ifstream read(topfilePath);

	int i = 0, flag=0;  

	try {
		if (read.is_open()) {
			while (getline(read, lineData)) { // read each line in file topTable.txt as a set of data of a Player.
				for (int i = 0; i < lineData.size(); i++) {
					if (lineData[i] == 9) {   // number 9 is ascii value of a TAB
						flag++;
					}
					else {
						if (flag == 0) {    //get Rank
							s1 = s1 + lineData[i];
						}
						else if (flag == 1) {    // get Name
							s2 = s2 + lineData[i];
						}
						else if (flag == 2) {    // get point
							s3 = s3 + lineData[i];
						}
						else if (flag == 3) {   //  get level
							s4 = s4 + lineData[i];
						}
					}
				}

				playerTmp.setRank(atoi(s1.c_str()));
				playerTmp.setName(s2);
				playerTmp.setPoint(atoi(s3.c_str()));
				playerTmp.setLevel(atoi(s4.c_str()));

				//put all data of this Player to the Linked List 
				playerList.push_front(playerTmp);

				//reset all temporary variables
				s1 = s2 = s3 = s4 = "";
				flag = 0;

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
		string message = "File " + topfilePath + " was not found";
		drawALineMessageInFrame(message, false, false, "center");

		drawALineMessageInFrame("        ", false, false, "center");
		drawALineMessageInFrame("   ", true, false, "center");
		drawALineMessageInFrame("Enter to continue.", false, false, "center");
		drawALineMessageInFrame("   ", false, true, "center");
	}
	 
	// sort the List by Point of Players.
	playerList.sort(sortPlayerByPoint);
	

	drawALineMessageInFrame("   ", true, false, "center");
	drawALineMessageInFrame("Top Players Table", false, false, "center");
	drawALineMessageInFrame("   ", false, true, "center");
	drawALineMessageInFrame("   ", false, false, "center");

	string printALine = "       Rank    Name          Point ";
	drawALineMessageInFrame(printALine, false, false, "left");
	
	printALine = "      -------------------------------------------------";
	drawALineMessageInFrame(printALine, false, false, "left");

	int rowNum = 0; 
	for (list<Player>::iterator it = playerList.begin();
		it != playerList.end();
		it++)
	{

		if (rowNum < 16) {

			moveCursor(10 + rowNum - 1, 0);  drawALineMessageInFrame("   ", false, false, "center");
			moveCursor(10 + rowNum, 0);  drawALineMessageInFrame("   ", false, false, "center");
			moveCursor(10 + rowNum, 15);  cout << it->getRank() << ".";
			moveCursor(10 + rowNum, 23); cout << it->getName();
			moveCursor(10 + rowNum, 37); cout << it->getPoint();

			int starNum = it->getLevel() / 5 + 1;


			moveCursor(10 + rowNum, 49);
			if (starNum <= 5) {
				for (i = 0; i < starNum; i++) {
					cout << "* ";
				}
			}
			else {
				cout << "-= MASTER =-";
			}
			rowNum += 2;
		}
		
	}
	 

	moveCursor(10 + rowNum-1, 0);  

	drawALineMessageInFrame("   ", false, false, "center");	 
	drawALineMessageInFrame("   ", true, false, "center");
	drawALineMessageInFrame("Esc to back to the Menu", false, false, "center");
	drawALineMessageInFrame("   ", false, true, "center");
	moveCursor(3, 47);

	waitForRightKey(27); // waiting until press 'Esc'(with Ascii value is 27)

}
 
void MainScreen::exit()
{
	system("cls");
	moveCursor(5,0);
	drawALineMessageInFrame("   ", true, false, "center");
	drawALineMessageInFrame("     ", false, false, "center");
	drawALineMessageInFrame("     ", false, false, "center");
	drawALineMessageInFrame("THANK YOU!", false, false, "center");
	drawALineMessageInFrame("_____________________________________________", false, false, "center");
	drawALineMessageInFrame("     ", false, false, "center");
	drawALineMessageInFrame("Hope you have a enjoy time this in game!...", false, false, "center");
	drawALineMessageInFrame("     ", false, false, "center");
	drawALineMessageInFrame("     ", false, false, "center");
	drawALineMessageInFrame("   ", false, true, "center");
	moveCursor(12, 59);
	Sleep(3000);
	finished = true;
}
