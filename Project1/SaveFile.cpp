#include <iostream>
#include <fstream>
#include "SaveFile.h"
#include <string>

void readSaveFile(GamePlay & gp, Player & p1, Player & p2, int id, Computer & computer)
{
	std::ifstream fin;

	string fi("savegame");
	fi= fi + std::to_string(id);
	fi = fi + ".out";

	fin.open(fi);
	
	int n, cur, com, tmp, level;
	int move1 = 0, move2 = 0;

	fin >> n; 
	gp.setSize(n);
	fin >> cur;
	fin >> com;
	fin >> level;
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < n; j++) 
		{
			fin >> tmp; 
			if (tmp >=0 && tmp <=2) gp.set(i, j, tmp - 1);
			if (tmp == 1) move1++;
			if (tmp == 2) move2++;
		}
	gp.setCurrent(cur);
	p1.setComputer(false);
	if (com == 1) p2.setComputer(true);
	else p2.setComputer(false);
	p1.setMove(move1);
	p2.setMove(move2);
	computer.setLevel(level);

	fin.close();
}

void writeSaveFile(GamePlay gp, Player p1, Player p2, int id, Computer computer)
{
	std::ofstream fout;

	string fo("savegame");
	fo = fo + std::to_string(id);
	fo = fo + ".out";

	fout.open(fo);

	fout << gp.getSize() << endl;
	fout << gp.getCurrent() << endl;

	if (p2.getComputer()) fout << "1" << endl;
	else fout << "0" << endl;

	if (p2.getComputer()) fout << computer.getLevel() << endl;
	else fout << "0" << endl;

	for (int i = 0; i < gp.getSize(); i++)
	{
		for (int j = 0; j < gp.getSize(); j++)
		{
			fout << gp.get(i, j) + 1 << " ";
		}
		fout << endl;
	}

	fout.close();
}

void readSettingFile(Setting & setting)
{
	std::ifstream fin;
	fin.open("setting.out");

	int size, a, b, colorCodeGrid, colorCodeChar1, colorCodeChar2, sound;

	fin >> size >> a >> b >> sound >> colorCodeGrid >> colorCodeChar1 >> colorCodeChar2;

	setting.setCharP1((char)a);
	setting.setCharP2((char)b);
	setting.setColorCodeChar1(colorCodeChar1);
	setting.setColorCodeChar2(colorCodeChar2);
	setting.setSound((bool)sound);
	setting.setColorCodeGrid(colorCodeGrid);
	setting.setSize(size);

	fin.close();
}

void writeSettingFile(Setting setting)
{
	std::ofstream fout;
	fout.open("setting.out");

	fout << setting.getSize() << " ";
	fout << (int)setting.getCharP1() << " ";
	fout << (int)setting.getCharP2() << " ";
	if (setting.getSoundOn()) fout << "1 ";
	else fout << "0 ";
	fout << setting.getColorCodeGrid() << " ";
	fout << setting.getColorCodeChar1() << " ";
	fout << setting.getColorCodeChar2() << " ";

	fout.close();
}

void readStatFile(Statistic & statis)
{
	std::ifstream fin;
	fin.open("statistic.out");

	int n, p1, p2, d, mp1, mp2;

	fin >> n >> p1 >> p2 >> d >> mp1 >> mp2;

	statis.setTotal(n);
	statis.setWinP1(p1);
	statis.setWinP2(p2);
	statis.setDraw(d);
	statis.setMoveP1(mp1);
	statis.setMoveP2(mp2);

	fin.close();
}

void writeStatFile(Statistic statis)
{
	std::ofstream fout;
	fout.open("statistic.out");

	fout << statis.GetTotal() << " ";
	fout << statis.GetWinP1() << " ";
	fout << statis.GetWinP2() << " ";
	fout << statis.GetDraw() << " ";
	fout << statis.GetMoveP1() << " ";
	fout << statis.GetMoveP2() << " ";

	fout.close();
}
