//Kruskal算法
#include<iostream>
using namespace std;
class road
{
public:
	int start;
	int end;
	int weight;
};
void sort(road a[], int m)//先对所给的所有路径排序，从最小的依次检索
{
	for (int i = 0; i<m; i++)
	{
		for (int j = i+1; j<m; j++)
		{
			if (a[i].weight >a[j].weight)
			{
				road t = a[i];
				a[i] = a[j];
				a[j] = t;
			}
		}
	}
}
int findroot(int root[], int x)//找到某个位置的根节点 在root数组中的值等于其索引值
{
	if (root[x] == x)
	{
		return x;
	}
	else
	{
		x = root[x];
		findroot(root, x);
	}
}
void minroad(road a[], int n, int m, int root[])//求最小路径功能函数
{
	int i = 0;
	int sum = 0; 
	int count = 0;
	for (i = 0; i<m; i++)
	{
		int a1 = findroot(root, a[i].start);
		int a2 = findroot(root, a[i].end);
		if (a1 != a2)//如果两个结点相连，并且他们的根不一样（不同源）则把第一个结点的根的值赋值给第二个结点根的root值
		{
			root[a2] = a1;
			sum = sum + a[i].weight;//将该节点的长度纳到路径里来
			count++;
		}
	}
	if (count == n - 1)//如果有n-1个路径了，代表所有城市（n个）都检索过了
	{
		cout <<sum;
	}
	else
		cout << "Impossible";
}
int main()
{
	road a[100] = {};
	int root[100];//并查集
	int n, m;
	cin >> n >> m;
	for (int i = 0; i<m; i++)
	{
		cin >> a[i].start >> a[i].end >> a[i].weight;
	}
	for (int i = 1; i <= n; i++)
	{
		root[i] = i;
	}
	sort(a, m);
	minroad(a, n, m, root);
	system("pause");
	return 0;
}