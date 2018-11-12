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

#pragma comment(lib, "winmm.lib")

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

void play(bool, bool);
void SaveFile(void);
void LoadFile(void);
void settingMenu(void);
void SaveSetting(int, int, int, bool, int, int, int);
void StatisticMenu(void);
void pvcMenu(void);

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
	gotoXY(5, 9);
	printf("Player %d has won!!!!!!", no + 1);
	Sleep(1000);
	gotoXY(5, 9);
	printf("                       ");
}

void Load(GamePlay gp)
{
	for (int i = 0; i<gp.getSize(); i++)
		for (int j = 0; j < gp.getSize(); j++) {
			int tmp = gp.get(i, j); 
			gotoXY(toXconsole(i), toYconsole(j));
			if (tmp == 0) TextColor(st.getColorCodeChar1()); 
			if (tmp == 1) TextColor(st.getColorCodeChar2());
			if (tmp >= 0) printf("%c", player[tmp].getPlayerChar());
			if (tmp < 0) printf(" ");
		}
}

void init(bool isNew, bool comp)
{
	setcursor(true, 0);
	if (!comp)
	{
		cur = { 2, 11 };
		gotoXY(cur);
		if (!isNew)
		{
			if (!resumepvp) {
				gp.clear();
				currentPlayer = 0;
				status.setIsPlay(true);
				player[0].setMove(0);
				player[1].setMove(0);
				gp.setCount(0);
			}
			else {
				currentPlayer = gp.getCurrent();
				status.setIsPlay(true);
			}
		}

		if (isNew) 
		{
			gp.clear();
			currentPlayer = 0;
			status.setIsPlay(true);
			player[0].setMove(0);
			player[1].setMove(0);
			gp.setCount(0);
		}
	}
	else 
	{
		player[1].setComputer(true);
		cur = { 2, 11 };
		gotoXY(cur);
		if (!isNew)
		{
			isWin = false;
			if (!resumepvc) {
				gp.clear();
				currentPlayer = 0;
				status.setIsPlay(true);
				player[0].setMove(0);
				player[1].setMove(0);
				gp.setCount(0);
			}
			else {
				currentPlayer = gp.getCurrent();
				status.setIsPlay(true);
			}
		}

		if (isNew)
		{
			gp.clear();
			currentPlayer = 0;
			status.setIsPlay(true);
			player[0].setMove(0);
			player[1].setMove(0);
			gp.setCount(0);
		}
	}
	isWin = false; isDraw = false;
	Load(gp);
	cur = { 2, 11 };
	gotoXY(cur);
}

