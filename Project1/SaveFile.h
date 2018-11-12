#ifndef FILE_H_

#define FILE_H_

#include <iostream>
#include <fstream>
#include "GamePlay.h"
#include "Player.h"
#include "setting.h"
#include "Statistic.h"
#include "Computer.h"

void readSaveFile(GamePlay &gp, Player &p1, Player &p2, int id, Computer & computer);
void writeSaveFile(GamePlay gp, Player p1, Player p2, int id, Computer computer);
void readSettingFile(Setting & setting);
void writeSettingFile(Setting setting);
void readStatFile(Statistic & statis);
void writeStatFile(Statistic statis);

#endif // !FILE_H_

