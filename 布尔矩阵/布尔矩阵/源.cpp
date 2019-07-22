/*
布尔矩阵是指由0和1组成的矩阵，一个布尔矩阵有奇偶均势特性，当且仅当矩阵的每行、每列得总和为偶数，
即包含偶数个1，该矩阵就具有奇偶均势特性。如下面这个4*4的矩阵就具有奇偶均势特性：
1 0 1 0
0 0 0 0
1 1 1 1
0 1 0 1
每一行的和分别为2,0,4,2,每一列的和分别为2,2,2,2。
编写程序，读入一个n*n阶矩阵并检查它是否具有奇偶均势特性。如果没有，
你的程序应当再检查一下它是否可以通过修改一位（把0改为1，把1改为0）来使它具有奇偶均势特性。
如果不可能，这个矩阵就被认为是破坏了。
输入：
第一行是一个整数n ( 0< n < 100 )，代表该矩阵的大小。然后输入n 行，每行n个整数（0或1），由空格分隔。
输出：
如果矩阵具有奇偶均势特性，输出“OK”；如果能通过只修改该矩阵中的一位来使它具有奇偶均势特性，
则输出“Change bit (i,j)”，这里i和j是被修改的元素的行与列（行，列号从1开始）；否则，输出“Corrupt”
示例测试集:
- 第1组
输入：
4

1 0 1 0

0 0 0 0

1 1 1 1

0 1 0 1
输出：
OK
- 第2组
输入：
4

1 0 1 0

0 0 1 0

1 1 1 1

0 1 0 1
输出：
Change bit (2,3)
*/
#include<iostream>
using namespace std;
int main()
{
	int n;
	cin >> n;
	int a[100][100];
	int row[100] = {};
	int col[100] = {};
	for (int i = 0; i < n; i++)//输入矩阵
	{
		for (int j = 0; j < n; j++)
		{
			cin >> a[i][j];
		}
	}
	for (int k = 0; k < n; k++)//计算每行的1的和
	{
		for (int j = 0; j < n; j++)
		{
			if (a[k][j] == 1)
			{
				row[k]++;
			}
		}
	}
	for (int j = 0; j < n; j++)//计算每列1的和
	{
		for (int k=0; k < n; k++)
		{
			if (a[k][j] == 1)
			{
				col[j]++;
			}
		}
	}

	//输出每行和每列 1的数目
	/*for (int m = 0; m < n; m++) 
	{
		cout << row[m] << " ";
	}
	cout << endl;
	for (int m = 0; m < n; m++)
	{
		cout << col[m] << " ";
	}
	cout << endl;*/

	int flagr=1;
	int flagc = 1;
	int f,g;
	int resr, resc;
	int countr = 0, countc = 0;
	for (f = 0; f < n; f++)//检验每行和是否都为偶数
	{
		if(row[f]%2!=0)//不是偶数 记录有多少个不是 如果只有1次不是那么resr保存的就是这个不是偶数的位置
		{
			flagr = 0;
			resr = f;
			countr++;
		}
	}
	for (g = 0; g < n; g++)//检验每列和是否都为偶数
	{
		if (col[g] % 2 != 0)//不是偶数 记录有多少个不是 如果只有1次不是那么resc保存的就是这个不是偶数的位置
		{
			flagc = 0;
			resc = g;
			countc++;
		}
	}
	if (flagr == 1 && flagc == 1)//每行和 每列和都是偶数
	{
		cout << "OK";
	}
	else {
		if (countr == 1 && countc == 1)//只有一行和一列和不是偶数
		{
			cout << "Change bit " << "(" << resr+1 << "," << resc+1 << ")";
		}
		else//其余均不能改变
			cout << "Corrupt";
	}
	/*int count = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			
			if(i==n-1&&j==n-1)
			{
				cout << a[i][j];
			}
			else cout << a[i][j] << " ";
			count++;
			if (count == n)
			{
				cout << endl;
				count = 0;
			}
		}
	}*/
	system("pause");
	return 0;
}