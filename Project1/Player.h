#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

class Player
{
private:
	char playerChar;
	bool isComputer;
	int move;
public:
	void setPlayerChar(char c) {
		playerChar = c;
	}
	char getPlayerChar() {
		return playerChar;
	}
	void setComputer(bool c) {
		isComputer = c;
	}
	bool getComputer() {
		return isComputer;
	}
	void setMove(int s) {
		move = s;
	}
	int getMove() {
		return move;
	}
	Player() {
		playerChar = (char)48;
		isComputer = false;
		move = 0;
	}
};

#endif // !PLAYER_H
