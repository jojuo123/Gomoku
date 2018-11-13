#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include <iostream>
#include "support.h"
#include "GamePlay.h"
#include "Player.h"
#include "Status.h"
#include "SaveFile.h"
#include "setting.h"
#include "Statistic.h"
#include "Computer.h"
#include <string>
#include <map>
#include <mmsystem.h>
#include <mciapi.h>
#include "Importance.h"

#pragma comment(lib, "winmm.lib")
/*
COORD cur;
Setting st;
Computer computer;
GamePlay gp;
Player player[2];
Status status;
Statistic statis;
bool isWin = false;
bool isDraw = false;
int currentPlayer;
bool resumepvp = false;
bool resumepvc = false;
int n, a, b, colorGrid, color1, color2; 
bool sound; 
*/

void play(bool, bool, Variables &V);
void SaveFile(Variables &V);
void LoadFile(Variables &V);
void settingMenu(Variables &V);
void SaveSetting(int, int, int, bool, int, int, int, Variables &V);
void StatisticMenu(Variables &V);
void pvcMenu(Variables &V);

void Message(string str)
{
	gotoXY(5, 9);
	cout << str;
	Sleep(1000);
	gotoXY(5, 9);
	printf("                                                                                                     ");
}

void banner()
{
	gotoXY(0, 0);
	TextColor(3);
	printf("Gomoku Gaming v6.1.99\n");
	printf("[F1] Resume PvP game\t");
	printf("[F2] Resume PvC game\n");
	printf("[F3] New Play Game PvP\t");
	printf("[F4] New Play Game PvC\n");
	printf("[F5] Settings\t\t");
	printf("[F6] Save game\n");
	printf("[F7] Load save game\t");
	printf("[F8] Statistic\n");
	printf("[F9] Exit");
}

void congrat(int no)
{
	setcursor(false, 0);
	COORD tmp = { 115, 12 };
	clearRightSide();
	// no = 0 P1, 1 P2, 2 Com
	if (no == 0)
	{
		for (int i = 0; i < 3; i++)
		{
			COORD tmp = { 115, 12 };
			for (int j = 0; j < 20; j++)
			{
				gotoXY(tmp);
				printf("PLAYER 1 WIN               PLAYER 1 WIN");
				tmp.Y++;
			}
			Sleep(1000);
			clearRightSide();
		}
	}
	if (no == 1)
	{
		for (int i = 0; i < 3; i++)
		{
			COORD tmp = { 115, 12 };
			for (int j = 0; j < 20; j++)
			{
				gotoXY(tmp);
				printf("PLAYER 2 WIN               PLAYER 2 WIN");
				tmp.Y++;
			}
			Sleep(1000);
			clearRightSide();
		}
	}
	if (no == 2)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				COORD tmp = { 115, 12 };
				gotoXY(tmp);
				printf("COMPUTER WIN               COMPUTER WIN");
				tmp.Y++;
			}
			Sleep(1000);
			clearRightSide();
		}
	}
	if (no == 3)
	{
		for (int i = 0; i < 3; i++)
		{
			COORD tmp = { 115, 12 };
			for (int j = 0; j < 20; j++)
			{
				gotoXY(tmp);
				printf("DRAW GAME                   DRAW GAME");
				tmp.Y++;
			}
			Sleep(1000);
			clearRightSide();
		}
	}
	clearRightSide();
}

void Load(GamePlay gp, Variables &V)
{
	for (int i = 0; i<gp.getSize(); i++)
		for (int j = 0; j < gp.getSize(); j++) {
			int tmp = gp.get(i, j); 
			gotoXY(toXconsole(i), toYconsole(j));
			if (tmp == 0) TextColor(V.st.getColorCodeChar1()); 
			if (tmp == 1) TextColor(V.st.getColorCodeChar2());
			if (tmp >= 0) printf("%c", V.player[tmp].getPlayerChar());
			if (tmp < 0) printf(" ");
		}
}

