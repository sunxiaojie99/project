/*
约瑟夫环问题
一个刚出锅的山芋，在围成一圈的n（以编号1，2，3...n分别表示 ）个孩子间传递。大家一起数数，从编号为1的孩子开始报数，每数一次，
当前拿着山芋的孩子就把山芋交给紧邻其右的孩子。 一旦数到事先约定的某个数k ， 那个人就出列，他的下一个人又从1开始报数，
数到数k的那个人就出列。如此反复，最后剩下的那个孩子就是幸运者。
试实现算法josephus（int n, int k），输出孩子们出列的次序
程序输入：n k
程序输出：孩子们出列的次序
例子：
输入8 3
输出：
3->6->1->5->2->8->4->7
输入：
18 7
输出：
7->14->3->11->1->10->2->13->6->18->16->15->17->5->12->4->8->9
*/
//用第几个，对于3取模，如果是0，则输出，一个个往数组后面存前面不为0的  unsucessful
//#include<iostream>
//#include<stack>
//using namespace std;
//int main()
//{
//	int n, k, flag = 0,add=0,flag1=0;
//	cin >> n >> k;
//	int a[100],b[100],c[100],num=0;
//	for (int i = 0; i < 100; i++)
//	{
//		a[i] = i + 1;
//		b[i] = 1;
//	}
//	//stack<int> lucky;
//		for (int j = 0;j<100; j++)
//		{
//			flag = 0;
//				if (((j + 1) % (k)) != 0)
//				{
//					a[n + j] = a[j];
//				}
//				else if ((j + 1) % (k+add) == 0)
//				{
//					b[j] = 0;
//					//lucky.push(a[j]);
//					c[num] = a[j];
//					num++;
//					flag1 = 0;
//				}
//				if (num >= 3&&flag1==0) { add++; flag1 = 1; }
//				if (j == 10)
//				{
//					for (int i = 0; i < 20; i++)
//						cout << a[i]<<" ";
//				}
//				for (int x = 0; x < 100; x++)
//				{
//					if (b[x] == 0)
//					{
//						flag++;
//					}
//					if (flag == n) { break; break; break; }
//				}
//		}
//		/*while (!lucky.empty())
//		{
//			cout<<lucky.top()<<" ";
//			lucky.pop();
//		}*/
//		cout << endl;
//		for (int i = 0; i < n; i++)
//		{
//			cout << c[i] << " ";
//		}
//		system("pause");
//		return 0;
//}

////两个队列，当从一个中front后push到另一个队列，然后pop原来的，用count计数
//#include<iostream>
//#include<Queue>
//using namespace std;
//int main()
//{
//	queue<int>q1;
//	int n, k, e, count = 0, flag = 1;
//	cin >> n >> k;
//	for (int i = 0; i < n; i++)
//	{
//		q1.push(i+1);
//	}
//	queue<int>q2;//中转
//	for (;;)
//	{
//		if (flag == 1)
//		{
//			e = q1.front();
//			count++;
//			q1.pop();
//			q2.push(e);
//		}
//		else if (flag == 2)
//		{
//			e = q2.front();
//			count++;
//			q2.pop();
//			q1.push(e);
//		}
//		if (q1.empty())flag = 2;
//		else if (q2.empty())flag = 1;
//		if (count == k-1)
//		{
//			if (flag == 1)
//			{
//				cout << q1.front() << " ";
//				q1.pop();
//				count = 0;
//			}
//			else if (flag == 2)
//			{
//				cout << q2.front() << " ";
//				q2.pop();
//				count = 0;
//			}			
//		}
//		if (q1.empty())flag = 2;
//		else if (q2.empty())flag = 1;
//
//		if (q1.empty() && q2.empty())
//			break;
//	}
//	system("pause");
//	return 0;
//}

//将前面不是报3的数字front push到队尾，然后再pop 用count计数，记到2就把这个该报3的数front 存到数组
//#include<iostream>
//# include<queue>
//using namespace std;
//int main()
//{
//	queue<int>q1;
//	int n, k, e, count = 0,a[100],m=0;
//	cin >> n >> k;
//	for (int i = 0; i < n; i++)
//	{
//		q1.push(i+1);
//	}
//	for (;;)
//	{
//		if (count != (k - 1))//k=3 k-1=2  
//		{
//			e = q1.front();//1 2
//			count++;//1 2
//			q1.push(e);
//			q1.pop();
//		}
//		if (count ==( k-1))//2
//		{
//			count = 0;
//			a[m]=q1.front();//3
//			m++;//1
//			q1.pop();
//		}
//		if (m ==n)
//			break;
//	}
//	for (int j = 0; j < n ; j++)
//	{
//		if(j!=n-1)
//		cout << a[j] << "->";
//		if (j == n - 1)
//			cout << a[j];
//	}
//	system("pause");
//	return 0;
//}

