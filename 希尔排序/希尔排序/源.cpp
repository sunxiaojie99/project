#include<iostream>
using namespace std;
void hillsort(int a[],int n)
{
	int gap,i,j,temp;
	int count = 0;
	for (gap = n / 2; gap >= 1; gap /= 2)
	{
		for (i = 0; i < n; i++)//这一组gap元素的开始位置
		{
			for (j = i; j+gap < n; j += gap)//每隔gap的一组数的排序，插入排序，把一个数插入有序的数组中，移动，不交换！
			{
				if (a[j + gap] < a[j])//如果下一个元素小于上一个
				{
					temp = a[j + gap];//记录下这个元素
					while (j >= 0 && a[j] > temp)//将这个有序数组中所有比这个元素大的数都往后移动
					{
						a[j + gap] = a[j];
						j -= gap;
					}
					a[j + gap] = temp;//把这个数插入
				}
			}
		}
		count++;
		if (count != 1)
		{
			cout << endl;
		}
		for (int i = 0; i < n; i++)
		{
			cout << a[i];
			if (i != n - 1)
				cout << " ";
		}
	}
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
	hillsort(a, n);
	system("pause");
	return 0;
}