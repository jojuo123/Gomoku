#ifndef SETTING_H_

#define SETTING_H_

#include "Player.h"

class Setting 
{
private:
	char p1, p2;
	int size;
	bool soundOn;
	int colorCodeGrid;
	int colorCodeChar1, colorCodeChar2;
public:
	char getCharP1() {
		return p1;
	}
	void setCharP1(char a) {
		p2 = a;
	}
	char getCharP2() {
		return p2;
	}
	void setCharP2(char a) {
		p2 = a;
	}
	bool getSoundOn() {
		return soundOn;
	}
	void setSound(bool a) {
		soundOn = a;
	}
	int getColorCodeGrid() {
		return colorCodeGrid;
	}
	void setColorCodeGrid(int a) {
		colorCodeGrid = a;
	}
	int getColorCodeChar1() {
		return colorCodeChar1;
	}
	void setColorCodeChar1(int a) {
		colorCodeChar1 = a;
	}
	int getColorCodeChar2() {
		return colorCodeChar2;
	}
	void setColorCodeChar2(int a) {
		colorCodeChar2 = a;
	}
	void Save(Player& p1, Player& p2);
	int getSize() {
		return size;
	}
	void setSize(int i) {
		size = i;
	}
	char * getColor(int i);
	Setting() 
	{
		p1 = 'X';
		p2 = 'O';
		soundOn = true;
	}
};

#endif // !1
