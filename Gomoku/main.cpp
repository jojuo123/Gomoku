#include <cstdio>
#include <iostream>
#include <cstring>
#include <map>
#include <conio.h>
#include <Windows.h>

#define HEIGHT 50
#define WIDTH 150
#define SPACE 2

using namespace std;

enum huong
{
	LEFT, RIGHT, UP, DOWN
};

struct COO
{
	int x, y;
	COO (int _x, int _y)
	{
		x = _x;
		y = _y;
	}

	COO() {}
};

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

map<char, int> COLOR = { {'G', 10}, {'O', 9}, {'M', 3}, {'K', 14}, {'U', 12} };

COO currentCO;

void gotoXY(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void gotoXY(COO co)
{
	gotoXY(co.x, co.y);
}

void TextColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void SetWindow(int Width, int Height)
{
	_COORD coord;
	coord.X = Width;
	coord.Y = Height;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = Height - 1;
	Rect.Right = Width - 1;

	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle 
	SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size 
	SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size 
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
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &lpCursor);
}

int midX(int size)
{
	return (150 - size) / 2;
}

void LoadSplash() 
{
	int X0 = midX(39 + SPACE * 5);
	int Y0 = 20;

	setcursor(0, 0);

	currentCO = COO(X0, Y0);

	gotoXY(currentCO);
	
	for (int j = 0; j < 50; j++) {	//cot
		
		gotoXY(currentCO);

		for (int i = 0; i < 10; i++) {	//dong

			TextColor(COLOR[INTRO[i][j]]);
			printf("%c", INTRO[i][j]);

			currentCO.y++;

			gotoXY(currentCO);
		}

		currentCO.y = Y0;
		currentCO.x++;
		
		Sleep(100);
	}

	currentCO.x = X0;
	currentCO.y = Y0;
	gotoXY(currentCO);

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 50; j++) printf(" ");
		currentCO.y++;
		gotoXY(currentCO);
		Sleep(100);
	}
}

void printAPCS() 
{
	gotoXY(midX(70), 20);
	printf("       :i11ri+ri+i   ii++ii+++++rk:      ,i11kf1*ri    -fii}i}i}}k  \n");
	gotoXY(midX(70), 21);
	printf("     iri}iiiiiiiii   +iiiiiiiiiii}i1   'krrr1rk1rr1   :Izi||ii}}|i  \n");
	gotoXY(midX(70), 22);
	printf("    1fi++iiiiiir+ii :ii+ir+i+iiii+i}i  r111r11r1r1f:  iIi})i|?iif)i \n");
	gotoXY(midX(70), 23);
	printf("   1i++iir1i1*ki1k-  i111ik:::iiii+i1 ir1111*i::_---  i|ii}Ik::i,i, \n");
	gotoXY(midX(70), 24);
	printf("  ri++ri1_  +}+ii1   kii+fr    riiii1 fr1111.         +Ii}}}r       \n");
	gotoXY(midX(70), 25);
	printf(" ii+++ik    1iii++   1iriir   1+iii}: f11f1i           i|}|i)ii     \n");
	gotoXY(midX(70), 26);
	printf(" riiiii1rrkr+iiii1   i}ii+r:i+i+r+ir  r1r1f*            rziIiii1    \n");
	gotoXY(midX(70), 27);
	printf(" ++i+r+iiiifiii+i1   1iiri+i}+irii1   i1fk1i             1i}i)f?i   \n");
	gotoXY(midX(70), 27);
	printf(" iriiii}iiiiri+i+f   1i+iriiiiiiri    :1111ri             ii)I)iI+- \n");
	gotoXY(midX(70), 28);
	printf(" i++iir11i11+i+i+1   iii+iiiir*,       ir111ri.             r}iiIIr \n");
	gotoXY(midX(70), 29);
	printf(" r+i+i1     riri+r   iiii+ir:'          1f1f11ii,'-  i:i::ik?I}}ii: \n");
	gotoXY(midX(70), 30);
	printf(" kiiii+'    1iii+1   ii+i+r              k1rr1krrrri  i}}f|}Ii}ii}i.\n");
	gotoXY(midX(70), 31);
	printf(" :iririk    1ii+ir   iiii}+'              -1111rrrr,  :zfi|}}i?iIii \n");
	gotoXY(midX(70), 32);
	printf("  1iiiiii   1rrrr1   ii+ri1                 -:ik1ki    +iiiiiiir1:  \n");
	gotoXY(midX(70), 33);
	printf("   iiiik-                                               .           \n");
	gotoXY(midX(70), 34);
	printf("   -1:-                                                             \n");

}

