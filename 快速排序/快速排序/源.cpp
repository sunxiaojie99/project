#include<iostream>
using namespace std;
void swap(int a[],int i,int j)
{
	int temp;
	temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}
int cut(int a[],int left,int right)//找基准 划分
{
	int i = left+1;
	int j = right;
	int temp = a[left];
	while (i <= j)
	{
		while (a[i] < temp)
		{
			i++;
		}
		while (a[j] > temp)
		{
			j--;
		}
		if (i < j)
		{
			swap(a, i, j);
			i++;
			j++;
		}
		else
			i++;
	}
	swap(a, left, j);
	return j;
}
void quicksort(int a[],int left,int right)
{
	if (left > right)
		return;
	int j = cut(a, left, right);
	quicksort(a, left, j-1);
	quicksort(a, j + 1, right);
}
int main()
{
	int a[100];
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	quicksort(a, 0, n - 1);
	for (int i = 0; i < n; i++)
	{
		cout << a[i]<<" ";
	}
	system("pause");
	return 0;
}