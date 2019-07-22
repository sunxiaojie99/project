///*
//将一系列给定数字逐个插入一个初始为空的最大堆H[]。随后对任意给定的下标i，打印从H[i]到根结点的路径。
//输入格式:
//每组测试第1行包含2个正整数N和M(≤1000)，分别是插入元素的个数、以及需要打印的路径条数。下一行给出区间[-1000, 1000]内的N个要被插入一个初始为空的最大堆的整数。最后一行给出M个下标（根的下标为1）。
//输出格式:
//对输入中给出的每个下标i，在一行中输出从H[i]到根结点的路径上的所有节点。数字间以1个空格分隔。
//要求：
//每插入一个值，都要保证当前的H为最大堆。
//输入：
//5 4
//
//46 23 26 24 10
//
//5 4 3 1
//输出：
//10 24 46
//
//23 24 46
//
//26 46
//
//46
//*/
//
////先插入再整理成最大堆
////int checkmax(int a[],int x)//检查这个x位置左孩子和右孩子是否比它大
////{
////	int res1,res2,flag1=0,flag2=0;//1为左孩子，2为右孩子
////	if (a[2 * x])
////	{
////		if (a[2 * x] > a[x])
////		{
////			res1 = a[2 * x];
////			flag1 = 1;
////		}
////	}
////	if (a[2*x+1])
////	{
////		if (a[2 * x + 1] > a[x])
////		{
////			res2 = a[2 * x + 1];
////			flag2 = 1;
////		}
////	}
////	if (flag1 == 1 && flag2 == 1)
////	{
////		if (res1 > res2)
////			return 1;
////		else
////			return 2;
////	}
////	else if (flag1 == 1)
////	{
////		return 1;
////	}
////	else if(flag2==1)
////	{
////		return 2;
////	}
////	return 3;
////}
////#include<iostream>
////using namespace std;
////int main()
////{
////	int n, m,j,f,flag=0;
////	int a[1000] = {};//dui
////	int check[1000];
////	cin >> n >> m;
////	for (int i = 1; i <= n;)//输入插入的n个元素
////	{
////		flag = 0;
////		int d;
////		cin >> d;
////		for(int y = 1; y <= i; y++)
////		{
////			if (d == a[y])
////			{
////				flag = 1;
////				break;
////			}
////		}
////		if (flag == 0)
////		{
////			a[i] = d;
////			i++;
////		}
////		if (flag == 1)
////			n--;
////	}
////	/*int r = 1;
////	while (a[r])
////	{
////		cout << a[r] << " ";
////		r++;
////	}*/
////	for (int i = 1; i <= m; i++)//输入要检索到根路径的m条路径
////	{
////		cin >> check[i];
////	}
////	for (j = n / 2; j >= 1; j--)
////	{
////		f = 0;
////		f=checkmax(a, j);
////		if (f == 1)
////		{
////			int temp = a[j];
////			a[j] = a[2 * j];
////			a[2 * j] = temp;
////			j = n / 2;
////			j++;
////		}
////		else if (f == 2)
////		{
////			int temp = a[j];
////			a[j] = a[2 * j + 1];
////			a[2 * j + 1] = temp;
////			j = n / 2;
////			j++;
////		}
////	}
////	for (int h = 1; h <= m; h++)
////	{
////		for (int k = check[h]; k >= 1;)
////		{
////			cout << a[k];
////			if (k != 1)
////			{
////				cout << " ";
////			}
////			if (k % 2 == 0)
////			{
////				k = k / 2;
////			}
////			else
////				k = (k - 1) / 2;
////		}
////		if (h != m)
////		{
////			cout << endl;
////		}
////	}
////	system("pause");
////	return 0;
////}

//以下：每插入一个数 都使之成为最大堆，与先插入后整理结果不同
#include<iostream>
using namespace std;
void insert(int a[],int x)
{
	int max,p;
	p = x;
	for (int j = x / 2;j>=1;)
	{
		if (a[p] > a[j])
		{
			max = a[p];
			a[p] = a[j];
			a[j] = max;
			p = j;
		}
		j = j / 2;
	}
}
int main()
{
	int m, n, a[1000] = {}, check[1000];
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		insert(a, i);
	}
	for (int i = 1; i <= m; i++)
	{
		cin >> check[i];
	}
	
	for (int h = 1; h <= m; h++)
	{
		for (int k = check[h]; k >= 1;)
		{
			cout << a[k];
			if (k != 1)
			{
				cout << " ";
			}
			if (k % 2 == 0)
			{
				k = k / 2;
			}
			else
				k = (k - 1) / 2;
		}
		if (h != m)
		{
			cout << endl;
		}
	}
	system("pause");
	return 0;
}