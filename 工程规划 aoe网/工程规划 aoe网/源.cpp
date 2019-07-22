/*工程可以分为N个阶段。每个阶段都可以并行，但是有依赖关系。试计算工程的最短消耗时间。
程序输入格式：输入第一个为整数N，代表阶段个数，随后输入N行，分表包含阶段编号、耗时，以及依赖关系，不同依赖使用";"分割。
程序输出格式：工程的最短消耗时间
输入样例：
4
1 3
2 4
3 5 1;2;
4 3 3;
输出样例：
12

输入：
4
1 3
2 4 3;
3 5 1;2;
4 3 3;
输出：
error
*/


#include<iostream>
#include<string>
#include<sstream>
#include<stack>
using namespace std;
//算法没有失败，则theorder是一个拓扑排序，如果算法失败，有向图没有拓扑排序，并且有向图含有回路
//用一维数组表示theorder；用一个栈来保存可加入到theorder的候选顶点；用一个一维数组indegree，其中indegree[j]
//表示不在theorder中但邻接至顶点j的顶点数目（不含进入theorder节点的入度）；当indegree[j]变为0时候，顶点j就成为一个候选顶点
//每次向theorder中加入一个顶点时，所有邻接于该顶点的顶点j，其indegree[j]-1
bool checkinout(int a[],int n,int t)
{
	for (int i = 0; i < n; i++)
	{
		if (a[i] == t)
			return true;
	}
	return false;
}
bool topologicalorder(int graph[100][100],int theorder[100],int n)//利用拓扑排序判断是否有环路
{
	int indegree[100] = {};
	int flag[100] = {};
	int t=0;
	stack<int> a;//候选点
	for (int j = 0; j < n + 2; j++)//计算入度
	{
		for (int i = 0; i < n + 2; i++)
		{
			if (graph[i][j] != 10000)
			{
				indegree[j]++;
			}
		}
	}
	for (int i = 0; i < n + 2; i++)
	{
		if (indegree[i] == 0)
		{
			a.push(i);//压入首批候选点
			flag[i] = 1;
		}
	}
	while (!a.empty())
	{
		int d;
		d = a.top();//删除第几个节点
		theorder[t++] = d;
		a.pop();
		for (int i = 0; i < n + 2; i++)
		{
			if (graph[d][i] != 10000)
			{
				indegree[i]--;
			}
			if (indegree[i] == 0&&flag[i]==0)
			{
				a.push(i);
				flag[i] = 1;
			}
		}
	}
	if (t == n + 2)
	{
		return true;
	}
	return false;
}
int mintime(int graph[100][100],int x,int n)//求顶点x的最小时间
{
	int max=-1;
	int i;
	if (x == 0)return 0;
	else
	{
		for (i = 0; i < n + 2; i++)
		{
			if (graph[i][x] != 10000)
			{
				if (graph[i][x] + mintime(graph, i, n) > max)
					max = graph[i][x] + mintime(graph, i, n);
			}
		}
	}
	return max;
}
int main()
{
	int graph[100][100];
	int theorder[100];
	int n;
	cin >> n;
	string s;
	getline(cin, s);//读取换行！！！
	//初始化矩阵
	int m = n + 2;
	for (int i = 0; i < n+2; i++)//加存一个入度为0的点 第0行 和一个出度为0的点 第n+1行
	{
		for (int j = 0; j < n + 2; j++)
		{
			graph[i][j] = 10000;
		}
	}
	for (int i = 0; i < n; i++)//读取数据
	{
		getline(cin, s);
		stringstream ss;
		ss << s;
		int end, value;
		ss >> end >> value;
		string a;//待处理
		ss >> a;
		if (a.length() != 0)
		{
			for (int i = 0; i < a.length(); i++)
			{
				if (a[i] == ';')
					a[i] = ' ';
			}
			ss.clear();//存待处理的字符串
			ss.str(a);
			int d;
			while (ss>>d)
			{
				graph[d][end] = value;
			}
		}
		else
		{
			graph[0][end] = value;
		}
	}
	int flag = 1;
	//对于没有出度的边，增加一个出度到新增0出度点
	for (int i = 0; i < n + 1; i++)//最后一行增加点不用查了 全为10000，到哪个点都没有边
	{
		for (int j = 0; j < n + 2; j++)
		{
			if (graph[i][j] != 10000)
			{
				flag = 0;
			}
		}
		if (flag == 1)
		{
			graph[i][n + 1] = 0;
		}
		flag = 1;
	}
	if (topologicalorder(graph, theorder, n) == false)
	{
		cout << "error";
	}
	else
	{
		cout << mintime(graph, n+1, n);
	}
	system("pause");
	return 0;
}