void KeyEventProc(KEY_EVENT_RECORD ir) //can thay doi cac hang so khi lam phan option
{

	if (status.getIsPlay())
	{
		if (!ir.bKeyDown)
		{
			if (ir.wVirtualKeyCode == VK_DOWN) {
				if (cur.Y < (9 + gp.getSize() * 2)) cur.Y += 2;
				else cur.Y = 11;
				gotoXY(cur);
			}
			if (ir.wVirtualKeyCode == VK_UP) {
				if (cur.Y > 11) cur.Y -= 2;
				else cur.Y = (9 + gp.getSize() * 2);
				gotoXY(cur);
			}
			if (ir.wVirtualKeyCode == VK_LEFT) {
				if (cur.X > 2) cur.X -= 4;
				else cur.X = (4 * gp.getSize() - 2);
				gotoXY(cur);
			}
			if (ir.wVirtualKeyCode == VK_RIGHT) {
				if (cur.X < (4 * gp.getSize() - 2)) cur.X += 4;
				else cur.X = 2;
				gotoXY(cur);
			}
			if (ir.wVirtualKeyCode == VK_SPACE) {

				if (gp.isEmpty(toXarray(cur.X), toYarray(cur.Y)))
				{
					if (currentPlayer == 0) TextColor(st.getColorCodeChar1());
					else TextColor(st.getColorCodeChar2());
					printf("%c", player[currentPlayer].getPlayerChar());
					gp.set(toXarray(cur.X), toYarray(cur.Y), currentPlayer);
					if (!player[1].getComputer()) player[currentPlayer].setMove(player[currentPlayer].getMove() + 1);

					if (gp.win(toXarray(cur.X), toYarray(cur.Y)))
					{
						isWin = true;
						status.setIsPlay(false);
						congrat(currentPlayer);
						//updateStatistic(currentPlayer);
						if (!player[1].getComputer())
							statis.updatePvP(currentPlayer, player[0].getMove(), player[1].getMove());
						return;
					}

					if (gp.draw())
					{
						isDraw = true;
						status.setIsPlay(false);
						if (!player[1].getComputer())
							statis.updatePvP(-1, player[0].getMove(), player[1].getMove());
						Message("Draw game!");
						return;
					}

					currentPlayer = currentPlayer ^ 1; //swap player
					gp.setCurrent(currentPlayer);
				}

			}
		}
	}

	if (status.getStatus() == STATUS_SAVE || status.getStatus() == STATUS_LOAD)
	{
		if (!ir.bKeyDown)
		{
			if (ir.wVirtualKeyCode == VK_DOWN)
			{
				gotoXY(cur);
				printf("  ");
				if (cur.Y < 22) cur.Y++;
				else cur.Y = 12;
				gotoXY(cur);
				printf(">>");
			}

			if (ir.wVirtualKeyCode == VK_UP)
			{
				gotoXY(cur);
				printf("  ");
				if (cur.Y > 12) cur.Y--;
				else cur.Y = 22;
				gotoXY(cur);
				printf(">>");
			}

			if (ir.wVirtualKeyCode == VK_SPACE)
			{
				if (status.getStatus() == STATUS_SAVE)
				{
					if (cur.Y - 11 >= 1 && cur.Y - 11 <= 10)
					{
						if (isWin)
						{
							Message("Cannot save finished game!");
						}
						else
							if (isDraw) 
								Message("Cannot save finished game!");
							else
							{
								writeSaveFile(gp, player[0], player[1], cur.Y - 11, computer);
								status.setStatus(STATUS_NONE);
								clearRightSide();
								Message("SAVED SUCCESSFULLY TO SLOT " + std::to_string(cur.Y - 11));
							}
					}
					if (cur.Y == 22)
					{
						status.setStatus(STATUS_NONE);
						clearRightSide();
					}
				}

				if (status.getStatus() == STATUS_LOAD)
				{
					if (cur.Y - 11 >= 1 && cur.Y - 11 <= 10)
					{
						readSaveFile(gp, player[0], player[1], cur.Y - 11, computer);

						st.setSize(gp.getSize());
						clearGrid();
						TextColor(st.getColorCodeGrid());
						drawGrid(st.getSize());
						writeSettingFile(st);

						status.setStatus(STATUS_NONE);
						clearRightSide();
						if (player[1].getComputer())
						{
							status.setStatus(STATUS_PVC);
							status.setIsPlay(false);
							resumepvc = true;
							Message("LOADED SUCCESSFULLY SLOT " + std::to_string(cur.Y - 11));
							play(true, true);
						}
						else {
							status.setStatus(STATUS_RESUME_PVP);
							status.setIsPlay(false);
							resumepvp = true;
							Message("LOADED SUCCESSFULLY SLOT " + std::to_string(cur.Y - 11));
							play(false, false);
						}
					}
					if (cur.Y == 22)
					{
						status.setStatus(STATUS_NONE);
						clearRightSide();
					}
				}
			}
		}
	}

	if (status.getStatus() == STATUS_SETTING)
	{

		if (!ir.bKeyDown)
		{
			if (ir.wVirtualKeyCode == VK_DOWN)
			{
				gotoXY(cur);
				printf("  ");
				if (cur.Y < 20) cur.Y++;
				else cur.Y = 12;
				gotoXY(cur);
				printf(">>");
			}

			if (ir.wVirtualKeyCode == VK_UP)
			{
				gotoXY(cur);
				printf("  ");
				if (cur.Y > 12) cur.Y--;
				else cur.Y = 20;
				gotoXY(cur);
				printf(">>");
			}

			if (ir.wVirtualKeyCode == VK_RIGHT)
			{
				if (cur.Y == 12) //size setting
				{
					n++;
					if (n > 20) n = 10;
					gotoXY(132, 12);
					printf("%d", n);

				}

				if (cur.Y == 13) // character p1
				{
					a++;		
					if (a == b)
					{
						a++;
					} 
					if (a > 126) a = 33;
					gotoXY(132, 13);
					printf("%c", (char)a);
				}

				if (cur.Y == 14) // character p1
				{
					b++;
					if (a == b)
					{
						b++;
					}
					if (b > 126) b = 33;
					gotoXY(132, 14);
					printf("%c", (char)b);
				}

				if (cur.Y == 15)	//sound setting
				{
					sound = !sound;
					gotoXY(132, 15);
					if (sound) printf("On ");
					else printf("Off");
				}

				if (cur.Y == 16)
				{
					colorGrid++;
					colorGrid %= 16;
					if (colorGrid == 0) colorGrid++;
					gotoXY(132, 16);
					printf("%s", st.getColor(colorGrid));
				}

				if (cur.Y == 17)
				{
					color1++;
					color1 %= 16;
					if (color1 == 0) color1++;
					gotoXY(132, 17);
					printf("%s", st.getColor(color1));
				}

				if (cur.Y == 18)
				{
					color2++;
					color2 %= 16;
					if (color2 == 0) color2++;
					gotoXY(132, 18);
					printf("%s", st.getColor(color2));
				}
			}

			if (ir.wVirtualKeyCode == VK_LEFT)
			{
				if (cur.Y == 12) //size setting
				{
					n--;
					if (n < 10) n = 20;
					gotoXY(132, 12);
					printf("%d", n);

				}

				if (cur.Y == 13) // character p1
				{
					a--;
					if (a == b)
					{
						a--;
					}
					if (a < 33) a = 126;
					gotoXY(132, 13);
					printf("%c", (char)a);
				}

				if (cur.Y == 14) // character p2
				{
					b--;
					if (a == b)
					{
						b--;
					}
					if (b < 33) b = 126;
					gotoXY(132, 14);
					printf("%c", (char)b);
				}

				if (cur.Y == 15)	//sound setting
				{
					sound = !sound;
					gotoXY(132, 15);
					if (sound) printf("On ");
					else printf("Off");
				}

				if (cur.Y == 16)
				{
					colorGrid--;
					if (colorGrid == 0) colorGrid = 15;
					gotoXY(132, 16);
					printf("%s", st.getColor(colorGrid));
				}

				if (cur.Y == 17)
				{
					color1--;
					if (color1 == 0) color1 = 15;
					gotoXY(132, 17);
					printf("%s", st.getColor(color1));
				}

				if (cur.Y == 18)
				{
					color2--;
					if (color2 == 0) color2 = 15;
					gotoXY(132, 18);
					printf("%s", st.getColor(color2));
				}
			}

			if (ir.wVirtualKeyCode == VK_SPACE)
			{
				if (cur.Y == 19)
				{
					SaveSetting(n, a, b, sound, colorGrid, color1, color2);
					status.setStatus(STATUS_NONE);
					clearRightSide();
					Message("Saved setting");
				}

				if (cur.Y == 20)
				{
					status.setStatus(STATUS_NONE);
					clearRightSide();
				}
			}
		}
	}

	if (status.getStatus() == STATUS_PVC && !status.getIsPlay())
	{

		if (!ir.bKeyDown)
		{
			if (ir.wVirtualKeyCode == VK_DOWN)
			{
				gotoXY(cur);
				printf("  ");
				if (cur.Y < 15) cur.Y++;
				else cur.Y = 12;
				gotoXY(cur);
				printf(">>");
			}

			if (ir.wVirtualKeyCode == VK_UP)
			{
				gotoXY(cur);
				printf("  ");
				if (cur.Y > 12) cur.Y--;
				else cur.Y = 15;
				gotoXY(cur);
				printf(">>");
			}

			if (ir.wVirtualKeyCode == VK_SPACE)
			{
				if (cur.Y == 12)
				{
					computer.setLevel(1);
					clearRightSide();
					setcursor(true, 0);
					play(true, true);
				}
				if (cur.Y == 13)
				{
					computer.setLevel(2);
					clearRightSide();
					setcursor(true, 0);
					play(true, true);
				}
				if (cur.Y == 14)
				{
					computer.setLevel(3);
					clearRightSide();
					setcursor(true, 0);
					play(true, true);
				}
				if (cur.Y == 15)
				{
					clearRightSide();
					status.setStatus(STATUS_NONE);
				}
			}
		}
	}

	if (!ir.bKeyDown)
	{
		if (ir.wVirtualKeyCode == VK_F1) 
		{
			clearRightSide();
			status.setStatus(STATUS_RESUME_PVP);
			status.setIsPlay(false);
			setcursor(true, 0);
			play(false, false);
		}
		if (ir.wVirtualKeyCode == VK_F2)
		{
			clearRightSide();
			status.setStatus(STATUS_RESUME_PVC);
			status.setIsPlay(false);
			setcursor(true, 0);
			play(false, true);
		}
		if (ir.wVirtualKeyCode == VK_F3)
		{
			clearRightSide();
			status.setStatus(STATUS_PVP);
			status.setIsPlay(false);
			setcursor(true, 0);
			play(true, false);
		}

		if (ir.wVirtualKeyCode == VK_F4)
		{
			clearRightSide();
			status.setStatus(STATUS_PVC);
			status.setIsPlay(false);
			setcursor(false, 0);
			pvcMenu();
			//play(true, true);
		}

		if (ir.wVirtualKeyCode == VK_F5)
		{
			clearRightSide();
			status.setStatus(STATUS_SETTING);
			status.setIsPlay(false);
			setcursor(false, 0);
			settingMenu();
		}

		if (ir.wVirtualKeyCode == VK_F6)
		{
			clearRightSide();
			status.setStatus(STATUS_SAVE);
			status.setIsPlay(false);
			//writeSaveFile(gp, player[0], player[1], 0);
			setcursor(false, 0);
			SaveFile();
		}

		if (ir.wVirtualKeyCode == VK_F7)
		{
			clearRightSide();
			status.setStatus(STATUS_LOAD);
			status.setIsPlay(false);
			//readSaveFile(gp, player[0], player[1], 0);
			setcursor(false, 0);
			LoadFile();
		}

		if (ir.wVirtualKeyCode == VK_F8)
		{
			clearRightSide();
			status.setStatus(STATUS_STAT);
			setcursor(false, 0);
			status.setIsPlay(false);
			StatisticMenu();
		}

		if (ir.wVirtualKeyCode == VK_F9)
		{
			status.setStatus(STATUS_EXIT);
			status.setIsPlay(false);
		}
	}

}

