#include<iostream>
using namespace std;
const int inf = 1e9;
int min(int a,int b)
{
	if (a > b)
		return b;
	else return a;
}
int main()
{
	int n,s;
	cin >> n>>s;
	int time[6000];
	int cost[6000];
	int f[6000];
	for (int j = 0; j <= n; j++)//初始化f
	{
		f[j] = inf;
	}
	for (int i = 1; i <= n; i++)
	{
		cin >> time[i] >> cost[i];
	}
	for (int i = 2; i <= n; i++)//time[i]表示工作1到i的时间的累加(前缀和)； cost[i]表示工作1到i的费用系数的累加(前缀和)。
	{
		time[i] = time[i - 1] + time[i];
		cost[i] = cost[i - 1] + cost[i];
	}
	//f[i]表示(完成工作1到i的费用)+(因增加了S导致的后面的工作增加的费用)的总和的最小值
	f[0] = 0; cost[0] = 0;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			f[i] = min(f[i],f[j]+time[i]*(cost[i]-cost[j])+s*(cost[n]-cost[j]));
		}
	}
	/*
	j用来分组，表示把工作j+1到工作i分到同一组中。
	t[i]*(f[i]-f[j]) 表示完成j+1到i这一组工作的费用
	s*(f[n]-f[j])表示因为增加了一次开机，导致从工作j+1到工作n增加的费用。 
	*/
	cout << f[n];
	system("pause");
	return 0;
}