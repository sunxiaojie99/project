/*
输入：
2
qRj dIm
aTy oFu
4
qRj aTy
qRj oFu
oFu cLq
aTy qUr
0
输出：
No
Yes*/
#include<iostream>
#include<string>
using namespace std;
int checkwhois(string a[100][100],int count,string t)//检查选手t在数组中在第几行
{
	for (int i = 1; i <= count; i++)
	{
		if (a[i][1] == t)
			return i;
	}
}
int checkhowmany(string a[100][100], int count, string t)//是自己赢,不是间接赢的人数 count是选手数量
{
	int count1 = 0;
	for (int j = 2; j <= count; j++)
	{
		if (a[checkwhois(a, count, t)][j] != "no")
			count1++;
	}
	return count1;
}
int checkall(string a[100][100], int count, string t)//检查间接+直接赢的人数 count是选手数量
{
	int num=0;
	num = checkhowmany(a, count, t);
	for (int j = 2; j <= count; j++)
	{
		if (a[checkwhois(a, count, t)][j] != "no")
		{
			num = num + checkall(a, count, a[checkwhois(a, count, t)][j]);
		}
		else break;
	}
	return num;//如果有选手的num==count，并且不是所有的选手的num都等于count 则该选手获胜
}
int countplayer(string a[100][100],int n)//数一共多少玩家参加了比赛
{
	int count = 0;
	for (int i = 1; i <= 2 * n+2; i++)
	{
		if (a[i][1] != "no")
		{
			count++;
		}
	}//count一共多少个玩家
	return count;
}
string winplayernum(string a[100][100], int count)//count是参与的玩家
{
	int countwin = 0;//数获胜的玩家：checkall的num数为count
	string t;
	for (int i = 1; i <= count; i++)
	{
		if (checkall(a, count, a[i][1]) == count-1)//赢了除了自己以外的其他选手
		{
			countwin++;
			t = a[i][1];
		}
	}
	//cout << "countwin=" << countwin<<endl;
	if (countwin == 1)return t;
	else return "not have winner";
}
string r;
string checkifcircle(string a[100][100],int count,string t)//检查由已知的胜负表，t选手是否可以自己赢自己
{
	string m;
	for (int k = 2; k <= count; k++)//t直接赢的选手一条线一条线的倒,看看有没有可以倒到自己的
	{
		if (a[checkwhois(a, count, t)][k] != "no"&&a[checkwhois(a, count, t)][k]!=t)
		{
			if (a[checkwhois(a, count, t)][k] == r)
				return "circle";
			else
			{
				m = checkifcircle(a, count, a[checkwhois(a, count, t)][k]);
				if (m == "circle")
				{
					return "circle";
				}
			}
		}
	}
	return "notcircle";
}
int check(string a[100][100], int count)
{
	for (int h = 1; h <= count; h++)
	{
		r = a[h][1];
		if (checkifcircle(a, count, a[h][1]) == "circle")
			return 0;
	}
	return 1;
}
int main()
{
	string result[100];
	int countround = 0;
	while (1)
	{
		string a[100][100];
		int n;//n局比赛
		cin >> n;
		int flag = 0;
		if (n == 0)break;
		for (int k = 1; k <= 2 * n+2; k++)
		{
			for (int f = 1; f <= 2 * n+2; f++)
			{
				a[k][f] = "no";
			}
		}
		for (int i = 0; i < n; i++)
		{
			flag = 0;
			string b, c;
			cin >> b>> c;
			for (int j = 1; j <= 2 * n+2; j++)
			{
				if (a[j][1] ==b)
				{
					for (int h = 2; h <= 2 * n+2; h++)
					{
						if (a[j][h] == "no")
						{
							a[j][h] = c;
							flag = 1;
							break;
						}
					}
				}
				else if (a[j][1] == "no")
				{
					a[j][1] = b;
					a[j][2] = c;
					break;
				}
				if (flag == 1) {
					flag = 0; break;
				}
			}
			for (int j = 1; j <= 2 * n+2; j++)
			{
				if (a[j][1] == c)
				{
					break;
				}
				else if (a[j][1] == "no")
				{
					a[j][1] = c;
					break;
				}
			}
		}
		int count = countplayer(a, n);
		//cout << check(a, count) << endl;
		int flag0 = 0;
		if (check(a, count) == 0)
		{
			result[countround++] = "No";
			flag0 = 1;
		}
		//cout << count << endl;
		if (flag0 == 0)
		{
			if (winplayernum(a, count) == "not have winner")
			{
				result[countround++] = "No";
			}
			else {// cout << winplayernum(a, count) << endl;
				result[countround++] = "Yse";
			}
		}
	}
	for (int o = 0; o < countround; o++)
	{
		if (o != 0)cout << endl;
		cout << result[o];
	}
	system("pause");
	return 0;
}