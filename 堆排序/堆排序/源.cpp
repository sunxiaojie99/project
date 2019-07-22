//① 初始化堆：将数列a[1...n]构造成最大堆。
//② 交换数据：将a[1]和a[n]交换，使a[n]是a[1...n]中的最大值；然后将a[1...n - 1]重新调整为最大堆。 接着，将a[1]和a[n - 1]交换，使a[n - 1]是a[1...n - 1]中的最大值；然后将a[1...n - 2]重新调整为最大值。 依次类推，直到整个数列都是有序的。
#include<iostream>
using namespace std;
void swap(int a[],int i,int j)
{
	int temp;
	temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}
void maxheap(int a[],int start,int end)//向下沉
{
	int cur = start;
	int l = 2 * cur + 1;
	for (; l <= end; cur=l,l = 2 * l + 1)
	{
		if (l < end&&a[l] < a[l + 1])
			l++;
		if (a[l] > a[cur])
			swap(a, l, cur);
	}
}
void heapsort(int a[],int n)
{
	int k = (n - 1) / 2;
	for (int i = k; i >= 0; i--)
	{
		maxheap(a, i, n - 1);
	}

	for (int j = n - 1; j >= 0; j--)
	{
		swap(a, 0, j);
		maxheap(a, 0, j - 1);
	}
}
int main()
{
	int n;
	int a[100];
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	heapsort(a, n);
	for (int i = 0; i < n; i++)
	{
		cout<< a[i]<<" ";
	}
	system("pause");
	return 0;
}