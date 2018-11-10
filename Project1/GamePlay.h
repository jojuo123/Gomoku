#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <iostream>

using namespace std;

const int N = 21;

class GamePlay
{
	private:
		int board[N][N];
		int size;
		int count;
		int currentPlayer;
	public:
		void setCount(int a) {
			count = a;
		}
		int getSize() {
			return size;
		}
		void setSize(int i) {
			size = i;
		}
		bool win(int x, int y);
		bool draw();
		void clear();
		int getCurrent() {
			return currentPlayer;
		}
		void setCurrent(int a) {
			currentPlayer = a;
		}
		bool isEmpty(int x, int y);
		void set(int x, int y, int no);
		int get(int x, int y);
		bool inBoard(int x, int y);
		bool fiveInRow(int x, int y);
		bool fiveInColumn(int x, int y);
		bool fiveInMainDiagonal(int x, int y);
		bool fiveInReverseDiagonal(int x, int y);
		GamePlay() {
			this->clear();
			currentPlayer = 0;
			count = 0;
		}
};

#endif // !1