void LoadFile()
{
	TextColor(st.getColorCodeGrid());
	gotoXY(115, 10);
	printf("CHOOSE LOAD SLOT:");
	for (int i = 12; i < 22; i++)
	{
		gotoXY(115, i);
		printf("Slot %d", i - 11);
	}

	gotoXY(115, 22);
	printf("Return");

	cur = { 112, 12 };
	gotoXY(cur);
	printf(">>");

	INPUT_RECORD InputRecord;
	DWORD Events;

	while (status.getStatus() == STATUS_LOAD)
	{
		ReadConsoleInput(hin, &InputRecord, 1, &Events);

		if (InputRecord.EventType == KEY_EVENT)
		{
			KeyEventProc(InputRecord.Event.KeyEvent);
		}
	}
}

void SaveFile()
{
	TextColor(st.getColorCodeGrid());
	gotoXY(115, 10);
	printf("CHOOSE SAVE SLOT:");
	for (int i = 12; i < 22; i++)
	{
		gotoXY(115, i); 
		printf("Slot %d", i - 11);
	}

	gotoXY(115, 22);
	printf("Return");

	cur = { 112, 12 };
	gotoXY(cur);
	printf(">>");

	INPUT_RECORD InputRecord;
	DWORD Events;

	while (status.getStatus() == STATUS_SAVE)
	{
		ReadConsoleInput(hin, &InputRecord, 1, &Events);

		if (InputRecord.EventType == KEY_EVENT)
		{
			KeyEventProc(InputRecord.Event.KeyEvent);
		}
	}

}

