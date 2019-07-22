/*
Input
The first line has two integers n, m, which means that the city has n intersections and m roads. 
The next m lines are descriptions of each road. Each line has three integers u, v, c 
which means that there is a direct road connection between the intersection u and v, 
and the score is c. (1 ≤ n ≤ 300, 1 ≤ c ≤ 10000).

Output
Output two integers 's' and 'max' separated by space. 's' means the total number of roads need to be upgraded.
'max' is the largest score of these roads.
*/
#include<iostream>
using namespace std;
class edge {
public:
	int start;
	int end;
	int value;
};
void sort(edge a[],int m)
{
	edge temp;
	int t;
	for (int i = 1; i <= m; i++)
	{
		if (a[i].value < a[i - 1].value)
		{
			t = i;//2
			temp = a[i];
			while (t>=1&&temp.value < a[t - 1].value)
			{
				a[t] = a[t - 1];
				t--;
			}
			a[t] = temp;
		}
	}
}
int findroot(int father[],int x)
{
	int t = x;
	if (father[t] == t)
		return t;
	else {
			t = father[t];
			findroot(father, t);
	}
}
int main()
{
	int n, m;
	cin >> n >> m;
	edge a[30000];
	int father[400];
	int check[30000] = {};
	for (int i = 1; i <= n; i++)
	{
		father[i] = i;
	}
	for (int i = 1; i <= m; i++)
	{
		int z, v, c;
		cin >> z >> v >> c;
		if (z < v)
		{
			a[i].start = z;
			a[i].end = v;
		}
		else
		{
			a[i].start = v;
			a[i].end = z;
		}
		a[i].value = c;
	}
	sort(a, m);
	int max=0;
	for (int i = 1; i <= m; i++)
	{
		if (check[i]==0&&findroot(father, a[i].start) != findroot(father, a[i].end))//把结束点的根节点认为是start节点
		{
			{
			int k = a[i].end;
			while (father[k]!=k)
			{
				int te = father[k];
				father[k] = findroot(father, a[i].start);
				k = te;
			}
			father[k] = findroot(father, a[i].start);
			}
			check[i] = 1;
			if (a[i].value > max)
				max = a[i].value;
		}
	}
	int count = 0;
	int sum=0;
	for (int i = 1; i <= m; i++)
	{
		if (check[i] == 1)
		{
			count++;
			sum += a[i].value;
		}
	}
	//cout << sum << endl;
	cout << count <<" "<< max;
	system("pause");
	return 0;
}
