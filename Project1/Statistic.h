#ifndef STATISTIC_H

#define STATISTIC_H

class Statistic {
private:
	int totalGame;
	int winP1;
	int winP2;
	int draw;
	int moveP1;
	int moveP2;
public:
	void increaseTotal() {
		totalGame++;
	}
	void increaseWinP1() {
		winP1++;
	}
	void increaseWinP2() {
		winP2++;
	}
	void increaseDraw() {
		draw++;
	}
	int GetTotal() {
		return totalGame;
	}
	void setTotal(int a) {
		totalGame = a;
	}
	int GetWinP1() {
		return winP1;
	}
	void setWinP1(int a) {
		winP1 = a;
	}
	int GetWinP2() {
		return winP2;
	}
	void setWinP2(int a) {
		winP2 = a;
	}
	int GetDraw() {
		return draw;
	}
	void setDraw(int a) {
		draw = a;
	}
	int GetMoveP1() {
		return moveP1;
	}
	void setMoveP1(int a) {
		moveP1 = a;
	}
	int GetMoveP2() {
		return moveP2;
	}
	void setMoveP2(int a) {
		moveP2 = a;
	}
	double GetWinPercentP1() {
		if (totalGame != 0)
		return (double)winP1 / totalGame * 100;
		else return 0.0;
	}
	double GetWinPercentP2() {
		if (totalGame != 0)
		return (double)winP2 / totalGame * 100;
		else return 0.0;
	}
	double GetDrawPercent() {
		if (totalGame != 0)
		return (double)draw / totalGame * 100;
		else return 0.0;
	}
	void updatePvP(int k, int mp1, int mp2) {
		switch (k) 
		{
			case -1: this->increaseDraw(); break;
			case 0: this->increaseWinP1(); break;
			case 1: this->increaseWinP2(); break;
		}
		this->increaseTotal();
		moveP1 += mp1;
		moveP2 += mp2;
	}
};

#endif // !1