void init(bool isNew, bool comp, Variables &V)
{
	setcursor(true, 0);
	if (!comp)
	{
		V.cur = { 2, 11 };
		gotoXY(V.cur);
		V.player[0].setComputer(false);
		V.player[1].setComputer(false);
		if (!isNew)
		{
			if (!V.resumepvp) {
				V.gp.clear();
				V.currentPlayer = 0;
				V.status.setIsPlay(true);
				V.player[0].setMove(0);
				V.player[1].setMove(0);
				V.gp.setCount(0);
			}
			else {
				V.currentPlayer = V.gp.getCurrent();
				V.status.setIsPlay(true);
			}
		}

		if (isNew) 
		{
			V.gp.clear();
			V.currentPlayer = 0;
			V.status.setIsPlay(true);
			V.player[0].setMove(0);
			V.player[1].setMove(0);
			V.gp.setCount(0);
		}
	}
	else 
	{
		V.player[1].setComputer(true);
		V.cur = { 2, 11 };
		gotoXY(V.cur);
		if (!isNew)
		{
			V.isWin = false;
			if (!V.resumepvc) {
				V.gp.clear();
				V.currentPlayer = 0;
				V.status.setIsPlay(true);
				V.player[0].setMove(0);
				V.player[1].setMove(0);
				V.gp.setCount(0);
			}
			else {
				V.currentPlayer = V.gp.getCurrent();
				V.status.setIsPlay(true);
			}
		}

		if (isNew)
		{
			V.gp.clear();
			V.currentPlayer = 0;
			V.status.setIsPlay(true);
			V.player[0].setMove(0);
			V.player[1].setMove(0);
			V.gp.setCount(0);
		}
	}
	V.isWin = false; V.isDraw = false;
	Load(V.gp, V);
	V.cur = { 2, 11 };
	gotoXY(V.cur);
}