void play(bool isNew, bool comp)
{
	init(isNew, comp);

	resumepvp = (!comp) ? true : false;
	resumepvc = (comp) ? true : false;

	INPUT_RECORD InputRecord;
	DWORD Events;

	while (1)
	{
		setcursor(true, 0);
		ReadConsoleInput(hin, &InputRecord, 1, &Events);
		
		if (InputRecord.EventType == KEY_EVENT) 
		{
			KeyEventProc(InputRecord.Event.KeyEvent);
		}

		if (comp && currentPlayer == 1)
		{
			if (currentPlayer == 0) TextColor(st.getColorCodeChar1());
			else TextColor(st.getColorCodeChar2());
			setcursor(false, 0);
			cur = computer.nextMove(gp);
			gotoXY(toXconsole(cur.X), toYconsole(cur.Y));
			printf("%c", player[currentPlayer].getPlayerChar());

			gp.set(cur.X, cur.Y, currentPlayer);
			//player[currentPlayer].setMove(player[currentPlayer].getMove() + 1);

			if (gp.win(cur.X, cur.Y))
			{
				isWin = true;
				status.setIsPlay(false);
				Message("Computer win");
			}

			if (gp.draw())
			{
				isDraw = true;
				status.setIsPlay(false);
				Message("Draw game!");
			}

			cur.X = toXconsole(cur.X);
			cur.Y = toYconsole(cur.Y);
			gotoXY(cur);

			currentPlayer = currentPlayer ^ 1; //swap player
			gp.setCurrent(currentPlayer);
		}

		if (isWin || isDraw) 
		{
			resumepvp = false;
			resumepvc = false;
			status.setIsPlay(false);
			status.setStatus(STATUS_NONE);
			break;
		}

		if (!status.getIsPlay()) 
		{
			break;
		}
	}
	setcursor(false, 0);
}