void LoadAbout()
{
	TextColor(13);
	printAPCS();
	Sleep(1000);
	system("cls");

	TextColor(15);
	gotoXY(midX(88), 0);
	printf("       --       .ro-                                                                 \n");
	gotoXY(midX(88), 1);
	printf("      oiri      .!i-                                 ,__                             \n");
	gotoXY(midX(88), 2);
	printf("     :iiii_     oii-                                 iio                             \n");
	gotoXY(midX(88), 3);
	printf("     *i*o!i-    _ii-_*o_:     :.*ro:    :__   -o_- _*ri*_.       _.:   ,_o-  ,_rr*o  \n");
	gotoXY(midX(88), 4);
	printf("    :i!- ii.    o!iii*i!i:  ,r!irriir-  iir   :if_ riiiirr       i!r   _ii: ,iir*ii- \n");
	gotoXY(midX(88), 5);
	printf("    rir  *!!:   _ii*  -rii  rir-  ,ri*  o!*   ,ii_   ii*         i!*   ,!i, r!r,     \n");
	gotoXY(midX(88), 6);
	printf("   _i!_ -:iir   oii-   _i!::i!.    .ii- rir   -ii_   rir         rio   ,!i: _iiir_-  \n");
	gotoXY(midX(88), 7);
	printf("   iiiiiiiiii:  .ii-   :i!-:!i.    oii, rfi   ,ii_   ri_         rio   _!i:  ,_oiii_ \n");
	gotoXY(midX(88), 8);
	printf("  _!i.__.:.iir  oiio   rii, iir   -r!i  rii   .ii_   ii.         rir   iii_     :iir \n");
	gotoXY(midX(88), 9);
	printf(" -i!r      oii_ o!iir.iii_  ,iiiooiii,  _!ir*iiif_   r!iro-      _iir_iii!_ _r*.*!i, \n");
	gotoXY(midX(88), 10);
	printf(" :*r:      ,r*o :r_:*rr*:    ,_*iro_     :r*r.,**:    orir-       _ri*_-ro, :irrr_-  \n");

	Sleep(200);

	gotoXY(midX(88), 20);
	printf("This is a progam to play Gomoku with computer and player!!!");
	gotoXY(midX(88), 21);
	printf("Do not rage, or you will be regreted.");
	
	TextColor(10);
	gotoXY(midX(88), 48);
	printf("Version beta v6.1.99");
	gotoXY(midX(88), 49);
	printf("Created by Vu Tran Duy (so HOTTTTT)");
	//gotoXY(midX(88), 22);
	
	TextColor(7);
	for (int i = 0; i <= 100; i++) {
		gotoXY(midX(88), 25);
		for (int j = 1; j <= 3; j++) {
			printf(".");
			Sleep(2);
		}
		gotoXY(midX(88) + 3, 25);
		printf("%d", i); 
		Sleep(2); 
	}

	gotoXY(midX(88), 27);
	printf("Press enter to continue...");

	
}

int main() 
{
	SetWindow(WIDTH, HEIGHT);
	//LoadSplash();

	//LoadAbout();	

	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD InputRecord;
	DWORD Events;
	COORD coord;
	//DWORD fdwMode = ENABLE_EXTENDED_FLAGS;
	SetConsoleMode(hin, ENABLE_EXTENDED_FLAGS);
	/*
	Step-2:
	Enable the window and mouse input events,
	after you have already applied that 'ENABLE_EXTENDED_FLAGS'
	to disable 'Quick Edit Mode'
	*/
	SetConsoleMode(hin, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
	COORD cur; cur.X = 0; cur.Y = 0;
	while (1) 
	{
		ReadConsoleInput(hin, &InputRecord, 1, &Events);
		
		if (InputRecord.EventType == MOUSE_EVENT) 
		{
			
			//if (InputRecord.Event.MouseEvent.dwButtonState )
			if (InputRecord.Event.MouseEvent.dwEventFlags == MOUSE_MOVED) {
				gotoXY(InputRecord.Event.MouseEvent.dwMousePosition.X, InputRecord.Event.MouseEvent.dwMousePosition.Y);
			}
			else
			if ((InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) && cur.X == 0 && cur.Y == 0) 
			{
				cur.X = InputRecord.Event.MouseEvent.dwMousePosition.X;
				cur.Y = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			}
			else
				if (InputRecord.Event.MouseEvent.dwButtonState != FROM_LEFT_1ST_BUTTON_PRESSED) {
					if (cur.X == InputRecord.Event.MouseEvent.dwMousePosition.X && cur.Y == InputRecord.Event.MouseEvent.dwMousePosition.Y && (cur.X != 0 || cur.Y != 0)) {
						printf("X");
						//cur = { 0, 0 };
					}
					cur = { 0, 0 };
				}
		}
	}

	return 0;
}

