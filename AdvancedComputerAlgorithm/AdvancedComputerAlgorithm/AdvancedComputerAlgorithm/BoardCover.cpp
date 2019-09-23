#include <iostream>
# include "advancedcomputeralgorithm.h"
using namespace std;

/**********��������********************
* ��һ��2^k * 2^k��������ɵ������У�ǡ��һ����������������ͬ���Ƹ÷���Ϊһ���ⷽ���ҳƸ�����Ϊһ�������̡����̸���������ָ��Ҫ��4�ֲ�ͬ��̬��L* �͹��Ƹ��Ǹ��������������ϳ����ⷽ����������з������κ�2��L�͹��Ʋ����ص����ǡ�
������ȷ Ҫʹ�÷��ε�˼�롣
* (1) �����̵ȷֳ��ĸ������ηֱ��ǣ����ϡ����¡����ϡ����� �ĸ������̡�
* (2) ����ÿһ�������̣������������ⷽ�񣬽����ٷֳ��ĸ������̣�����ʹ��ͬ���ķ������������̽��еݹ顣
* (3)���ڲ��������ⷽ��������̣��ٶ�������������������ӵ�Ϊ���ⷽ���������ⷽ��֮�󣬶���������̽��еݹ�
* (4)ֱ��������Ϊ1*1�������Ρ�

*/
static int tile = 1;  // �����������
static int board[BOARD_SZ][BOARD_SZ] = { 0 };  // ��������

/*************chess_board()����******************
* ��������chess_board()
* ����������int tr, int tc, int dr, int dc, int size���ֱ��ʾ���������Ͻ��������꣬������������꣬�����̳���
* ��������ֵ����

*/
void chess_board(int tr, int tc, int dr, int dc, int size)
{
	if (size == 1)
	{
		return;  // ������̱���Ϊһ��һ���Ĳ��֣�ֹͣ�ָ���ء�
	}

	int t = tile++;  // ��Ƭ����˼����ʾ���ǲ���
	int sz = size / 2;  // ÿ�ε������֣������̵ȷֳ��ĸ�С����

	// ͨ��<>=�ϸ�����ĸ����̵�����

	// �������Ͻǵ�����
	// ������ⷽ��������������У���ô��������̼��������ȷֳ��ĸ�С����
	if (dr < tr + sz && dc < tc + sz)
		chess_board(tr, tc, dr, dc, sz);
	// ������ⷽ��������������У��������������������������ӵ��Ǹ�����ת��Ϊ���ⷽ�񣬼�������
	else
	{
		board[tr + sz - 1][tc + sz - 1] = t;
		chess_board(tr, tc, tr + sz - 1, tc + sz - 1, sz);  // ע���ʱ���ⷽ���λ�þ�����һ��ת����λ��
	}

	// �������Ͻǵ�����
	if (dr < tr + sz && dc >= tc + sz)  // ע������ı߽�ֵ
		chess_board(tr, tc + sz, dr, dc, sz);
	else
	{
		board[tr + sz - 1][tc + sz] = t;   // ����ע���������ⷽ���λ��
		chess_board(tr, tc + sz, tr + sz - 1, tc + sz, sz);
	}

	// �������½ǵ�����
	if (dr >= tr + sz && dc < tc + sz)
		chess_board(tr + sz, tc, dr, dc, sz);  // ע������
	else
	{
		board[tr + sz][tc + sz - 1] = t;
		chess_board(tr + sz, tc, tr + sz, tc + sz - 1, sz);
	}

	// �������½ǵ�����
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
	cout.setf(ios::left);  // �����
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
