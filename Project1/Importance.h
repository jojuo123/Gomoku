#ifndef _IMPORTANCE_H
#define _IMPORTANCE_H

#include <Windows.h>
#include "support.h"
#include "GamePlay.h"
#include "Player.h"
#include "Status.h"
#include "SaveFile.h"
#include "setting.h"
#include "Statistic.h"
#include "Computer.h"

class Variables
{
public:
	COORD cur;
	Setting st;
	Computer computer;
	GamePlay gp;
	Player player[2];
	Status status;
	Statistic statis;
	bool isWin;
	bool isDraw;
	int currentPlayer;
	bool resumepvp, resumepvc;
	int n, a, b, colorGrid, color1, color2;
	bool sound;

	Variables()
	{
		isWin = false;
		isDraw = false;
		resumepvp = false;
		resumepvc = false;
	}
};

#endif // !_IMPORTANCE_H
