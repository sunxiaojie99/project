/*
给定一个主串S和子串P，使用KMP算法查找子串P在主串S中存在的位置，若子串P在主串S中存在，
则输出与子串P中第一字符相等的字符在主串S中的序号；若不存在则输出“no”
程序输入格式：主串S 子串P；
程序输出格式：输出与子串P中第一字符相等的字符在主串S中的序号；
输入样例：ababcabcacbab abcac
输出样例：5
*/
#include<iostream>
#include<string>
using namespace std;
//void next(char T[], int Next[], int len) //经典算法
//{
//	int k = 0, j = 1; //k是前缀 j是后缀
//	Next[1] = 0;
//	while (j<len)
//	{
//		if (k == 0 || T[k] == T[j])//如果j是比的最后一个,那么应该是j后面的一个的next位置赋为k+1(k为重合度)
//		{
//			k++;
//			j++;
//			Next[j] = k;
//		}
//		else k = Next[k];
//	}
//}
void next(char T[],int Next[], int len)//此程序数组均从1 开始储存
{
	int i = 3,j,k;//i是next数组的位置 j是往i的前面找到的第一个与i-1相等的值的位置
	int yes=0;
	Next[1] = 0;
	Next[2] = 1;
	for (i = 3; i <=len ; i++)
	{
		k = i;//i能变，要充当next数组的指引，所以单独设一个变量k
		j = k - 2;//j是是往i的前面找到的第一个与i-1相等的值的位置，初始化从i-1前一个开始（即i-2）
		while(j>0)
		{
			if (T[k - 1] == T[j])//如果找到与i-1相等的第一个位置，再去将k-1与j均向前倒，看下一个是否相等，如果相等记录yes++
			{
				k--;
				j--;
				yes++;
			}
			else { j--;yes = 0; }//如果不相等，继续向前寻找下一个和i-1相等的位置，将该次检索中yes次数设置为0
		}
		if (yes == 0) Next[i] = 1;//如果yes为0，代表没有相等的前缀和后缀，next[i]=0+1
		if(yes!=0)//如果yes不等于0，代表有相等的前缀和后缀，next[i]=yes+1
		{ Next[i] = yes + 1;
		yes = 0;
		}
	}

}
int main()
{
	string T, S;
	cin >> S >> T;
	char ss[100], tt[100];
	int Next[100];
	int lens = S.length();
	int lent = T.length();
	for (int i = 1; i <= lens; i++)
	{
		ss[i] = S[i - 1];
	}
	for (int i = 1; i <= lent; i++)
	{
		tt[i] = T[i - 1];
	}
	next(tt, Next, lent);
	int p = 1;
	int j = 1;
	int flag = 1;
	while (p <= lens&&j <= lent)
	{
		if (ss[p] == tt[j])
		{
			p++;
			j++;
			flag = 1;
		}
		else
		{
			flag = 0;
			j = Next[j];
			if (p >= lens - lent + 1) { cout << "no"; break; }
		}

		if (j > lent&&flag == 1) { cout << p - lent-1 << endl; break; }
		if (j == 0) { j = 1; p++; };
	}
	system("pause");
	return 0;
}