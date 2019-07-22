//#include<stdio.h>
//#include<iostream>
//using namespace std;
//int main()
//{
//	int a[100], b[100], d, i, j, k, n,count=0;
//	int sort(int a[100], int n);
//	scanf("%d", &n);
//	for (i = 0; i<n; i++)
//		scanf("%d", &a[i]);
//
//	for (d = n / 2; d >= 1; d = d / 2)
//	{
//		for (k = 0; k<n - d ; k++)
//		{
//			for (i = k, j = 0; i < n; i = i + d, j++)
//			{
//				b[j] = a[i];
//				count++;
//			}
//			sort(b, count);
//			for (i = k, j = 0; j<count; i = i + d, j++)
//			{
//				a[i] = b[j];
//				cout << b[j]<<" ";
//			}
//			count = 0;
//			cout << endl;
//		}
//		cout << "#";
//		for (i = 0; i<n; i++)
//			printf("%d ", a[i]);
//		printf("\n");
//
//	}
//	system("pause");
//	return 0;
//}
//int sort(int a[100], int n)
//{
//	int i, j, temp;
//	for (i = 1; i<n; i++)
//	{
//		if (a[i - 1]>a[i])
//		{
//			temp = a[i];
//			for (j = i - 1; j >= 0 && a[j]>temp; j--)
//			{
//				a[j + 1] = a[j];
//			}
//			a[j + 1] = temp;
//		}
//	}
//	return a[100];
//
//
//}

#include<iostream>
#include<string>
using namespace std;
int main()
{
	char a[1000];
	char b[1000];
	int c = strlen(a),flag=0;
	cout << c << endl;
	cin.getline(a, 1000);
	b[0] = a[c - 1];
	for (int i = 1; i < c; i++)
	{
		for (int x = 0; x < strlen(b); x++)
		{
			if (a[c - i] == b[x])
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			b[i] = a[c - i - 1];
		}
		else
			flag = 0;
	}
	if (c > 50)
		cout << "out" << endl;
	else
	{
		if (!strcmp(a, "END"))
			return 0;
		else
			cout << b << endl;
	}
	system("pause");
	return 0;
	
}