void KeyEventProc(KEY_EVENT_RECORD ir, Variables &V) //can thay doi cac hang so khi lam phan option
{

	if (V.status.getIsPlay())
	{
		if (!ir.bKeyDown)
		{
			if (ir.wVirtualKeyCode == VK_DOWN) {
				if (V.cur.Y < (9 + V.gp.getSize() * 2)) V.cur.Y += 2;
				else V.cur.Y = 11;
				gotoXY(V.cur);
			}
			if (ir.wVirtualKeyCode == VK_UP) {
				if (V.cur.Y > 11) V.cur.Y -= 2;
				else V.cur.Y = (9 + V.gp.getSize() * 2);
				gotoXY(V.cur);
			}
			if (ir.wVirtualKeyCode == VK_LEFT) {
				if (V.cur.X > 2) V.cur.X -= 4;
				else V.cur.X = (4 * V.gp.getSize() - 2);
				gotoXY(V.cur);
			}
			if (ir.wVirtualKeyCode == VK_RIGHT) {
				if (V.cur.X < (4 * V.gp.getSize() - 2)) V.cur.X += 4;
				else V.cur.X = 2;
				gotoXY(V.cur);
			}
			if (ir.wVirtualKeyCode == VK_SPACE) {

				if (V.gp.isEmpty(toXarray(V.cur.X), toYarray(V.cur.Y)))
				{
					if (V.currentPlayer == 0) TextColor(V.st.getColorCodeChar1());
					else TextColor(V.st.getColorCodeChar2());
					printf("%c", V.player[V.currentPlayer].getPlayerChar());
					V.gp.set(toXarray(V.cur.X), toYarray(V.cur.Y), V.currentPlayer);
					if (!V.player[1].getComputer()) V.player[V.currentPlayer].setMove(V.player[V.currentPlayer].getMove() + 1);

					if (V.gp.win(toXarray(V.cur.X), toYarray(V.cur.Y)))
					{
						V.isWin = true;
						V.status.setIsPlay(false);
						//updateStatistic(currentPlayer);
						if (!V.player[1].getComputer())
							V.statis.updatePvP(V.currentPlayer, V.player[0].getMove(), V.player[1].getMove());
						congrat(V.currentPlayer);
						return;
					}

					if (V.gp.draw())
					{
						V.isDraw = true;
						V.status.setIsPlay(false);
						if (!V.player[1].getComputer())
							V.statis.updatePvP(-1, V.player[0].getMove(), V.player[1].getMove());
						//Message("Draw game!");
						congrat(3);
						return;
					}

					V.currentPlayer = V.currentPlayer ^ 1; //swap player
					V.gp.setCurrent(V.currentPlayer);
				}

			}
		}
	}

	if (V.status.getStatus() == STATUS_SAVE || V.status.getStatus() == STATUS_LOAD)
	{
		if (!ir.bKeyDown)
		{
			if (ir.wVirtualKeyCode == VK_DOWN)
			{
				gotoXY(V.cur);
				printf("  ");
				if (V.cur.Y < 22) V.cur.Y++;
				else V.cur.Y = 12;
				gotoXY(V.cur);
				printf(">>");
			}

			if (ir.wVirtualKeyCode == VK_UP)
			{
				gotoXY(V.cur);
				printf("  ");
				if (V.cur.Y > 12) V.cur.Y--;
				else V.cur.Y = 22;
				gotoXY(V.cur);
				printf(">>");
			}

			if (ir.wVirtualKeyCode == VK_SPACE)
			{
				if (V.status.getStatus() == STATUS_SAVE)
				{
					if (V.cur.Y - 11 >= 1 && V.cur.Y - 11 <= 10)
					{
						if (V.isWin)
						{
							Message("Cannot save finished game!");
						}
						else
							if (V.isDraw) 
								Message("Cannot save finished game!");
							else
							{
								writeSaveFile(V.gp, V.player[0], V.player[1], V.cur.Y - 11, V.computer);
								V.status.setStatus(STATUS_NONE);
								clearRightSide();
								Message("SAVED SUCCESSFULLY TO SLOT " + std::to_string(V.cur.Y - 11));
							}
					}
					if (V.cur.Y == 22)
					{
						V.status.setStatus(STATUS_NONE);
						clearRightSide();
					}
				}

				if (V.status.getStatus() == STATUS_LOAD)
				{
					if (V.cur.Y - 11 >= 1 && V.cur.Y - 11 <= 10)
					{
						readSaveFile(V.gp, V.player[0], V.player[1], V.cur.Y - 11, V.computer);

						V.st.setSize(V.gp.getSize());
						clearGrid();
						TextColor(V.st.getColorCodeGrid());
						drawGrid(V.st.getSize());
						writeSettingFile(V.st);

						V.status.setStatus(STATUS_NONE);
						clearRightSide();
						if (V.player[1].getComputer())
						{
							V.status.setStatus(STATUS_PVC);
							V.status.setIsPlay(false);
							V.resumepvc = true;
							Message("LOADED SUCCESSFULLY SLOT " + std::to_string(V.cur.Y - 11));
							play(false, true, V);
						}
						else {
							V.status.setStatus(STATUS_RESUME_PVP);
							V.status.setIsPlay(false);
							V.resumepvp = true;
							Message("LOADED SUCCESSFULLY SLOT " + std::to_string(V.cur.Y - 11));
							if (V.gp.getCurrent() == 0) Message("It is player 1 turn");
							else Message("It is player 2 turn");
							//else Message("It is player 2 turn");
							play(false, false, V);
						}
					}
					if (V.cur.Y == 22)
					{
						V.status.setStatus(STATUS_NONE);
						clearRightSide();
					}
				}
			}
		}
	}

	if (V.status.getStatus() == STATUS_SETTING)
	{

		if (!ir.bKeyDown)
		{
			if (ir.wVirtualKeyCode == VK_DOWN)
			{
				gotoXY(V.cur);
				printf("  ");
				if (V.cur.Y < 20) V.cur.Y++;
				else V.cur.Y = 12;
				gotoXY(V.cur);
				printf(">>");
			}

			if (ir.wVirtualKeyCode == VK_UP)
			{
				gotoXY(V.cur);
				printf("  ");
				if (V.cur.Y > 12) V.cur.Y--;
				else V.cur.Y = 20;
				gotoXY(V.cur);
				printf(">>");
			}

			if (ir.wVirtualKeyCode == VK_RIGHT)
			{
				if (V.cur.Y == 12) //size setting
				{
					V.n++;
					if (V.n > 20) V.n = 10;
					gotoXY(132, 12);
					printf("%d", V.n);

				}

				if (V.cur.Y == 13) // character p1
				{
					V.a++;		
					if (V.a == V.b)
					{
						V.a++;
					} 
					if (V.a > 126) V.a = 33;
					gotoXY(132, 13);
					printf("%c", (char)V.a);
				}

				if (V.cur.Y == 14) // character p1
				{
					V.b++;
					if (V.a == V.b)
					{
						V.b++;
					}
					if (V.b > 126) V.b = 33;
					gotoXY(132, 14);
					printf("%c", (char)V.b);
				}

				if (V.cur.Y == 15)	//sound setting
				{
					V.sound = !V.sound;
					gotoXY(132, 15);
					if (V.sound) printf("On ");
					else printf("Off");
				}

				if (V.cur.Y == 16)
				{
					V.colorGrid++;
					V.colorGrid %= 16;
					if (V.colorGrid == 0) V.colorGrid++;
					gotoXY(132, 16);
					printf("%s", V.st.getColor(V.colorGrid));
				}

				if (V.cur.Y == 17)
				{
					V.color1++;
					V.color1 %= 16;
					if (V.color1 == 0) V.color1++;
					gotoXY(132, 17);
					printf("%s", V.st.getColor(V.color1));
				}

				if (V.cur.Y == 18)
				{
					V.color2++;
					V.color2 %= 16;
					if (V.color2 == 0) V.color2++;
					gotoXY(132, 18);
					printf("%s", V.st.getColor(V.color2));
				}
			}

			if (ir.wVirtualKeyCode == VK_LEFT)
			{
				if (V.cur.Y == 12) //size setting
				{
					V.n--;
					if (V.n < 10) V.n = 20;
					gotoXY(132, 12);
					printf("%d", V.n);

				}

				if (V.cur.Y == 13) // character p1
				{
					V.a--;
					if (V.a == V.b)
					{
						V.a--;
					}
					if (V.a < 33) V.a = 126;
					gotoXY(132, 13);
					printf("%c", (char)V.a);
				}

				if (V.cur.Y == 14) // character p2
				{
					V.b--;
					if (V.a == V.b)
					{
						V.b--;
					}
					if (V.b < 33) V.b = 126;
					gotoXY(132, 14);
					printf("%c", (char)V.b);
				}

				if (V.cur.Y == 15)	//sound setting
				{
					V.sound = !V.sound;
					gotoXY(132, 15);
					if (V.sound) printf("On ");
					else printf("Off");
				}

				if (V.cur.Y == 16)
				{
					V.colorGrid--;
					if (V.colorGrid == 0) V.colorGrid = 15;
					gotoXY(132, 16);
					printf("%s", V.st.getColor(V.colorGrid));
				}

				if (V.cur.Y == 17)
				{
					V.color1--;
					if (V.color1 == 0) V.color1 = 15;
					gotoXY(132, 17);
					printf("%s", V.st.getColor(V.color1));
				}

				if (V.cur.Y == 18)
				{
					V.color2--;
					if (V.color2 == 0) V.color2 = 15;
					gotoXY(132, 18);
					printf("%s", V.st.getColor(V.color2));
				}
			}

			if (ir.wVirtualKeyCode == VK_SPACE)
			{
				if (V.cur.Y == 19)
				{
					SaveSetting(V.n, V.a, V.b, V.sound, V.colorGrid, V.color1, V.color2, V);
					V.status.setStatus(STATUS_NONE);
					clearRightSide();
					Message("Saved setting");
				}

				if (V.cur.Y == 20)
				{
					V.status.setStatus(STATUS_NONE);
					clearRightSide();
				}
			}
		}
	}

	if (V.status.getStatus() == STATUS_PVC && !V.status.getIsPlay())
	{

		if (!ir.bKeyDown)
		{
			if (ir.wVirtualKeyCode == VK_DOWN)
			{
				gotoXY(V.cur);
				printf("  ");
				if (V.cur.Y < 15) V.cur.Y++;
				else V.cur.Y = 12;
				gotoXY(V.cur);
				printf(">>");
			}

			if (ir.wVirtualKeyCode == VK_UP)
			{
				gotoXY(V.cur);
				printf("  ");
				if (V.cur.Y > 12) V.cur.Y--;
				else V.cur.Y = 15;
				gotoXY(V.cur);
				printf(">>");
			}

			if (ir.wVirtualKeyCode == VK_SPACE)
			{
				if (V.cur.Y == 12)
				{
					V.computer.setLevel(1);
					clearRightSide();
					setcursor(true, 0);
					play(true, true, V);
				}
				if (V.cur.Y == 13)
				{
					V.computer.setLevel(2);
					clearRightSide();
					setcursor(true, 0);
					play(true, true, V);
				}
				if (V.cur.Y == 14)
				{
					V.computer.setLevel(3);
					clearRightSide();
					setcursor(true, 0);
					play(true, true, V);
				}
				if (V.cur.Y == 15)
				{
					clearRightSide();
					V.status.setStatus(STATUS_NONE);
				}
			}
		}
	}

	if (!ir.bKeyDown)
	{
		if (ir.wVirtualKeyCode == VK_F1) 
		{
			clearRightSide();
			V.status.setStatus(STATUS_RESUME_PVP);
			V.status.setIsPlay(false);
			setcursor(true, 0);
			play(false, false, V);
		}
		if (ir.wVirtualKeyCode == VK_F2)
		{
			clearRightSide();
			V.status.setStatus(STATUS_RESUME_PVC);
			V.status.setIsPlay(false);
			setcursor(true, 0);
			play(false, true, V);
		}
		if (ir.wVirtualKeyCode == VK_F3)
		{
			clearRightSide();
			V.status.setStatus(STATUS_PVP);
			V.status.setIsPlay(false);
			setcursor(true, 0);
			play(true, false, V);
		}

		if (ir.wVirtualKeyCode == VK_F4)
		{
			clearRightSide();
			V.status.setStatus(STATUS_PVC);
			V.status.setIsPlay(false);
			setcursor(false, 0);
			pvcMenu(V);
			//play(true, true);
		}

		if (ir.wVirtualKeyCode == VK_F5)
		{
			clearRightSide();
			V.status.setStatus(STATUS_SETTING);
			V.status.setIsPlay(false);
			setcursor(false, 0);
			settingMenu(V);
		}

		if (ir.wVirtualKeyCode == VK_F6)
		{
			clearRightSide();
			V.status.setStatus(STATUS_SAVE);
			V.status.setIsPlay(false);
			//writeSaveFile(gp, player[0], player[1], 0);
			setcursor(false, 0);
			SaveFile(V);
		}

		if (ir.wVirtualKeyCode == VK_F7)
		{
			clearRightSide();
			V.status.setStatus(STATUS_LOAD);
			V.status.setIsPlay(false);
			//readSaveFile(gp, player[0], player[1], 0);
			setcursor(false, 0);
			LoadFile(V);
		}

		if (ir.wVirtualKeyCode == VK_F8)
		{
			clearRightSide();
			V.status.setStatus(STATUS_STAT);
			setcursor(false, 0);
			V.status.setIsPlay(false);
			StatisticMenu(V);
		}

		if (ir.wVirtualKeyCode == VK_F9)
		{
			V.status.setStatus(STATUS_EXIT);
			V.status.setIsPlay(false);
		}
	}

}

