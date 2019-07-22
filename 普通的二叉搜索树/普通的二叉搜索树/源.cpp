#include<iostream>
#include<Windows.h>
#include<queue>
#include<vector>
#include<functional>
#include <stdlib.h>
#include<time.h>
using namespace std;
class node {
public:
	node* leftchild=NULL;//左孩子 指针初始化为空
	node* rightchild=NULL;//右孩子
	int value;//节点数据
};
void make(node *&root,node *k)//插入节点
{
	if (root == NULL)//如果根节点为空，则直接插到根节点
	{
		root = k;
	}
	else//不为空 利用递归寻找合适的位置插入
	{
		if (k->value  < root->value)//如果插入的数据小于当前节点的数据，在左子树中插入该数据
		{
			make(root->leftchild, k);
		}
		else if (k->value  > root->value)//反之，向右子树插入
			make(root->rightchild, k);
	}
}
node *find(node *root,int k,node *&parent)//搜索节点 返回该节点和其父亲
{
	node*o;
	if (root == NULL)//如果根节点为空，则寻找到的节点为空，其父亲为为空
	{
		parent = NULL;
		return NULL;
	}
	else//从根开始搜索
	{
		if (k < root->value)//数据小于root的，将root赋给parent，在root的左子树里寻找该数据
		{
			parent = root;
			find(root->leftchild, k,parent);
		}
		else if (k > root->value)//数据大于root的，将root赋给parent，在root的右子树里寻找该数据
		{
			parent = root;
			find(root->rightchild, k,parent);
		}
		else if(k==root->value )//相等，返回该节点
			return root;
	}
}
node *findmax(node *root)//寻找此树最大节点
{
	if (root->rightchild == NULL)//如果该节点的右子树不存在，则该节点就是最大节点
		return root;
	else//否则一直寻找到该节点右子树的最右节点即为以root为根的树的最大节点
	{
		while (root)
		{
			root = root->rightchild;
		}
	}
	return root;
}
node *findmin(node*root,node *&parent)//寻找此树最小节点
{
	if (root->leftchild == NULL)//如果该节点的左子树不存在，则该节点就是最小节点
	{
		return root;
	}
	else//否则一直寻找到该节点左子树的最左节点即为以root为根的树的最小节点
	{
		while (root->leftchild)
		{
			parent = root;
			root = root->leftchild;
		}
	}
	return root;
}
node * deletenode(node *k)//删除节点
{
	if (k->rightchild!=NULL&&k->leftchild!=NULL)//k有2个孩子
	{
		node *p = NULL;
		int flag = 1;
		node *parent = k;
		p = findmin(k->rightchild,parent);//找到右子树的最左节点p
		if (parent->rightchild == p)
			flag = 1;//右孩子
		else
			flag = 0;
		k->value = p->value;//将p的值替换k的值
		p=deletenode(p); //转换为删除该替代节点p
		if (flag == 1)
		{
			parent->rightchild = p;
		}
		else if (flag == 0)
			parent->leftchild = p;
		return k;
	}
	else if (k->leftchild ||k->rightchild )//k有1个孩子
	{
		if (k->rightchild)//有右孩子 用右孩子替代该节点
			k = k->rightchild;
		else//有左孩子，用左孩子替代该节点
			k = k->leftchild;
		return k;//返回替代完成的节点
	}
	else
	{
		return NULL;//无孩子，用NULL替代该节点
	}
}
void print(node *root)//中序输出
//中序遍历是一种以上行顺序访问BST所有节点的遍历方式，也就是从小到达的顺序访问所有节点。
//中序遍历的一种应用就是对树进行排序操作。输出结果是从小到大的排列的数
{
	if (!root) {
		return;
	}
	else
	{
		print(root->leftchild);//先输出左孩子
		cout << root->value<<" ";//再输出根
		print(root->rightchild);//再输出右孩子
	}
}
void swap(int a[],int i,int j)
{
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}
int main()
{
	int size = 5000;//size范围1000~100000
	for (size = 1000; size <= 10000; size += 1000)
	{
		int *up = new int[size];//升序
		int *down = new int[size];//降序
		int *m = new int[size];//随机
		int *n = new int[size];//随机
		for (int i = 0; i < size; i++)
		{
			up[i] = i + 1;
			down[i] = size - i;
			m[i] = i + 1;  //依次将数组赋值为1~N 
			n[i] = i + 1;
		}
		for (int i = size - 1; i >= 1; --i) {
			swap(m,i, rand() % i);  //随机将两个数交换顺序 
			swap(n, i, rand() % i);
		}
		for (int i = size - 1; i >= 1; --i) {
		//随机将两个数交换顺序 
			swap(n, i, rand() % i);
		}

		node *root = NULL;
		//计时函数
		LARGE_INTEGER t1, t2, tc;
		QueryPerformanceFrequency(&tc);
		QueryPerformanceCounter(&t1);

		//BST-1 递增插入 相同顺序删除
		for (int i = 0; i < size; i++)
		{
			node*k = new node;
			k->value=up[i];
			make(root, k);
		}
		for (int j = 0; j < size; j++)
		{
			node *r = new node;
			r->value = up[j];
			node *parent = NULL;
			r = find(root, r->value,parent);
			if (r == NULL)
				cout << "erro";
			else
			{
				if (parent)
				{
					if (parent->leftchild == r)
					{
						parent->leftchild = deletenode(r);
					}
					else if (parent->rightchild == r)
					{
						parent->rightchild = deletenode(r);
					}
				}
				else
				{
					root= deletenode(r);
				}
			}
		}
		
		//BST-2 递增插入 相反顺序删除

		/*for (int i = 0; i < size; i++)
		{
			node*k = new node;
			k->value = up[i];
			make(root, k);
		}
		for (int j = 0; j < size; j++)
		{
			node *r = new node;
			r->value = down[j];
			node *parent = NULL;
			r = find(root, r->value, parent);
			if (r == NULL)
				cout << "erro";
			else
			{
				if (parent)
				{
					if (parent->leftchild == r)
					{
						parent->leftchild = deletenode(r);
					}
					else if (parent->rightchild == r)
					{
						parent->rightchild = deletenode(r);
					}
				}
				else
				{
					root = deletenode(r);
				}
			}
		}
		*/


		//BST-3 随机插入 随机顺序删除
		/*for (int i = 0; i < size; i++)
		{
			node*k = new node;
			k->value = m[i];
			make(root, k);
		}
		for (int j = 0; j < size; j++)
		{
			node *r = new node;
			r->value =n[j];
			node *parent = NULL;
			r = find(root, r->value, parent);
			if (r == NULL)
				cout << "erro";
			else
			{
				if (parent)
				{
					if (parent->leftchild == r)
					{
						parent->leftchild = deletenode(r);
					}
					else if (parent->rightchild == r)
					{
						parent->rightchild = deletenode(r);
					}
				}
				else
				{
					root = deletenode(r);
				}
			}
		}*/
		QueryPerformanceCounter(&t2);
		printf("%d,Use Time:%f\n", size,(t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart);
		cout << endl;
	}
	system("pause");
	return 0;
}
//bool* empty1=new bool[5*size+1];
//for (int i = 0; i < 5 * size; i++)
//{
//	empty1[i] = true;
//}
//bool *empty2=new bool[size+1];
//for (int i = 0; i < size; i++)
//{
//	empty2[i] = true;
//}
//priority_queue<int, vector<int>, greater<int>> pq1, pq11;//降序排列
//priority_queue<int> pq2, pq22;//升序排列 
//vector<int> v0, v1;//随机排列，v0存储随机数，v1存储随机产生的v0的下标 
////产生随机数
//srand((unsigned)time(NULL));
//for (int i = 0; i < size; i++)
//{
//	int t = rand() % (5 * size);
//	if (empty1[t]==true)
//	{
//		empty1[t] = false;
//		v0.push_back(t);
//		pq1.push(t);
//		pq2.push(t);
//	}
//	else
//		i--;
//}
//srand((unsigned)time(NULL));
//for (int i = 0; i < size; i++)
//{
//	int t = rand() % size;
//	if (empty2[t] == true)
//	{
//		empty2[t] = false;
//		v1.push_back(t);
//	}
//	else
//		i--;
//}
//pq11 = pq1;
//pq22 = pq2;