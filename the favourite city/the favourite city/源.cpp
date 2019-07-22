/*
Input：
The input contains multiple lines.
The first line: two positive integers n (n <= 10) and m (m <= n * (n-1) / 2), n represents the number of cities, and m represents the number of line segments.
Next m lines: each line contains three integers a, b and l, indicating that there is a line segment between city a and city b. The length of the line segment is l. (a is different from b)
The Last line: two integers x and y. Indicate the problem: what is the shortest distance between city x and city y. (x is different from y)
The city number is 1~n, l<=20.

Output：
The shortest distance between city x and city y.If city x and city y are not connected, output 0.

输入：
4 4
1 2 4
1 3 1
1 4 1
2 3 1
2 4
输出：
3
*/
#include<iostream>
using namespace std;
int ford(int map[100][100],int city)
{
	for (int i = 1; i <= city; i++)
	{
		for (int j = 1; j <= city; j++)
		{
			for (int k = 1; k <= city; k++)
			{
				if (map[k][j] != 0)
				{
					if (map[i][j] > map[k][j] + map[i][k])
					{
						map[i][j] = map[k][j] + map[i][k];
					}
				}
			}
		}
	}
	return 0;
}
int main()
{
	int map[100][100];
	int city, road;
	cin >> city >> road;
	for (int i = 1; i <= city; i++)
	{
		for (int j = 1; j <= city; j++)
		{
			map[i][j] = 100000;
		}
	}
	for (int i = 1; i <= road; i++)
	{
		int a;
		int b;
		int c;
		cin >> a >> b >> c;
		map[a][b] = c;
		map[b][a] = c;
	}
	for (int i = 1; i <= city; i++)
	{
		map[i][i] = 0;//初始化对角线元素
	}
	int x, y;
	cin >> x >> y;
	ford(map, city);
	if (map[x][y] != 100000)
	{
		cout << map[x][y];
	}
	else cout << "0";
	system("pause");
	return 0;
}