void LoadFile(Variables &V)
{
	TextColor(V.st.getColorCodeGrid());
	gotoXY(115, 10);
	printf("CHOOSE LOAD SLOT:");
	for (int i = 12; i < 22; i++)
	{
		gotoXY(115, i);
		printf("Slot %d", i - 11);
	}

	gotoXY(115, 22);
	printf("Return");

	V.cur = { 112, 12 };
	gotoXY(V.cur);
	printf(">>");

	INPUT_RECORD InputRecord;
	DWORD Events;

	while (V.status.getStatus() == STATUS_LOAD)
	{
		ReadConsoleInput(hin, &InputRecord, 1, &Events);

		if (InputRecord.EventType == KEY_EVENT)
		{
			KeyEventProc(InputRecord.Event.KeyEvent, V);
		}
	}
}

void SaveFile(Variables &V)
{
	TextColor(V.st.getColorCodeGrid());
	gotoXY(115, 10);
	printf("CHOOSE SAVE SLOT:");
	for (int i = 12; i < 22; i++)
	{
		gotoXY(115, i); 
		printf("Slot %d", i - 11);
	}

	gotoXY(115, 22);
	printf("Return");

	V.cur = { 112, 12 };
	gotoXY(V.cur);
	printf(">>");

	INPUT_RECORD InputRecord;
	DWORD Events;

	while (V.status.getStatus() == STATUS_SAVE)
	{
		ReadConsoleInput(hin, &InputRecord, 1, &Events);

		if (InputRecord.EventType == KEY_EVENT)
		{
			KeyEventProc(InputRecord.Event.KeyEvent, V);
		}
	}

}

