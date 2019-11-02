#include <iostream>
#include <string>
#include <list>
#include "Player.h"

using namespace std;

#ifndef COMPONENTS_H
#define COMPONENTS_H
  


void waitForRightKey(int rightKey);

void moveCursor(int row, int column);

bool displayFromFile(string path);

void drawALineMessageInFrame(string message, bool topLine, bool bottomLine, string align);
void drawframePrintfromFile(string title, string path);
 
bool askReplayScreen();


//-- Play screen elements methods -----------------------------------------------------------------


string getStatusBar(int level, int time, int life);

void showMatric(int cellAddress[], int *cellValue, int level);

int *createARandomArray();

void showMessagesWithBigFrame(string message, int cursorX, int cursorY);

void updateStatusBar(Player *player);


void showMainPlayFrame(Player *player, int *challengeArray);


int askMessageChoosing(string message, bool back, bool next, int cursor_row, int cursor_column);
void countDown(int cursor_row, int cursor_column);
int playing(Player *player, int * challengeArray);

void analysisShow(Player *playerPtr);
 
#endif // !COMPONENTS_H
