#include <iostream>
#include"Player.h"

// override constructors!
Player::Player()  // default constructor
{	
	name = "Default_Player";
	level = 0;
	point = 0;
	chance = 0;
	rank = 0;

}
 
Player::Player(string _name) : name(_name) // initialisation list
{ 
	level = 0;
	point = 0;
	chance = 0;
	rank = 0;
}

Player::Player(string _name, int _level, int _point, int _chance, int _rank) : name{ _name }, level{ _level}, point { _point }, chance{ _chance }, rank { _rank }
{

}

// destructor
Player::~Player()
{

}

// methods

void Player::setName(string _name){
	name = _name;
}
void Player::setLevel(int _level) {
	level = _level;
}
void Player::setPoint(int _point) {
	point = _point;
}
void Player::setChance(int _chance) {
	chance = _chance;
}
void Player::setRank(int _rank) {
	rank = _rank;
}


string Player::getName() {
	return name;
}
int Player::getLevel() {
	return level;
}
int Player::getPoint() {
	return point;
}
int Player::getChance() {
	return chance;
}
int Player::getRank() {
	return rank;
}

void Player::displayAPlayer() // only for testing We should keep for improving in the future.
{
	cout << rank << "\t" << name << "\t" << point << "\t" << level << endl;
}


bool sortPlayerByPoint(const Player &P1, const Player &P2)
{
	return ((P1.point > P2.point) ? true : false);
};