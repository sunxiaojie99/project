#include<iostream>
using namespace std;
void mulmatix(int a[5][5],int b[5][1],int c[5][1],int ar,int ac,int bc)
{
	int i, j, k;
	for (i = 0; i < ar; i++)
	{
		for (j = 0; j < bc; j++)
		{
			c[i][j] = 0;
			for (k = 0; k < ac; k++)
			{
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
}
void mulmatix1551(int a[1][5], int b[5][1], int c[1][1], int ar, int ac, int bc)
{
	int i, j, k;
	for (i = 0; i < ar; i++)
	{
		for (j = 0; j < bc; j++)
		{
			c[i][j] = 0;
			for (k = 0; k < ac; k++)
			{
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
}
void addmatix55(int a[5][5],int b[5][5],int c[5][5],int row,int col)
{
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < row; j++)
		{
			c[i][j] = a[i][j] + b[i][j];
		}
	}
}
void addmatix51(int a[5][1], int b[5][1], int c[5][1], int row, int col)
{
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			c[i][j] = a[i][j] + b[i][j];
		}
	}
}
void inti(int a[5][1])
{
	for (int p = 0; p < 5; p++)
	{
		a[p][0] = 0;
	}
}
void inti55(int a[5][5])
{
	for (int p = 0; p < 5; p++)
	{
		for (int r = 0; r < 5; r++)
		{
			a[p][r] = 0;
		}
	}
}
void inti15(int a[1][5])
{
	for (int p = 0; p < 1; p++)
	{
		for (int r = 0; r < 5; r++)
		{
			a[p][r] = 0;
		}
	}
}
int findmax(int a[5][1])
{
	int max=a[0][0];
	for (int i = 1; i < 5; i++)
	{
		if (a[i][0] > max)
		{
			max = a[i][0];
		}
	}
	return max;
}
int main()
{
	//abcde 分别为组件12345对应的横坐标为资源12345 纵坐标为生产线ABCDE 的5*5矩阵 （a 每列分别代表组件1在ABCDE上分别消耗12345资源各多少）
	int a[5][5] = { {2,0,1,0,0},{0,2,0,0,1},{2,1,0,0,0},{1,0,0,1,0},{0,0,0,2,2} };
	int b[5][5] = { {0,2,2,2,0},{1,0,2,3,0},{0,2,0,0,0},{2,0,0,0,4},{5,0,0,0,0} };
	int c[5][5] = { {1,1,0,1,0},{0,0,0,0,0},{2,0,2,2,0},{0,2,3,0,0},{0,5,0,0,3} };
	int d[5][5] = { {0,0,0,0,2},{0,1,0,2,0},{0,0,0,0,3},{3,0,1,3,1},{5,2,4,0,0} };
	int e[5][5] = { {0,0,1,0,1},{2,0,0,3,3},{0,0,0,0,0},{0,3,1,0,0},{2,0,3,6,0} };
	int t[5][5] = { {10,4,22,2,6},{8,10,13,16,8},{20,6,4,25,13},{4,12,10,8,11},{8,5,8,2,16} };
	int t1[1][5] = { 10,4,22,2,6 };//组件1在ABCDE上生产所花费的时间
	int t2[1][5] = { 8,10,13,16,8 };
	int t3[1][5] = { 20,6,4,25,13 };
	int t4[1][5] = { 4,12,10,8,11 };
	int t5[1][5] = { 8,5,8,2,16 };
	int source[5][1] = {3,4,3,4,6};//拥有的资源1 2 3 4 5 
	int y[5][5] = {};//y[][0]代表组件1在ABCDE上哪生产 一列只能有一个为1
	int y1[5][1] = {};
	int y2[5][1] = {};
	int y3[5][1] = {};
	int y4[5][1] = {};
	int y5[5][1] = {};
	int tempp[5][1] = {};
	int time[5][1] = {};//time[0][0]代表A生产线上的总时间消耗
	int sourcea[5][1] = {}, sourceb[5][1] = {}, sourcec[5][1] = {}, sourced[5][1] = {}, sourcee[5][1] = {};
	char min1, min2, min3, min4, min5;
	char i, j, k, l,m;
	int mintime=0;
	for (i = 'A'; i <='E'; i++)
	{
		for (j = 'A'; j <= 'E'; j++)
		{
			for (k = 'A'; k <= 'E'; k++)
			{
				for (l = 'A'; l <= 'E'; l++)
				{
					for (m = 'A'; m <= 'E'; m++)
					{
						y[i - 'A'][0] = 1;
						y1[i - 'A'][0] = 1;
						y[j - 'A'][1] = 1;
						y2[j - 'A'][0] = 1;
						y[k - 'A'][2] = 1;
						y3[k - 'A'][0] = 1;
						y[l - 'A'][3] = 1;
						y4[l - 'A'][0] = 1;
						y[m - 'A'][4] = 1;
						y5[m - 'A'][0] = 1;
						int temp1[5][1] = {};
						mulmatix(a, y1, temp1, 5, 5, 1);
						int temp2[5][1] = {};
						mulmatix(b, y2, temp2, 5, 5, 1);
						int temp3[5][1] = {};
						mulmatix(c, y3, temp3, 5, 5, 1);
						int temp4[5][1] = {};
						mulmatix(d, y4, temp4, 5, 5, 1);
						int temp5[5][1] = {};
						mulmatix(e, y5, temp5, 5, 5, 1);
						addmatix51(temp1, temp2, tempp, 5, 1);
						addmatix51(tempp, temp3, tempp, 5, 1);
						addmatix51(tempp, temp4, tempp, 5, 1);
						addmatix51(tempp, temp5, tempp, 5, 1);
						int flag = 0;
						for (int u = 0; u < 5; u++)
						{
							if (tempp[u][0] > source[u][0])
							{
								flag = 1;
								break;
							}
						}
						if (flag == 0)
						{
							//cout << i << j << k << l << m << endl; //满足拥有资源限制的情况
							int w[1][1] = {};//↓计算time矩阵  举例：time[0][0]代表A生产线上的总时间消耗
							mulmatix1551(t1, y1, w, 1, 5, 1);
							time[i-'A'][0] = time[i-'A'][0] + w[0][0];
							mulmatix1551(t2, y2, w, 1, 5, 1);
							time[j - 'A'][0] = time[j - 'A'][0] + w[0][0];
							mulmatix1551(t3, y3, w, 1, 5, 1);
							time[k - 'A'][0] = time[k - 'A'][0] + w[0][0];
							mulmatix1551(t4, y4, w, 1, 5, 1);
							time[l - 'A'][0] = time[l - 'A'][0] + w[0][0];
							mulmatix1551(t5, y5, w, 1, 5, 1);
							time[m - 'A'][0] = time[m - 'A'][0] + w[0][0];
							if (mintime == 0)
							{
								mintime = findmax(time);//求time矩阵中的最大元素即为此次的时间消耗
								min1 = i; min2 = j; min3 = k; min4 = l; min5 = m;
							}
							if (mintime > findmax(time))
							{
								mintime = findmax(time);
								min1 = i; min2 = j; min3 = k; min4 = l; min5 = m;
							}
						}
						flag = 0;
						inti(y1);
						inti(y2); inti(y3); inti(y4); inti(y5);
						inti(sourcea); inti(sourceb); inti(sourcec); inti(sourced); inti(sourcee); inti(time);
						inti55(y);
					}
				}
			}
		}
	}
	cout << mintime << endl;
	cout << min1 << min2 << min3 << min4 << min5;
	system("pause");
	return 0;
}