void play(bool isNew, bool comp, Variables &V)
{
	init(isNew, comp, V);

	V.resumepvp = (!comp) ? true : false;
	V.resumepvc = (comp) ? true : false;

	INPUT_RECORD InputRecord;
	DWORD Events;

	while (1)
	{
		setcursor(true, 0);
		ReadConsoleInput(hin, &InputRecord, 1, &Events);
		
		if (InputRecord.EventType == KEY_EVENT) 
		{
			KeyEventProc(InputRecord.Event.KeyEvent, V);
		}

		if (comp && V.currentPlayer == 1)
		{
			if (V.currentPlayer == 0) TextColor(V.st.getColorCodeChar1());
			else TextColor(V.st.getColorCodeChar2());
			setcursor(false, 0);
			V.cur = V.computer.nextMove(V.gp);
			gotoXY(toXconsole(V.cur.X), toYconsole(V.cur.Y));
			printf("%c", V.player[V.currentPlayer].getPlayerChar());

			V.gp.set(V.cur.X, V.cur.Y, V.currentPlayer);
			//player[currentPlayer].setMove(player[currentPlayer].getMove() + 1);

			if (V.gp.win(V.cur.X, V.cur.Y))
			{
				V.isWin = true;
				V.status.setIsPlay(false);
				//Message("Computer win");
				congrat(2);
			}

			if (V.gp.draw())
			{
				V.isDraw = true;
				V.status.setIsPlay(false);
				congrat(3);
			}

			V.cur.X = toXconsole(V.cur.X);
			V.cur.Y = toYconsole(V.cur.Y);
			gotoXY(V.cur);

			V.currentPlayer = V.currentPlayer ^ 1; //swap player
			V.gp.setCurrent(V.currentPlayer);
		}

		if (V.isWin || V.isDraw) 
		{
			V.resumepvp = false;
			V.resumepvc = false;
			V.status.setIsPlay(false);
			V.status.setStatus(STATUS_NONE);
			break;
		}

		if (!V.status.getIsPlay()) 
		{
			break;
		}
	}
	setcursor(false, 0);
}

