#include<iostream>
using namespace std;
void charusort1(int a[],int n,int m)
{
	int temp,i,j;
	
		for (j = n; j+1 < m; j++)
		{
			if (a[j + 1] < a[j])
			{
				int temp = a[j + 1];
				i = j;
				while (i >= n && a[i]>temp)
				{
					a[i + 1] = a[i];
					i--;
				}
				a[i + 1] = temp;
			}
		}
}
void charusort(int a[], int n,int b[],int c[])
{
	int temp, i, j, flag1 = 1, flag2 = 1;

	for (j = 0; j + 1 < n; j++)
	{
		if (a[j + 1] < a[j])
		{
			int temp = a[j + 1];
			i = j;
			while (i >= 0 && a[i]>temp)
			{
				a[i + 1] = a[i];
				i--;
			}
			a[i + 1] = temp;
		}
		for (int i = 0; i < n; i++)
		{
			if (flag2 == 0)
			{
				c[i] = a[i];
			}
			if (a[i] != b[i])
			{
				flag1 = 0;
			}
		}
		if (flag2 == 0)
		{
			cout << "Insertion Sort" << endl;
			for (int i = 0; i < n; i++)
			{
				cout << c[i];
				if (i != n - 1)
					cout << " ";
			}
			return;
		}
		if (flag1 == 0)
			flag1 = 1;
		else if (flag1 == 1)
		{
			flag2 = 0;
		}
	}
}
int findmaxmi(int n)
{
	int m=2,count=0;
	while (m < n)
	{
		m *= 2;
		count++;
	}
	return m;
}
void guibingsort(int a[],int n,int b[],int c[])
{
	int x = findmaxmi(n),i,flag1=1,flag2=1;
	for (i = 2; i <= x; i *= 2)
	{
			for (int k = 0; k < n; k+=i)
			{
				if (k + i < n)
				{
					charusort1(a, k, k + i);
				}
				else
				{
					charusort1(a, k, n);
				}
			}

			for (int l = 0; l < n; l++)
			{
				if (a[l] != b[l])
				{
					flag1 = 0;
				}
				if (flag2 == 0)
				{
					c[l] = a[l];
				}
			}
			if (flag2 == 0)
			{
				cout << "Merge Sort" << endl;
				for (int l = 0; l < n; l++)
				{
					cout << c[l] ;
					if (l != n - 1)
						cout << " ";
				}
				return;
			}
			if (flag1 == 1)
			{
				flag2 = 0;
			}
			else if (flag1 == 0)
				flag1 = 1;

	}
	
}

int main()
{
	int n;
	int a[100],b[100],c[100],d[100];
	int flag1, flag2;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
		d[i]=a[i];
	}
	for (int i = 0; i < n; i++)
	{
		cin >> b[i];
	}
	charusort(a, n, b, c);
	guibingsort(d, n, b, c);
	system("pause");
	return 0;
}