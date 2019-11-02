#include <iostream>

using namespace std;

#ifndef MAINSCREEN_H
#define MAINSCREEN_H

class MainScreen
{
private:
	bool finished;
public:
	void update();
	void showManuOptions();
	bool introSreen();
	void howToPlayScreen();
	void playScreen();
	void recordScreen();
	void exit();

};


#endif // !MAINSCREEN_H

 