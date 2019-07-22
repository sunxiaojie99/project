#include<iostream>
using namespace std;
int cmul(int t)
{
	int sum = 1;
	while(t>1)
	{
		sum = sum*t;
		t--;
	}
	return sum;
}
int f(int fruit, int bag)
{
	if (fruit == 0)
		return 1;
	if (bag == 1)
		return 1;
	if (fruit < bag)
		return  (cmul(bag) / (cmul(fruit)*cmul(bag - fruit)))*f(fruit, fruit);
	else
	{
		return f(fruit - bag, bag) + bag*f(fruit, bag - 1);
	}
}
int main()
{
	int t;
	cin >> t;
	int a[1000][4];
	for (int i = 0; i < t; i++)
	{
		cin >> a[i][0] >> a[i][1];
	}
	for (int i = 0; i < t; i++)
	{
		if (i != 0)cout << endl;
		cout << f(a[i][0],a[i][1]);
	}
	system("pause");
	return 0;
}