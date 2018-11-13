#include <iostream>
#include <cstdio>
#include <Windows.h>
#include "support.h"
#include <map>

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

void LoadSplash()
{
	char INTRO[10][50] = {
		"GGGGGG  OOOOOO  MM     M  OOOOOO  KK   KK  UU   U",
		"GGGGGG  OOOOOO  MMM   MM  OOOOOO  KK   KK  UU   U",
		"GG      OO   O  MMMM MMM  OO   O  KK  KK   UU   U",
		"GG      OO   O  MM MMM M  OO   O  KK KK    UU   U",
		"GG      OO   O  MM  M  M  OO   O  KKKK     UU   U",
		"GG      OO   O  MM     M  OO   O  KKK      UU   U",
		"GG GGG  OO   O  MM     M  OO   O  KK K     UU   U",
		"GG   G  OO   O  MM     M  OO   O  KK  K    UU   U",
		"GG   G  OO   O  MM     M  OO   O  KK   K   UUUUUU",
		"GGGGGG  OOOOOO  MM     M  OOOOOO  KK    K  UUUUUU"
	};

	std::map<char, int> COLOR = { { 'G', 10 },{ 'O', 9 },{ 'M', 3 },{ 'K', 14 },{ 'U', 12 } };

	COORD currentCO = { 60, 20 };

	setcursor(false, 0);

	gotoXY(currentCO);

	for (int j = 0; j < 50; j++) {	//cot

		gotoXY(currentCO);

		for (int i = 0; i < 10; i++) {	//dong
			
			TextColor(COLOR[INTRO[i][j]]);
			printf("%c", INTRO[i][j]);

			currentCO.Y++;

			gotoXY(currentCO);
		}

		currentCO.X++;
		currentCO.Y = 20;

		Sleep(10);
	}

	currentCO.X = 60;
	currentCO.Y = 20;
	gotoXY(currentCO);

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 50; j++) printf(" ");
		currentCO.Y++;
		gotoXY(currentCO);
		Sleep(10);
	}
}

void printAPCS()
{
	gotoXY(50, 20);
	printf("       :i11ri+ri+i   ii++ii+++++rk:      ,i11kf1*ri    -fii}i}i}}k  \n");
	gotoXY(50, 21);
	printf("     iri}iiiiiiiii   +iiiiiiiiiii}i1   'krrr1rk1rr1   :Izi||ii}}|i  \n");
	gotoXY(50, 22);
	printf("    1fi++iiiiiir+ii :ii+ir+i+iiii+i}i  r111r11r1r1f:  iIi})i|?iif)i \n");
	gotoXY(50, 23);
	printf("   1i++iir1i1*ki1k-  i111ik:::iiii+i1 ir1111*i::_---  i|ii}Ik::i,i, \n");
	gotoXY(50, 24);
	printf("  ri++ri1_  +}+ii1   kii+fr    riiii1 fr1111.         +Ii}}}r       \n");
	gotoXY(50, 25);
	printf(" ii+++ik    1iii++   1iriir   1+iii}: f11f1i           i|}|i)ii     \n");
	gotoXY(50, 26);
	printf(" riiiii1rrkr+iiii1   i}ii+r:i+i+r+ir  r1r1f*            rziIiii1    \n");
	gotoXY(50, 27);
	printf(" ++i+r+iiiifiii+i1   1iiri+i}+irii1   i1fk1i             1i}i)f?i   \n");
	gotoXY(50, 27);
	printf(" iriiii}iiiiri+i+f   1i+iriiiiiiri    :1111ri             ii)I)iI+- \n");
	gotoXY(50, 28);
	printf(" i++iir11i11+i+i+1   iii+iiiir*,       ir111ri.             r}iiIIr \n");
	gotoXY(50, 29);
	printf(" r+i+i1     riri+r   iiii+ir:'          1f1f11ii,'-  i:i::ik?I}}ii: \n");
	gotoXY(50, 30);
	printf(" kiiii+'    1iii+1   ii+i+r              k1rr1krrrri  i}}f|}Ii}ii}i.\n");
	gotoXY(50, 31);
	printf(" :iririk    1ii+ir   iiii}+'              -1111rrrr,  :zfi|}}i?iIii \n");
	gotoXY(50, 32);
	printf("  1iiiiii   1rrrr1   ii+ri1                 -:ik1ki    +iiiiiiir1:  \n");
	gotoXY(50, 33);
	printf("   iiiik-                                               .           \n");
	gotoXY(50, 34);
	printf("   -1:-                                                             \n");

}

void LoadAbout()
{
	TextColor(13);
	printAPCS();
	Sleep(1000);
	system("cls");

	TextColor(15);
	gotoXY(50, 0);
	printf("       --       .ro-                                                                 \n");
	gotoXY(50, 1);
	printf("      oiri      .!i-                                 ,__                             \n");
	gotoXY(50, 2);
	printf("     :iiii_     oii-                                 iio                             \n");
	gotoXY(50, 3);
	printf("     *i*o!i-    _ii-_*o_:     :.*ro:    :__   -o_- _*ri*_.       _.:   ,_o-  ,_rr*o  \n");
	gotoXY(50, 4);
	printf("    :i!- ii.    o!iii*i!i:  ,r!irriir-  iir   :if_ riiiirr       i!r   _ii: ,iir*ii- \n");
	gotoXY(50, 5);
	printf("    rir  *!!:   _ii*  -rii  rir-  ,ri*  o!*   ,ii_   ii*         i!*   ,!i, r!r,     \n");
	gotoXY(50, 6);
	printf("   _i!_ -:iir   oii-   _i!::i!.    .ii- rir   -ii_   rir         rio   ,!i: _iiir_-  \n");
	gotoXY(50, 7);
	printf("   iiiiiiiiii:  .ii-   :i!-:!i.    oii, rfi   ,ii_   ri_         rio   _!i:  ,_oiii_ \n");
	gotoXY(50, 8);
	printf("  _!i.__.:.iir  oiio   rii, iir   -r!i  rii   .ii_   ii.         rir   iii_     :iir \n");
	gotoXY(50, 9);
	printf(" -i!r      oii_ o!iir.iii_  ,iiiooiii,  _!ir*iiif_   r!iro-      _iir_iii!_ _r*.*!i, \n");
	gotoXY(50, 10);
	printf(" :*r:      ,r*o :r_:*rr*:    ,_*iro_     :r*r.,**:    orir-       _ri*_-ro, :irrr_-  \n");

	Sleep(200);

	gotoXY(50, 20);
	printf("This is a progam to play Gomoku with computer and player!!!");
	gotoXY(50, 21);
	printf("Do not rage, or you will be regreted.");

	TextColor(10);
	gotoXY(50, 48);
	printf("Version beta v6.1.99");
	gotoXY(50, 49);
	printf("Created by Vu Tran Duy");
	//gotoXY(midX(88), 22);

	/*TextColor(7);
	for (int i = 0; i <= 100; i++) {
		gotoXY(50, 25);
		for (int j = 1; j <= 3; j++) {
			printf(".");
			Sleep(1);
		}
		gotoXY(50 + 3, 25);
		printf("%d", i);
		Sleep(1);
	}*/
	//for (int i = 0; i < 10; i++)
	//	printf("%c", 196);

	Sleep(1000);
	system("cls");
	//drawGrid(20);
}
