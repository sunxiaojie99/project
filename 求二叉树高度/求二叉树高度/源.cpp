/*
描述:
给出一棵二叉树的先序遍历和中序遍历序列，计算该二叉树的高度。
其中，二叉树的先序和中序遍历序列为不包含重复英文字母（区别大小写）的字符串。

输入格式：
二叉树结点的总个数n<=50；然后输入先序和中序遍历序列，两个序列长度均为n。

输出格式：
二叉树高度（整数）
示例测试集:
- 第1组
输入：
9

ABDGHCEIF

GDHBAEICF
输出：
4
*/

#include<iostream>
using namespace std;
class node {
public:
	node *leftchild, *rightchild;
	char root;
};
int findlength(node *t)//求高度
{
	if (t==NULL) return 0;
	int hl = findlength(t->leftchild);
	int hr = findlength(t->rightchild);
	if (hl > hr)
		return ++hl;
	else
		return ++hr;
}
node* hy(char xx[], char zx[], int n)//求二叉树
{
	node *m=new node;
	int i = 0;
	if (n == 0) return NULL;
	else {
		m->root = xx[0];
		while (zx[i] != xx[0])
		{
			i++;
		}
		m->leftchild = hy(xx + 1, zx, i);
		m->rightchild = hy(xx + i + 1, zx + i+1, n - i-1);
	}
	return m;
}
int main()
{
	int n;
	cin >> n;
	char xx[100], zx[100];
	node *k;
	for (int i = 0; i < n; i++)
	{
		cin >> xx[i];
	}
	for (int j = 0; j < n; j++)
	{
		cin >> zx[j];
	}
	k=hy(xx, zx, n);
	cout << findlength(k);
	system("pause");
	return 0;
}
