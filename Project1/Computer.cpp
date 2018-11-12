#include "Computer.h"

const int MAX_VAL = (int)trunc(1e9);
const int MIN_VAL = -(int)trunc(1e9);

COORD Computer::nextMove(GamePlay & gp)
{
	vector<pair<int, int> > Coord;
	COORD res = { -1, -1 };
	int maxval = MIN_VAL;
	int alpha = MIN_VAL;
	int beta = MAX_VAL;

	for (int i = 0; i < gp.getSize(); i++)
		for (int j = 0; j < gp.getSize(); j++)
			if (gp.isEmpty(i, j) && PlayArea(gp, i, j)) Coord.push_back(make_pair(i, j));

	for (int i = 0; i < (int)Coord.size(); i++)
	{
		int tmp = minimax(gp, 1, 0, Coord[i].first, Coord[i].second, alpha, beta);
		if (tmp > maxval)
		{
			maxval = tmp;
			res.X = Coord[i].first;
			res.Y = Coord[i].second;
		}
		if (maxval > alpha)
			alpha = maxval;
		//if (alpha >= beta)
		//	break;
	}

	if (res.X == -1 || res.Y == -1)
	{
		for (int i = 0; i < gp.getSize(); i++)
			for (int j = 0; j < gp.getSize(); j++)
				if (gp.isEmpty(i, j))
				{
					res.X = i; res.Y = j;
					return res;
				}
	}

	return res;
}

int Computer::Depth(int level)
{
	if (level == 1) return 1;
	else return 3;
}

//current player = 0 => choose max value
int Computer::minimax(GamePlay & gp, int depth, int currentPlayer, int x, int y, int alpha, int beta)
{
	gp.set(x, y, currentPlayer ^ 1);

	if (gp.win(x, y))
	{
		gp.set(x, y, -1);
		if (currentPlayer == 0) return MAX_VAL;
		else return MIN_VAL;
	} 
	if (gp.draw())
	{
		gp.set(x, y, -1);
		return 0;
	}
	if (depth == Depth(level))
	{
		int value = evaluation(gp);
		gp.set(x, y, -1);
		return value;
	}

	vector<pair<int, int> > Coord;
	for (int i = 0; i < gp.getSize(); i++)
		for (int j = 0; j < gp.getSize(); j++)
			if (gp.isEmpty(i, j) && PlayArea(gp, i, j)) Coord.push_back(make_pair(i, j));
	
	int len = (int)Coord.size();

	if (currentPlayer == 0) // lay min 
	{
		int minval = MAX_VAL;
		for (int i = 0; i < len; i++)
		{
			int tmp = minimax(gp, depth + 1, 1, Coord[i].first, Coord[i].second, alpha, beta);
			if (minval > tmp) 
				minval = tmp;
			if (beta > minval)
				beta = minval;
			//if (beta <= alpha)
			//	break;
		}

		gp.set(x, y, -1);
		return minval;
	}
	else 
	{
		int maxval = MIN_VAL;
		for (int i = 0; i < len; i++)
		{
			int tmp = minimax(gp, depth + 1, 0, Coord[i].first, Coord[i].second, alpha, beta);
			if (tmp > maxval)
				maxval = tmp;
			if (maxval > alpha)
				alpha = maxval;
			//if (alpha >= beta)
			//	break;
		}

		gp.set(x, y, -1);
		return maxval;
	}
}

