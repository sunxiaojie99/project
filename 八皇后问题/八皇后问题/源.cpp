#include<stdio.h>
#include<iostream>
#define  RANGE 8
#define  TRUE 1
#define  FALSE 0
void showEightQueens(int(*eq)[RANGE]);
int isPositionSafe(int(*eq)[RANGE], int row, int col);
void eightQueens(int(*eq)[RANGE], int i);
void eightQueens(int(*eq)[RANGE], int i)
{
	int j;
	if (i >= RANGE)//递归函数必须要有一个出口，不能无限递归
		showEightQueens(eq);
	else
	{
		for (j = 0; j < RANGE; j++)
		{
			if (isPositionSafe(eq, i, j))//判断此位置是否安全
			{
				eq[i][j] = 1;//若安全将此位置放皇后
				eightQueens(eq, i + 1);//处理下一行如果下一行所有位置都不安全，则返回调用递归的位置，继续进行下面的操作。
				eq[i][j] = 0;//完成此位置的操作后，将皇后去掉。因为要列出所有的可能结果，则应该每个位置都判断。
			}
		}
	}
}
int isPositionSafe(int(*eq)[RANGE], int row, int col)//判断位置是否安全
{
	int OK = TRUE;//这是一个技巧，我应该学会，相当于计算机用到很多的标志位
	int i;
	int j;
	for (i = row - 1, j = col - 1; OK && i >= 0 && j >= 0; i--, j--)//对角线
		if (eq[i][j] == 1)
			OK = FALSE;
	for (i = row - 1, j = col; OK && i >= 0; i--)//列
		if (eq[i][j] == 1)
			OK = FALSE;
	for (i = row - 1, j = col + 1; OK && i >= 0 && j < RANGE; i--, j++)//右斜对角线
		if (eq[i][j] == 1)
			OK = FALSE;
	return OK;
}
void showEightQueens(int(*eq)[RANGE])
{
	int i;
	int j;
	static int count = 0;//用到了静态变量
	printf("第%d种摆法\n", ++count);
	for (i = 0; i < RANGE; i++)
	{
		for (j = 0; j < RANGE; j++)
			printf("%3d", eq[i][j]);
		printf("\n");
	}
}
void main(void)
{
	int eightQueen[RANGE][RANGE] = { 0 };
	eightQueens(eightQueen, 0);
	system("pause");
}