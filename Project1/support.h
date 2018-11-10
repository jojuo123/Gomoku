
#ifndef SUPPORT_H
#define SUPPORT_H

#include <Windows.h>

const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
const HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);


void gotoXY(int x, int y);

void TextColor(int color);

void drawGrid(int size);

void gotoXY(COORD cur);

void setConsoleWindow();

void setMode();

bool isInBanner(int, int);

bool isInGrid(int, int);

bool isInRightSide(int, int);

int toXarray(int x);

int toYarray(int y);

int toXconsole(int x);

int toYconsole(int y);

void clearRightSide();

void clearGrid();

void setcursor(bool visible, DWORD size);

#endif // !SUPPORT_H
