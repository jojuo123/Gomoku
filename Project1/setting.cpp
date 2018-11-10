#include "setting.h"

void Setting::Save(Player & p1, Player & p2)
{
	p1.setPlayerChar(this->p1);
	p2.setPlayerChar(this->p2);
}

char * Setting::getColor(int i)
{
	static char colorCode[16][12] = {
		"      Black",
		"  Dark Blue",
		" Dark Green",
		"  Dark Cyan",
		"   Dark Red",
		"  Dark Pink",
		"Dark Yellow",
		" Dark White",
		"       Grey",
		"       Blue",
		"      Green",
		"       Cyan",
		"        Red",
		"       Pink",
		"     Yellow",
		"      White",
	};
	return colorCode[i];
}


