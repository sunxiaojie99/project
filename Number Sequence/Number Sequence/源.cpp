//(1) = 1, f(2) = 1, f(n) = (A * f(n - 1) + B * f(n - 2)) mod 7.
/*
1 1 3

1 2 10

0 0 0
Êä³ö£º
2

5
*/

#include<iostream>
using namespace std;
int f(int a, int b, long long int n)
{
	long long int x1=1,x2=1;
	long long int i = n - 2;
	if (n == 1 || n == 2)return 0;
	while (i--)
	{
		int t;
		t = x2;
		x2 = (a*x2 + b*x1) % 7;
		x1 = t;
	}
	return x2;
}
int main()
{
	long long int a, b;
	long long int n;
	long long int i = 0;
	while (cin >> a >> b >> n && !(a == 0 && b == 0 && n == 0))
	{
		cout << f(a, b, n) << endl;
		i++;
	}
	system("pause");
	return 0;
}