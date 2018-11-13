#include "GamePlay.h"

bool GamePlay::win(int x, int y)
{
	return (fiveInColumn(x, y) || fiveInRow(x, y) || fiveInMainDiagonal(x, y) || fiveInReverseDiagonal(x, y));
}

bool GamePlay::draw()
{
	return (count == size * size);
}

void GamePlay::clear()
{
	count = 0;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			board[i][j] = 0;
}

bool GamePlay::isEmpty(int x, int y)
{
	if (!inBoard(x, y)) return false;
	return (board[x][y] == 0);
}

void GamePlay::set(int x, int y, int no)
{
	board[x][y] = no + 1;
	count++;
}

int GamePlay::get(int x, int y)
{
	return board[x][y] - 1;
}

bool GamePlay::inBoard(int x, int y)
{
	return (x >= 0 && x < size && y >= 0 && y < size);
}

bool GamePlay::fiveInRow(int x, int y)
{
	int k = 1, c = 1;
	int cur = board[x][y];
	while (y - k >= 0 && board[x][y - k] == cur) {
		k++; c++;
	}

	k = 1;
	while (y + k < size && board[x][y + k] == cur) {
		k++; c++;
	}

	return (c >= 5);
}

bool GamePlay::fiveInColumn(int x, int y)
{
	int k = 1, c = 1;
	int cur = board[x][y];
	while (x - k >= 0 && board[x - k][y] == cur) {
		k++; c++;
	}

	k = 1;
	while (x + k < size && board[x + k][y] == cur) {
		k++; c++;
	}

	return (c >= 5);
}

bool GamePlay::fiveInMainDiagonal(int x, int y)
{
	int k = 1, c = 1;
	int cur = board[x][y];
	while (x - k >= 0 && y - k >= 0 && board[x - k][y - k] == cur) {
		k++; c++;
	}

	k = 1;
	while (x + k < size && y + k < size && board[x + k][y + k] == cur) {
		k++; c++;
	}

	return (c >= 5);
}

bool GamePlay::fiveInReverseDiagonal(int x, int y)
{
	int k = 1, c = 1;
	int cur = board[x][y];
	while (x - k >= 0 && y + k < size && board[x - k][y + k] == cur) {
		k++; c++;
	}

	k = 1;
	while (x + k < size && y - k >= 0 && board[x + k][y - k] == cur) {
		k++; c++;
	}

	return (c >= 5);
}
