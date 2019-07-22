//https://www.cnblogs.com/skywang12345/p/3577360.html#a1
//在AVL树中，任何节点的两个子树的高度最多相差1；如果它们高度相差不止1，则需要重新平衡以恢复这种属性。
//现在给定一个插入序列， 一个一个地将键值插入初始为空的AVL树中，输出得到的AVL树的层次顺序遍历序列，
//并判断它是否是一个完全二叉树。
//输入格式：
//第一行包含一个正整数N(<= 20)。然后在下一行给出N个不同的整数键。所有数字都用空格隔开。
//
//输出格式：
//第一行打印得到的AVL树的层次顺序遍历序列。所有数字都必须用空格隔开，并且行尾必须没有多余的空格。
//然后在下一行中，如果树为完全二叉树，则打印“Yes”;如果不是，则打印“No”。
//示例测试集:
//- 第1组
//输入：
//5
//
//88 70 61 63 65
//输出：
//70 63 88 61 65
//
//Yes
//- 第2组
//输入：
//10
//
//62 88 58 47 35 73 51 99 37 93
//输出：
//62 47 88 35 58 73 99 37 51 93
//
//No
//
#include<iostream>
#include<Queue>
#include<vector>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<functional>
#include<Windows.h>

using namespace std;
class node
{
public:
	int value;//数据
	node *leftnode;//左孩子
	node *rightnode;//右孩子
};
int findheight(node *t)//求当前节点的高度
{
	if (!t)return 0;//若为空指针，则其高度为0
	else//不为空，求左子树右子树高度的最大值+1
	{
		int hl = findheight(t->leftnode);
		int hr = findheight(t->rightnode);
		if (hl>hr)
			return ++hl;
		else
			return ++hr;
	}
}
node * LL(node *T)//插入元素位于左树的左儿子，为L型不平衡，应右旋
{
	node *temp;
	temp = T->leftnode;
	T->leftnode = temp->rightnode;
	temp->rightnode = T;

	return temp;
}
node *RR(node *T)//插入元素位于右树的右儿子，则为R型不平衡，应左旋 
{
	node *temp;
	temp = T->rightnode;
	T->rightnode = temp->leftnode;
	temp->leftnode = T;
	return temp;
}
node *LR(node *T)//插入元素位于左树的右儿子，LR型不平衡，先左旋后右旋 
{
	node *temp1,*temp2;
	temp1=RR(T->leftnode);
	T->leftnode = temp1;
	temp2=LL(T);
	return temp2;
}
node *RL(node *T)//插入元素位于右树的左儿子，RL型不平衡，先右旋再左旋
{
	node *temp1, *temp2;
	temp1 = LL(T->rightnode);
	T->rightnode = temp1;
	temp2 = RR(T);
	return temp2;
}
node *insert_in_AVL(int num, node *T)//递归插入新节点
{
	if (T==NULL)//如果原来根为空，就直接插在根节点
	{
		T = new node;
		T->value = num;
		T->leftnode = NULL;
		T->rightnode = NULL;
	}
	else
	{
		if (num<T->value)//若插入值小于当前根节点t
		{
			T->leftnode =insert_in_AVL(num, T->leftnode);//递归，插入在t的左子树里
			if (findheight(T->leftnode) - findheight(T->rightnode) == 2) //若其平衡因子为2 
			{
				if (num<T->leftnode->value)//若插入在左子树的左节点
				{
					T=LL(T);
				}
				else if (num > T->leftnode->value)//若插入在左子树的右节点
				{
					T = LR(T);
				}
			}
		}
		else if (num > T->value)//若插入值大于当前根节点t
		{
			T->rightnode =insert_in_AVL(num, T->rightnode);//递归，插入在t的右子树里
			if (findheight(T->leftnode) - findheight(T->rightnode) == -2) //若其平衡因子为2 
			{
				if (num > T->rightnode->value)//若插在右子树的右节点
				{
					T = RR(T);
				}
				else if (num < T->rightnode->value)//若插在右子树的左节点
				{
					T = RL(T);
				}
			}
		}
	}
	return T;
}
void printtree(node *t)//使用队列按层打印，每弹出一个结点，就将其左右子树节点压入栈
{
	queue<node *>a;
	a.push(t); 
	while (!a.empty())
	{
		cout << a.front()->value;
		node *f; 
		f = a.front();
		a.pop();
		if (f->leftnode != NULL)
		{
			a.push(f->leftnode);
		}
		if (f->rightnode != NULL)
		{
			a.push(f->rightnode);
		}
		if (!a.empty())
			cout << " ";
	}
}
bool check(node *t)//判断是否为完全二叉树
{
	queue <node *>a;
	a.push(t);
	while (!a.empty())
	{
		node *f = a.front();
		a.pop();
		if (f->leftnode == NULL&&f->rightnode !=NULL)
		{
			return false;
		}
		else if (f->leftnode == NULL||f->rightnode == NULL)
		{
			while (!a.empty())
			{
				node *j = a.front();
				a.pop();
				if (j->leftnode != NULL || j->rightnode != NULL)
					return false;
			}
			return true;
		}
		else
		{
			a.push(f->leftnode);
			a.push(f->rightnode);
		}
	}
}
node *findmax(node *root)//寻找以当前节点为根的树中最大节点
{
	if (root == NULL)//若根为空 返回空
		return NULL;
	else
	{
		while (root->rightnode)
		{
			root = root->rightnode;
		}
	}
	return root;
}
node *findmin(node *root)//寻找以当前节点为根的树的最小节点
{
	if (root == NULL)
		return NULL;
	else
	{
		while (root->leftnode)
		{
			root = root->leftnode;
		}
	}
	return root;
}
node *search(node *root,int k)//在根为root的树中寻找值为k的节点
{
	if (root == NULL)//如果根为空，返回空
		return NULL;
	if (root->value == k)
		return root;
	else if (k > root->value)//如果数字大于当前节点，在其右子树中搜索
	{
		return search(root->rightnode, k);
	}
	else if (k < root->value)//如果数字小于当前节点，在其左子树中搜索
	{
		return search(root->leftnode, k);
	}
}
node * delete_avl(node *root,node *z)//删除节点
{
	if (root == NULL || z == NULL)//如果根是空或者删除的节点是空 返回空
	{
		return NULL;
	}
	else
	{
		if (z->value < root->value)//如果该节点比根节点小，递归，在root的左子树中删除
		{
			root->leftnode = delete_avl(root->leftnode, z);
			if (findheight(root->rightnode) - findheight(root->leftnode) == 2)//如果删除完，“根”的平衡因子等于2
			{
				node *r = root->rightnode;
				if (findheight(r->rightnode )>findheight(r->leftnode ))//如果呈现RR型不平衡
				{
					root=RR(root);
				}
				else//呈现RL型不平衡
				{
					root = RL(root);
				}
			}
		}
		else if (z->value > root->value)//如果该节点大于“根”节点，递归，在root的右子树中删除
		{
			root->rightnode = delete_avl(root->rightnode, z);
			if (findheight(root->leftnode) - findheight(root->rightnode) == 2)//删除完“根”的平衡因子变成2
			{
				node *l = root->leftnode;
				if (findheight(l->leftnode) > findheight(l->rightnode))//如果是LL型不平衡
				{
					root = LL(root);
				}
				else//如果是LR型不平衡
					root = LR(root);
			}
		}
		else if (z->value == root->value)//如果该节点等于当前“根”节点值
		{
			if (root->leftnode &&root->rightnode)//若当前“根”节点的左右子树都存在
			{
				if (findheight(root->leftnode) > findheight(root->rightnode))//若左子树比较高，则选用左子树最大（右）节点“替代”要删除的节点  
				{
					node *replace = findmax(root->leftnode);
					root->value = replace->value;//将替代节点的值赋给删除节点
					root->leftnode  = delete_avl(root->leftnode , replace);//在左子树中删除替代节点
				}
				else//若右子树比较高，选择右子树的最小（左）节点替代当前删除节点
				{
					node *replace = findmin(root->rightnode);
					root->value = replace->value;//将替代节点的值赋给删除节点
					root->rightnode  = delete_avl(root->rightnode , replace);//在右子树中删除替代节点
				}
			}
			else//当前节点有1个或者没有孩子 令孩子节点替代删除节点即可
			{
				node *tmp=root;
				root = (root->leftnode != NULL) ? root->leftnode : root->rightnode;
				delete tmp;
			}
		}
	}
	return root;
}
void swap(int a[],int i,int j)
{
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}
int main()
{
	int size = 1000;//size范围1000~100000
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
			swap(m, i, rand() % i);  //随机将两个数交换顺序 
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
		node *T;
		T = NULL;
		//AVL1 递增插入 相同顺序删除
		/*
		for (int j = 0; j < size; j++)
		{
			T = insert_in_AVL(up[j], T);
		}
		for (int i = 0; i < size; i++)
		{
			node *e = new node;
			e = search(T, up[i]);
			T = delete_avl(T, e);
		}
		*/

		//AVL2 递增插入，相反顺序删除
		
		for (int j = 0; j < size; j++)
		{
			T = insert_in_AVL(up[j], T);
		}
		for (int i = 0; i < size; i++)
		{
			node *e = new node;
			e = search(T, down[i]);
			T = delete_avl(T, e);
		}
		
		

		//AVL3 随机插入随机删除
		/*
		for (int j = 0; j < size; j++)
		{
			T = insert_in_AVL(m[j], T);
		}
		for (int i = 0; i < size; i++)
		{
			node *e = new node;
			e = search(T,n[i]);
			T = delete_avl(T, e);
		}*/
		
		QueryPerformanceCounter(&t2);
		printf("%f", (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart);
		cout << endl;
	}
	system("pause");
	return 0;
}


