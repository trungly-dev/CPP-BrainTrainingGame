#include <iostream>
#include <string>

using namespace std;

#ifndef PLAYER_H
#define PLAYER_H

class Player 
{
private: 
	string name;
	int level;
	int chance;
	int rank;

public:

	int point;

	// override constructors
	Player(); // default constructor
	Player(string _name);
	Player(string _name, int _level, int _point, int _chance, int _rank);

	// destructor
	~Player();

	//  setter
	void setName(string _name);
	void setLevel(int _level);
	void setPoint(int _point);
	void setChance(int _chance);
	void setRank(int _rank);

	//  getter
	string getName();
	int getLevel();
	int getPoint();
	int getChance();
	int getRank();

	// this Function is used only for testing We should keep for improving in the future.
	void displayAPlayer();


};


bool sortPlayerByPoint(const Player &P1, const Player &P2);
#endif
