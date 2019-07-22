/*
有n个点和m个无向边。每条边的长度是d，花费是p，你有起点s和终点t，你能算出从s到t最短的距离吗?
您还需要计算它的成本。如果最短的距离有多个选择，你应该选择花费最少的路线。
input
There are multiple test cases. For each test case, the first line has two integers n and m, 
which are mentioned above, followed by m lines. For each line, there are four integers a, b, d and p, which means there is an edge between a and b. The length of the edge is d, and the cost is p. Then the last line has the two integers s and t as mentioned above. 
When n and m are 0, the input ends.
Output
Output the shortest distance and its cost in one line, separated by space.
输入：
3 2
1 2 5 6
2 3 4 5
1 3
0 0
输出：
9 11
*/
#include<iostream>
using namespace std;
void init(int a[100][100],int n)
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			a[i][j] = 1000000;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		a[i][i] = 0;
	}
}
int findmin(int dis[100],int s,int cost[100][100],int flag[100],int n)
{
	int min = 1000000;
	int index;
	int i;
	for (i = 1; i <= n; i++)
	{
		if (dis[i] < min&&flag[i]==0)
		{
			min = dis[i];
			index = i;
		}
		/*if (dis[i] == min&&flag[i] == 0)
		{
			if (cost[s][i] < cost[s][index])
			{
				index = i;
			}
		}*/
	}
	return index;
}
int ifempty(int flag[100],int n)
{
	for (int i = 1; i <= n; i++)
	{
		if (flag[i] != 1)
		{
			return 0;
		}
	}
	return 1;//全部都被选择过了
}
int dijkstra(int road[100][100],int cost[100][100],int dis[100],int s,int n,int m,int t)//以s为源点最小短路径，且最小耗费
{
	int money = 0;
	int pre[100] = {};
	int flag[100];
	for (int i = 1; i <= n; i++)//初始化flag
	{
		flag[i] = 0;
	}
	flag[s] = 1;
	for (int i = 1; i <= n; i++)//初始化dis数组
	{
		dis[i] = road[s][i];
	}
	for (int i = 1; i <= n; i++)//初始化pre数组 s的pre也是自己
	{
		if (dis[i] != 1000000)
		{
			pre[i] = s;
		}
	}
	while (!ifempty(flag, n))
	{
		int v = findmin(dis, s, cost, flag, n);
		flag[v] = 1;
		for (int i = 1; i <= n; i++)
		{
			if (road[v][i] != 0 && road[v][i] != 1000000)
			{
				if (dis[v] + road[v][i] < dis[i])
				{
					dis[i] = dis[v] + road[v][i];
					pre[i] = v;
				}
			}
		}
	}
	int p = t;
	while (pre[p] != p)
	{
		int u = pre[p];
		money += cost[u][p];
		p = u;
	}
	return money;
}
int main()
{
	int road[100][100];
	int dis[100];//每个点 距离源点的最小距离
	int cost[100][100];
	int s, t;//源点和初始点
	int m, n;//n个点，m条边
	int a, b, c, d;//a和b之间有一条边，这条边的长度是d，代价是p
	while (1)
	{
		cin >> n >> m;
		if (m == 0 && n == 0)
		{
			break;
		}
		init(road, n);
		init(cost, n);
		for (int i = 1; i <= m; i++)
		{
			cin >> a >> b >> c >> d;
			road[a][b] = c;
			road[b][a] = c;
			cost[a][b] = d;
			cost[b][a] = d;
		}
		cin >> s >> t;
		int money=dijkstra(road, cost, dis, s,n,m,t);
		cout << dis[t] << " " << money;
		cout << endl;
	}
	return 0;
}
//
//#include<iostream>
//using namespace std;
//void init(int a[100][100],int n)
//{
//	for (int i = 1; i <= n; i++)
//	{
//		for (int j = 1; j <= n; j++)
//		{
//			a[i][j] = 1000000;
//		}
//	}
//	for (int i = 1; i <= n; i++)
//	{
//		a[i][i] = 0;
//	}
//}
//int main(){
//		int road[100][100];
//		int dis[100];//每个点 距离源点的最小距离
//		int cost[100][100];
//		int s, t;//源点和初始点
//		int m, n;//n个点，m条边
//		int a, b, c, d;//a和b之间有一条边，这条边的长度是d，代价是p
//		while (1)
//		{
//			cin >> n >> m;
//			if (m == 0 && n == 0)
//			{
//				break;
//			}
//			init(road, n);
//			init(cost, n);
//			for (int i = 1; i <= m; i++)
//			{
//				cin >> a >> b >> c >> d;
//				road[a][b] = c;
//				road[b][a] = c;
//				cost[a][b] = d;
//				cost[b][a] = d;
//			}
//			cin >> s >> t;
//			for (int k = 1; k <= n; k++)
//			{
//				for (int i = 1; i <= n; i++)
//				{
//					for (int j = 1; j <= n; j++)
//					{
//						if (road[i][j] > road[i][k] + road[k][j])
//						{
//							road[i][j] = road[i][k] + road[k][j];
//							cost[i][j] = cost[i][k] + cost[k][j];
//						}
//						else if (road[i][j] == road[i][k] + road[k][j])
//						{
//							if (cost[i][j] > cost[i][k] + cost[k][j])
//							{
//								cost[i][j] = cost[i][k] + cost[k][j];
//							}
//						}
//					}
//				}
//			}
//			cout << road[s][t] << " " << cost[s][t]<<endl;
//		}
//		return 0;
//}