void pvcMenu(Variables &V)
{
	TextColor(V.st.getColorCodeGrid());
	gotoXY(115, 10);
	printf("PVC MODE:");

	gotoXY(115, 12);
	printf("Easy");
	gotoXY(115, 13);
	printf("Medium");
	gotoXY(115, 14);
	printf("Hard");
	gotoXY(115, 15);
	printf("Return");

	V.cur = { 112, 12 };
	gotoXY(V.cur);
	printf(">>");

	INPUT_RECORD InputRecord;
	DWORD Events;

	while (V.status.getStatus() == STATUS_PVC && !V.status.getIsPlay())
	{
		ReadConsoleInput(hin, &InputRecord, 1, &Events);

		if (InputRecord.EventType == KEY_EVENT)
		{
			KeyEventProc(InputRecord.Event.KeyEvent, V);
		}
	}
}

void settingMenu(Variables &V)
{
	TextColor(V.st.getColorCodeGrid());

	V.n = V.st.getSize();
	V.a = (int)V.st.getCharP1();
	V.b = (int)V.st.getCharP2();
	V.sound = V.st.getSoundOn();
	V.colorGrid = V.st.getColorCodeGrid();
	V.color1 = V.st.getColorCodeChar1();
	V.color2 = V.st.getColorCodeChar2();

	gotoXY(115, 10);
	printf("SETTINGS:");
	gotoXY(115, 12);
	printf("size:            ");
	printf("%d", V.n);

	gotoXY(115, 13);
	printf("Player 1 symbol: ");
	printf("%c", (char)V.a);

	gotoXY(115, 14);
	printf("Player 2 symbol: ");
	printf("%c", (char)V.b);

	gotoXY(115, 15);
	printf("Sound On/Off:    ");
	if (V.sound) printf("On");
	else printf("Off");

	gotoXY(115, 16);
	printf("Grid color:      ");
	printf("%s", V.st.getColor(V.colorGrid));

	gotoXY(115, 17);
	printf("Player 1 color:  ");
	printf("%s", V.st.getColor(V.color1));

	gotoXY(115, 18);
	printf("Player 2 color:  ");
	printf("%s", V.st.getColor(V.color2));

	gotoXY(115, 19);
	printf("Save change");


	gotoXY(115, 20);
	printf("Return");

	V.cur = { 112, 12 };
	gotoXY(V.cur);
	printf(">>");

	INPUT_RECORD InputRecord;
	DWORD Events;

	while (V.status.getStatus() == STATUS_SETTING)
	{
		ReadConsoleInput(hin, &InputRecord, 1, &Events);

		if (InputRecord.EventType == KEY_EVENT)
		{
			KeyEventProc(InputRecord.Event.KeyEvent, V);
		}
	}
}