void pvcMenu()
{
	TextColor(st.getColorCodeGrid());
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

	cur = { 112, 12 };
	gotoXY(cur);
	printf(">>");

	INPUT_RECORD InputRecord;
	DWORD Events;

	while (status.getStatus() == STATUS_PVC && !status.getIsPlay())
	{
		ReadConsoleInput(hin, &InputRecord, 1, &Events);

		if (InputRecord.EventType == KEY_EVENT)
		{
			KeyEventProc(InputRecord.Event.KeyEvent);
		}
	}
}

void settingMenu()
{
	TextColor(st.getColorCodeGrid());

	n = st.getSize();
	a = (int)st.getCharP1();
	b = (int)st.getCharP2();
	sound = st.getSoundOn();
	colorGrid = st.getColorCodeGrid();
	color1 = st.getColorCodeChar1();
	color2 = st.getColorCodeChar2();

	gotoXY(115, 10);
	printf("SETTINGS:");
	gotoXY(115, 12);
	printf("size:            ");
	printf("%d", n);

	gotoXY(115, 13);
	printf("Player 1 symbol: ");
	printf("%c", (char)a);

	gotoXY(115, 14);
	printf("Player 2 symbol: ");
	printf("%c", (char)b);

	gotoXY(115, 15);
	printf("Sound On/Off:    ");
	if (sound) printf("On");
	else printf("Off");

	gotoXY(115, 16);
	printf("Grid color:      ");
	printf("%s", st.getColor(colorGrid));

	gotoXY(115, 17);
	printf("Player 1 color:  ");
	printf("%s", st.getColor(color1));

	gotoXY(115, 18);
	printf("Player 2 color:  ");
	printf("%s", st.getColor(color2));

	gotoXY(115, 19);
	printf("Save change");


	gotoXY(115, 20);
	printf("Return");

	cur = { 112, 12 };
	gotoXY(cur);
	printf(">>");

	INPUT_RECORD InputRecord;
	DWORD Events;

	while (status.getStatus() == STATUS_SETTING)
	{
		ReadConsoleInput(hin, &InputRecord, 1, &Events);

		if (InputRecord.EventType == KEY_EVENT)
		{
			KeyEventProc(InputRecord.Event.KeyEvent);
		}
	}
}

