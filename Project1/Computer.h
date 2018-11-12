#ifndef COMPUTER_H
#define COMPUTER_H

#include <algorithm>
#include <Windows.h>
#include <vector>
#include "GamePlay.h"
#include <climits>

extern const int MAX_VAL;
extern const int MIN_VAL;

class Computer
{
private:
	int level;
public:
	void setLevel(int a) {
		if (a >= 1 && a <= 3) level = a;
		else level = 1;
	}
	int getLevel() {
		return level;
	}
	COORD nextMove(GamePlay & gp);
	//currentPlayer = 1 => computer => get max
	int minimax(GamePlay & gp, int depth, int currentPlayer, int x, int y, int alpha, int beta);
	int evaluation(GamePlay & gp);
	bool PlayArea(GamePlay & gp, int x, int y);
	int Depth(int);
	Computer()
	{
		level = 1;
	}
};

#endif // !COMPUTER_H
