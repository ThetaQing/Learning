#include <iostream>
# include "advancedcomputeralgorithm.h"
using namespace std;

/**********问题描述********************
* 在一个2^k * 2^k个方格组成的棋盘中，恰有一个方格与其他方格不同，称该方格为一特殊方格，且称该棋盘为一特殊棋盘。棋盘覆盖问题是指，要用4种不同形态的L* 型骨牌覆盖给定的特殊棋盘上除特殊方格以外的所有方格，且任何2个L型骨牌不得重叠覆盖。
首先明确 要使用分治的思想。
* (1) 把棋盘等分成四个正方形分别是：左上、左下、右上、右下 四个子棋盘。
* (2) 对于每一个子棋盘，如果其存在特殊方格，将它再分成四个子棋盘，并且使用同样的方法，对子棋盘进行递归。
* (3)对于不存在特殊方格的子棋盘，假定与另外三个子棋盘相接的为特殊方格，有了特殊方格之后，对这个子棋盘进行递归
* (4)直到子棋盘为1*1的正方形。

*/
static int tile = 1;  // 定义特殊骨牌
static int board[BOARD_SZ][BOARD_SZ] = { 0 };  // 定义棋盘

/*************chess_board()函数******************
* 函数名：chess_board()
* 函数参数：int tr, int tc, int dr, int dc, int size，分别表示子棋盘左上角行列坐标，特殊点行列坐标，和棋盘长度
* 函数返回值：无

*/
void chess_board(int tr, int tc, int dr, int dc, int size)
{
	if (size == 1)
	{
		return;  // 如果棋盘被分为一个一个的部分，停止分割，返回。
	}

	int t = tile++;  // 瓦片的意思，表示覆盖步骤
	int sz = size / 2;  // 每次迭代划分，将棋盘等分成四个小棋盘

	// 通过<>=严格控制四个棋盘的区域。

	// 覆盖左上角的棋盘
	// 如果特殊方格在这个子棋盘中，那么将这个棋盘继续迭代等分成四个小棋盘
	if (dr < tr + sz && dc < tc + sz)
		chess_board(tr, tc, dr, dc, sz);
	// 如果特殊方格不在这个子棋盘中，将这个棋盘与其他三个棋盘相接的那个方格转化为特殊方格，继续迭代
	else
	{
		board[tr + sz - 1][tc + sz - 1] = t;
		chess_board(tr, tc, tr + sz - 1, tc + sz - 1, sz);  // 注意此时特殊方格的位置就是上一步转化的位置
	}

	// 覆盖右上角的棋盘
	if (dr < tr + sz && dc >= tc + sz)  // 注意这里的边界值
		chess_board(tr, tc + sz, dr, dc, sz);
	else
	{
		board[tr + sz - 1][tc + sz] = t;   // 尤其注意这里特殊方格的位置
		chess_board(tr, tc + sz, tr + sz - 1, tc + sz, sz);
	}

	// 覆盖左下角的棋盘
	if (dr >= tr + sz && dc < tc + sz)
		chess_board(tr + sz, tc, dr, dc, sz);  // 注意坐标
	else
	{
		board[tr + sz][tc + sz - 1] = t;
		chess_board(tr + sz, tc, tr + sz, tc + sz - 1, sz);
	}

	// 覆盖右下角的棋盘
	if (dr >= tr + sz && dc >= tc + sz)
		chess_board(tr + sz, tc + sz, dr, dc, sz);
	else
	{
		board[tr + sz][tc + sz] = t;
		chess_board(tr + sz, tc + sz, tr + sz, tc + sz, sz);
	}
}

void print_chess_board()
{
	cout.setf(ios::left);  // 左对齐
	for (int i = 0; i < BOARD_SZ; ++i)
	{
		for (int j = 0; j < BOARD_SZ; ++j)
		{
			cout.width(3);
			cout << board[i][j];
		}
		cout << endl;
	}
}