void LoadSetting()
{
	readSettingFile(st);
	player[0].setPlayerChar(st.getCharP1());
	player[1].setPlayerChar(st.getCharP2());
	gp.setSize(st.getSize());
	TextColor(st.getColorCodeGrid());
	drawGrid(st.getSize());
	//PlaySound(TEXT("dive.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
	mciSendString("open \"dive.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
	if (st.getSoundOn())
	{
		mciSendString("play mp3 repeat", NULL, 0, NULL);
	}
	else
	{
		mciSendString("pause mp3", NULL, 0, NULL);
	}
}

void SaveSetting(int n, int a, int b, bool sound, int colorGrid, int color1, int color2)
{
	st.setCharP1((char)a);
	st.setCharP2((char)b);
	st.setColorCodeChar1(color1);
	st.setColorCodeChar2(color2);
	st.setSound((bool)sound);
	st.setColorCodeGrid(colorGrid);
	st.setSize(n);

	player[0].setPlayerChar(st.getCharP1());
	player[1].setPlayerChar(st.getCharP2());
	if (st.getSize() != gp.getSize())
	{
		clearGrid();
		gp.clear();
		gp.setSize(st.getSize());
		TextColor(st.getColorCodeGrid());
		drawGrid(st.getSize());
		resumepvp = false;
		resumepvc = true;
	}
	else 
	{
		TextColor(st.getColorCodeGrid());
		drawGrid(st.getSize());
		Load(gp);
	}

	if (st.getSoundOn())
	{
		mciSendString("play mp3 repeat", NULL, 0, NULL);
	}
	else
	{
		mciSendString("pause mp3", NULL, 0, NULL);
	}

	writeSettingFile(st);
	TextColor(st.getColorCodeGrid());
	Message("Saved settings!");
}

void StatisticMenu()
{
	TextColor(st.getColorCodeGrid());
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
	printf("%d", statis.GetTotal());

	gotoXY(117, 14);
	printf("Player 1 win:         ");
	printf("%d", statis.GetWinP1());

	gotoXY(117, 15);
	printf("Player 2 win:         ");
	printf("%d", statis.GetWinP2());

	gotoXY(117, 16);
	printf("Draw game:            ");
	printf("%d", statis.GetDraw());

	gotoXY(117, 17);
	printf("Player 1 total move:  ");
	printf("%d", statis.GetMoveP1());

	gotoXY(117, 18);
	printf("Player 2 total move:  ");
	printf("%d", statis.GetMoveP2());

	gotoXY(117, 19);
	printf("Player 1 win percent: ");
	printf("%.2lf", statis.GetWinPercentP1());

	gotoXY(117, 20);
	printf("Player 2 win percent: ");
	printf("%.2lf", statis.GetWinPercentP2());

	gotoXY(117, 21);
	printf("Draw percent:         ");
	printf("%.2lf", statis.GetDrawPercent());
}

void LoadStatFile()
{
	readStatFile(statis);
}

int main()
{
	setConsoleWindow();
	setMode();

	LoadSplash();

	LoadAbout();

	banner();
	setcursor(false, 0);
	
	LoadSetting();
	LoadStatFile();

	INPUT_RECORD InputRecord;
	DWORD Events;
	
	while (1)
	{
		ReadConsoleInput(hin, &InputRecord, 1, &Events);

		if (InputRecord.EventType == KEY_EVENT)
		{
			KeyEventProc(InputRecord.Event.KeyEvent);
		}

		if (status.getStatus() == STATUS_EXIT) break;
	}
	
	//system("pause");
	writeStatFile(statis);
	return 0;
}