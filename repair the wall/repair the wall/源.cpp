/*
The shape of the crack is a rectangle with the size of 1×L (inch). 
Fortunately, Kitty got N wood blocks and a saw from her neighbors.
the width of all the blocks was 1 inch. Kitty could cut down some of the blocks and put them in the crack. 
Now, Kitty had the size of each block and wanted to use as few blocks as possible. Could you help her?

Input
The input contains multiple test cases, please process to the end of file (EOF).
Each test case contains two lines.
In the first line, there are two integers L (0<L<1000000000) and N (0<=N<600) as mentioned above.
In the second line, there are N positive integers. The ith integer Ai (0<Ai<1000000000 ) means that the ith block has the size of 1×Ai (inch).

Output
For each test case, give an integer to represent the minimum number of blocks that are needed.
If Kitty could not repair the wall, just print "impossible".
输入
输入包含多个测试用例，请处理到文件末尾(EOF)。
每个测试用例包含两行。
在第一行中，有两个整数L (0<L<1000000000)和N (0<=N<600)。
在第二行，有N个正整数。第i个整数Ai (0<Ai<1000000000)表示第i个块大小为1×Ai(英寸)。
输出
对于每个测试用例，给出一个整数来表示需要的最小块数。
如果凯蒂不能修墙，就打印“不可能”。
23812 33
1920
931
1339
1398
2074
1178
2118
335
2679
1509
3260
88
436
3059
2190
3208
1394
779
2516
3036
2589
1843
289
704
2507
2409 2930 3047 1311 937 2823 196 1502
*/
#include<iostream>
using namespace std;
void sort(long long int a[],long long int n)//从大到小对砖的长度进行排序
{
	for (long long int i = 1; i < n; i++)
	{
		if (a[i] > a[i - 1])
		{
			long long int temp = a[i];
			long long int j = i;
			while (j >= 1&& temp > a[j - 1])
			{
				a[j] = a[j - 1];
				j--;
			}
			a[j] = temp;
		}
	}
}
int main()
{
	long long int len,n;
	long long int a[1000];
	while (cin >> len >> n)
	{
		long long int count = 0;
		for (long long int i = 0; i < n; i++)
		{
			cin >> a[i];
		}
		sort(a, n);
		for (long long int j = 0; j < n; j++)
		{
			if (len <= 0)
				break;
			if(len > 0)
			{
				len = len - a[j];
				count++;
			}
			
		}
		if(len<=0)
		{ 
			cout << count<<endl;
		}
		else
		{
			cout << "impossible"<<endl;
		}
	}
	return 0;
}