int Computer::evaluation(GamePlay & gp)
{
	// 1: XOO 5
	// 2: OO 25
	// 3: XOOO 125 
	// 4: XOOOO 625
	// 5: OOO 1251
	// 6: OOOO 3500
	// 7: OOOOO MAX_VAL

	// 0: person
	// 1: computer
	int pattern[2][8] = { {0} };

	for (int i = 0; i < gp.getSize(); i++)
	{
		for (int j = 0; j < gp.getSize(); j++)
		{
			if (!gp.isEmpty(i, j))
			{

				int c = gp.get(i, j); //current 
				//columns
				int same = 1; 
				int k = 1;
				while (i - k >= 0 && gp.get(i - k, j) == c)
				{
					same++; k++;
				}

				int d = 1;
				while (i + d < gp.getSize() && gp.get(i + d, j) == c)
				{
					same++; d++;
				}

				if (same >= 5)
					pattern[c][7]++;
				if (same == 4 && gp.isEmpty(i - k, j) && gp.isEmpty(i + d, j))
					pattern[c][6]++;
				if (same == 3 && gp.isEmpty(i - k, j) && gp.isEmpty(i + d, j))
					pattern[c][5]++;
				if (same == 4 && ((!gp.isEmpty(i - k, j)) != (!gp.isEmpty(i + d, j))))
					pattern[c][4]++;
				if (same == 3 && ((!gp.isEmpty(i - k, j)) != (!gp.isEmpty(i + d, j))))
					pattern[c][3]++;
				if (same == 2 && gp.isEmpty(i - k, j) && gp.isEmpty(i + d, j))
					pattern[c][2]++;
				if (same == 2 && ((!gp.isEmpty(i - k, j)) != (!gp.isEmpty(i + d, j))))
					pattern[c][1]++;

				//rows
				same = 1;
				k = 1;
				while (j - k >= 0 && gp.get(i, j - k) == c)
				{
					same++; k++;
				}

				d = 1;
				while (j + d < gp.getSize() && gp.get(i, j + d) == c)
				{
					same++; d++;
				}

				if (same >= 5)
					pattern[c][7]++;
				if (same == 4 && gp.isEmpty(i, j - k) && gp.isEmpty(i, j + d))
					pattern[c][6]++;
				if (same == 3 && gp.isEmpty(i, j - k) && gp.isEmpty(i, j + d))
					pattern[c][5]++;
				if (same == 4 && ((!gp.isEmpty(i, j - k)) != (!gp.isEmpty(i, j + d))))
					pattern[c][4]++;
				if (same == 3 && ((!gp.isEmpty(i, j - k)) != (!gp.isEmpty(i, j + d))))
					pattern[c][3]++;
				if (same == 2 && gp.isEmpty(i, j - k) && gp.isEmpty(i, j + d))
					pattern[c][2]++;
				if (same == 2 && (gp.isEmpty(i, j-k) ^ gp.isEmpty(i, j+d)))
					pattern[c][1]++;

				//main diagonal
				same = 1;
				k = 1;
				while (j - k >= 0 && i - k >= 0 && gp.get(i - k, j - k) == c)
				{
					same++; k++;
				}

				d = 1;
				while (j + d < gp.getSize() && i + d < gp.getSize() && gp.get(i + d, j + d) == c)
				{
					same++; d++;
				}
				
				if (same >= 5)
					pattern[c][7]++;
				if (same == 4 && gp.isEmpty(i - k, j - k) && gp.isEmpty(i + d, j + d))
					pattern[c][6]++;
				if (same == 3 && gp.isEmpty(i - k, j - k) && gp.isEmpty(i + d, j + d))
					pattern[c][5]++;
				if (same == 4 && ((!gp.isEmpty(i - k, j - k)) != (!gp.isEmpty(i + d, j + d))))
					pattern[c][4]++;
				if (same == 3 && ((!gp.isEmpty(i - k, j - k)) != (!gp.isEmpty(i + d, j + d))))
					pattern[c][3]++;
				if (same == 2 && gp.isEmpty(i - k, j - k) && gp.isEmpty(i + d, j + d))
					pattern[c][2]++;
				if (same == 2 && ((!gp.isEmpty(i - k, j - k)) != (!gp.isEmpty(i + d, j + d))))
					pattern[c][1]++;

				//reverse diagonal
				same = 1;
				k = 1;
				while (j + k < gp.getSize() && i - k >= 0 && gp.get(i - k, j + k) == c)
				{
					same++; k++;
				}

				d = 1;
				while (j - d >= 0 && i + d < gp.getSize() && gp.get(i + d, j - d) == c)
				{
					same++; d++;
				}

				if (same >= 5)
					pattern[c][7]++;
				if (same == 4 && gp.isEmpty(i - k, j + k) && gp.isEmpty(i + d, j - d))
					pattern[c][6]++;
				if (same == 3 && gp.isEmpty(i - k, j + k) && gp.isEmpty(i + d, j - d))
					pattern[c][5]++;
				if (same == 4 && ((!gp.isEmpty(i - k, j + k)) != (!gp.isEmpty(i + d, j - d))))
					pattern[c][4]++;
				if (same == 3 && ((!gp.isEmpty(i - k, j + k)) != (!gp.isEmpty(i + d, j - d))))
					pattern[c][3]++;
				if (same == 2 && gp.isEmpty(i - k, j + k) && gp.isEmpty(i + d, j - d))
					pattern[c][2]++;
				if (same == 2 && ((!gp.isEmpty(i - k, j + k)) != (!gp.isEmpty(i + d, j - d))))
					pattern[c][1]++;
			}
		}
	}

	// 1: XOO 10
	// 2: OO 100
	// 3: XOOO 1000 
	// 4: XOOOO 10000
	// 5: OOO 10050
	// 6: OOOO 100000
	// 7: OOOOO MAX_VAL

	if (pattern[0][7] > 0) return MIN_VAL;
	if (pattern[1][7] > 0) return MAX_VAL;

	int sum = 0;
	if (level == 3)
	{
		sum += (pattern[1][1] / 2) * 10;
		sum -= (pattern[0][1] / 2) * 10;

		sum += (pattern[1][2] / 2) * 100;
		sum -= (pattern[0][2] / 2) * 100;
	}

	sum += (pattern[1][3] / 3) * 1000;
	sum -= (pattern[0][3] / 3) * 1000;

	sum += (pattern[1][4] / 4) * 10000;
	sum -= (pattern[0][4] / 4) * 10000;

	sum += (pattern[1][5] / 3) * 10050;
	sum -= (pattern[0][5] / 3) * 10050;

	sum += (pattern[1][6] / 4) * 100000;
	sum -= (pattern[0][6] / 4) * 100000;

	return sum;
}

bool Computer::PlayArea(GamePlay & gp, int x, int y)
{
	int cx[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
	int cy[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };

	for (int i = 0; i < 8; i++)
	{
		int u = x + cx[i];
		int v = y + cy[i];

		if (gp.inBoard(u, v))
			if (!gp.isEmpty(u, v)) return true;
	}

	return false;
}