void LoadSetting(Variables &V)
{
	readSettingFile(V.st);
	V.player[0].setPlayerChar(V.st.getCharP1());
	V.player[1].setPlayerChar(V.st.getCharP2());
	V.gp.setSize(V.st.getSize());
	TextColor(V.st.getColorCodeGrid());
	drawGrid(V.st.getSize());
	//PlaySound(TEXT("dive.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	mciSendString("open \"dive.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
	if (V.st.getSoundOn())
	{
		mciSendString("play mp3 repeat", NULL, 0, NULL);
	}
	else
	{
		mciSendString("pause mp3", NULL, 0, NULL);
	}
}

void SaveSetting(int n, int a, int b, bool sound, int colorGrid, int color1, int color2, Variables &V)
{
	V.st.setCharP1((char)a);
	V.st.setCharP2((char)b);
	V.st.setColorCodeChar1(color1);
	V.st.setColorCodeChar2(color2);
	V.st.setSound((bool)sound);
	V.st.setColorCodeGrid(colorGrid);
	V.st.setSize(n);

	V.player[0].setPlayerChar(V.st.getCharP1());
	V.player[1].setPlayerChar(V.st.getCharP2());
	if (V.st.getSize() != V.gp.getSize())
	{
		clearGrid();
		V.gp.clear();
		V.gp.setSize(V.st.getSize());
		TextColor(V.st.getColorCodeGrid());
		drawGrid(V.st.getSize());
		V.resumepvp = false;
		V.resumepvc = true;
	}
	else 
	{
		TextColor(V.st.getColorCodeGrid());
		drawGrid(V.st.getSize());
		Load(V.gp, V);
	}

	if (V.st.getSoundOn())
	{
		mciSendString("play mp3 repeat", NULL, 0, NULL);
	}
	else
	{
		mciSendString("pause mp3", NULL, 0, NULL);
	}

	writeSettingFile(V.st);
	TextColor(V.st.getColorCodeGrid());
	Message("Saved settings!");
}

void StatisticMenu(Variables &V)
{
	TextColor(V.st.getColorCodeGrid());
	gotoXY(115, 10);
	printf("STATISTIC:");
	gotoXY(115, 11);
	printf("PvP Statistic");
	gotoXY(115, 12);
	printf("%c", 197);
	for (int i = 0; i < 30; i++) printf("%c", 196);
	printf("%c", 197);
	for (int i = 0; i < 10; i++) 
	{
		gotoXY(115, 13 + i);
		printf("%c", 179);
		for (int i = 0; i < 30; i++) printf(" ");
		printf("%c", 179);
	}
	gotoXY(115, 22);
	printf("%c", 197);
	for (int i = 0; i < 30; i++) printf("%c", 196);
	printf("%c", 197);

	gotoXY(117, 13);  
	printf("Total game:           "); 
	printf("%d", V.statis.GetTotal());

	gotoXY(117, 14);
	printf("Player 1 win:         ");
	printf("%d", V.statis.GetWinP1());

	gotoXY(117, 15);
	printf("Player 2 win:         ");
	printf("%d", V.statis.GetWinP2());

	gotoXY(117, 16);
	printf("Draw game:            ");
	printf("%d", V.statis.GetDraw());

	gotoXY(117, 17);
	printf("Player 1 total move:  ");
	printf("%d", V.statis.GetMoveP1());

	gotoXY(117, 18);
	printf("Player 2 total move:  ");
	printf("%d", V.statis.GetMoveP2());

	gotoXY(117, 19);
	printf("Player 1 win percent: ");
	printf("%.2lf", V.statis.GetWinPercentP1());

	gotoXY(117, 20);
	printf("Player 2 win percent: ");
	printf("%.2lf", V.statis.GetWinPercentP2());

	gotoXY(117, 21);
	printf("Draw percent:         ");
	printf("%.2lf", V.statis.GetDrawPercent());
}

void LoadStatFile(Variables &V)
{
	readStatFile(V.statis);
}

int main()
{
	setConsoleWindow();
	setMode();
	Variables V;
	LoadSplash();

	LoadAbout();

	banner();
	setcursor(false, 0);
	
	LoadSetting(V);
	LoadStatFile(V);

	INPUT_RECORD InputRecord;
	DWORD Events;
	
	while (1)
	{
		ReadConsoleInput(hin, &InputRecord, 1, &Events);

		if (InputRecord.EventType == KEY_EVENT)
		{
			KeyEventProc(InputRecord.Event.KeyEvent, V);
		}

		if (V.status.getStatus() == STATUS_EXIT) break;
	}
	
	//system("pause");
	writeStatFile(V.statis);
	return 0;
}