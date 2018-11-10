#include <iostream>
#include <cstdio>
#include <Windows.h>
#include "support.h"

void gotoXY(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(hout, coord);
}

void TextColor(int color)
{
	SetConsoleTextAttribute(hout, color);
}

void drawGrid(int size)
{
	int x = 0, y = 10;
	gotoXY(x, y);
	for (int i = 0; i < size * 2 + 1; i++) {
		for (int j = 0; j < size + 1; j++) {
			if (i % 2 == 0 && j < size)
				printf("%c%c%c%c", 197, 196, 196, 196);
			else if (i % 2 == 0)
				printf("%c", 197);
			else
				printf("%c   ", 179);
		}
		printf("\n");
	}
}

void gotoXY(COORD co)
{
	gotoXY(co.X, co.Y);
}

void setConsoleWindow()
{
	CONSOLE_SCREEN_BUFFER_INFO SBInfo;
	COORD coord;
	GetConsoleScreenBufferInfo(hout, &SBInfo);
	coord.X = 120;
	coord.Y = 50;
	SetConsoleScreenBufferSize(hout, coord);
	SetConsoleDisplayMode(hout, CONSOLE_FULLSCREEN_MODE, 0);
}

void setMode()
{
	SetConsoleMode(hin, ENABLE_EXTENDED_FLAGS);
	SetConsoleMode(hin, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
}

bool isInBanner(int x, int y)
{
	return (x >= 0 && x <= 80 && y >= 0 && y <= 10);
}

bool isInGrid(int x, int y)
{
	return (x >= 0 && x <= 80 && y >= 11);
}

bool isInRightSide(int x, int y)
{
	return (x >= 81);
}

int toXarray(int x)
{
	return (x - 2) / 4;
}

int toYarray(int y)
{
	return (y - 11) / 2;
}

int toXconsole(int x)
{
	return 4 * x + 2;
}

int toYconsole(int y)
{
	return 2 * y + 11;
}

void clearRightSide()
{
	for (int i = 0; i < 50; i++)
	{
		gotoXY(81, i);
		for (int j = 0; j < 80; j++) {
			printf(" ");
		}
	}
}

void clearGrid()
{
	for (int i = 10; i < 55; i++)
	{
		gotoXY(0, i);
		for (int j = 0; j <= 80; j++) printf(" ");
	}
}

void setcursor(bool visible, DWORD size) // set bool visible = 0 - invisible, bool visible = 1 - visible
{
	if (size == 0)
	{
		size = 20;	// default cursor size Changing to numbers from 1 to 20, decreases cursor width
	}
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(hout, &lpCursor);
}
