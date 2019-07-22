#include<iostream>
#include<Queue>
#include<vector>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<functional>
#include<Windows.h>
using namespace std;
enum nodecolor {red,black};
class node {
public:
	node *leftchild=NULL;//左孩子
	node *rightchild=NULL;//右孩子
	node *parent=NULL;//父节点
	nodecolor color;//颜色
	int key;//关键字
};
/*
* 对红黑树的节点(x)进行左旋转
*
* 左旋示意图(对节点x进行左旋)：
*      px                              px
*     /                               /
*    x                               y
*   /  \      --(左旋)-->           / \                #
*  lx   y                          x  ry
*     /   \                       /  \
*    ly   ry                     lx  ly
*
*
*/

void leftroate (node *&root,node *x)//左旋
{
	node *y = x->rightchild;//将x的右孩子设为y
	if (x->parent == NULL)//如果x为root，则令y等于root
	{
		root = y;
	}
	else
	{
		if (x->parent->leftchild == x)//如果x等于x父节点的左孩子
		{
			x->parent->leftchild = y;//令x父亲的左孩子为y
			y->parent = x->parent;//x的父亲为y的父亲
		}
		else//如果x等于x父亲的右孩子
		{
			x->parent->rightchild = y;//令x父亲的右孩子指向y
			y->parent = x->parent;//令y的父亲指向x的父亲
		}
	}
	x->rightchild = y->leftchild;//y的左孩子设为x的右孩子
	if (y->leftchild != NULL)//如果y的左孩子非空
	{
		y->leftchild->parent = x;//y左孩子的父亲设为x
	}
	y->leftchild = x;//y的左孩子设为x
	x->parent = y;//x的父亲设为y
}
/*
* 对红黑树的节点(y)进行右旋转
*
* 右旋示意图(对节点y进行左旋)：
*            py                               py
*           /                                /
*          y                                x
*         /  \      --(右旋)-->            /  \                     #
*        x   ry                           lx   y
*       / \                                   / \                   #
*      lx  rx                                rx  ry
*
*/
void rightroate(node *&root,node *y)//与avl区别 多了parent结点，要双向赋值 右旋
{
	node *x = y->leftchild;//设置x为当前节点y的左孩子
	if (y->parent == NULL)//如果y是根节点
	{
		root = x;//把根设为x
	}
	else
	{
		if (y->parent->leftchild == y)//如果y是其父亲节点的左孩子
		{
			y->parent->leftchild = x;//将y父亲的左孩子设为x
			x->parent = y->parent;//y的父亲设为x的父亲
		}
		else//如果y是其父亲的右孩子
		{
			y->parent->rightchild = x;//将其父亲的右孩子设置为x
			x->parent = y->parent;//x的父亲设置为y的父亲
		}
	}
	y->leftchild = x->rightchild;//x的右孩子设为y的左孩子
	if (x->rightchild != NULL)//如果x的右孩子非空
	{
		x->rightchild->parent = y;//x右孩子的父亲为y
	}
	x->rightchild = y;//x的右孩子设置为y
	y->parent = x;//y的父亲设置为x
}
void printtree(node *root)//使用队列按层打印，每弹出一个结点，就将其左右子树节点压入栈  层序打印树
{
	queue<node *>a;
	a.push(root);
	while (!a.empty())
	{
		cout << a.front()->key;
		node *f;
		f = a.front();
		a.pop();
		if (f->leftchild != NULL)
		{
			a.push(f->leftchild);
		}
		if (f->rightchild != NULL)
		{
			a.push(f->rightchild);
		}
		if (!a.empty())
			cout << " ";
	}
}
void print(node *root)//中序输出
{
	if (root == NULL)
	{
		return;
	}
	print(root->leftchild);
	cout << root->key << " ";
	print(root->rightchild);
	return;
}
void printfront(node *root,node *a)//前序输出
{
	char d;
	int p,f;
	if (root)
	{
		if (a == NULL)
		{
			return;
		}
		if (a->color == black)
			d = 'B';
		else
			d = 'R';
		if (a != root)
			cout << " ";
		cout << a->key << "(" << d << ")";

		printfront(root, a->leftchild);
		printfront(root, a->rightchild);
	}
	else
		cout << "Null";
	return;
}
node * findbrother(node *&root, node *x)//寻找某个节点的兄弟节点
{
	node *r = x;
	if (r == root)//如果该节点为根节点，其兄弟节点为NULL
	{
		return NULL;
	}
	else
	{
		if (r == r->parent->leftchild)//如果该节点为其父亲节点的左孩子
		{
			return (r->parent->rightchild);
		}
		else if (r == r->parent->rightchild)//如果该节点为其父亲节点的右孩子
		{
			return r->parent->leftchild;
		}
	}
}
void rbinsertfixup(node *&root, node *nn)//修正红黑树
{
	if (nn == root)//如果节点为根，改变其颜色为黑色
	{
		nn->color = black;
	}
	else if (nn->parent->color == black)//若父节点是黑色 不用操作
	{

	}
	else if (nn->parent->color == red)//如果父节点为红色
	{
		if (nn->parent == nn->parent->parent->leftchild)//如果父节点是祖父节点的左孩子
		{
			//case1 条件：叔叔节点为红色
			if (findbrother(root, nn->parent) != NULL&&findbrother(root, nn->parent)->color == red)
			{
				nn->parent->color = black;
				findbrother(root, nn->parent)->color = black;
				nn->parent->parent->color = red;
				rbinsertfixup(root, nn->parent->parent);
			}
			else if (findbrother(root, nn->parent) == NULL || findbrother(root, nn->parent)->color == black)
			{
				//case2 条件：叔叔节点为黑色，且当前节点为右孩子
				if (nn == nn->parent->rightchild)
				{
					node *t = nn->parent;
					leftroate(root, t);
					rbinsertfixup(root, t);
				}
				//case3 条件：叔叔节点为黑色，且当前节点为左孩子
				else if (nn == nn->parent->leftchild)
				{
					node *b = NULL;
					nn->parent->color = black;
					nn->parent->parent->color = red;
					b = nn->parent->parent;
					rightroate(root, b);
				}
			}
		}
		else if (nn->parent == nn->parent->parent->rightchild)//若父节点是祖父节点的右孩子
		{
			//case1 条件：叔叔节点是红色
			if (findbrother(root, nn->parent) != NULL&&findbrother(root, nn->parent)->color == red)
			{
				nn->parent->color = black;
				findbrother(root, nn->parent)->color = black;
				nn->parent->parent->color = red;
				rbinsertfixup(root, nn->parent->parent);
			}
			else if (findbrother(root, nn->parent) == NULL || findbrother(root, nn->parent)->color == black)
			{
				//case2条件： 叔叔是黑色，且当前节点是右孩子
				if (nn == nn->parent->rightchild)
				{
					node *b = NULL;
					nn->parent->color = black;
					nn->parent->parent->color = red;
					b = nn->parent->parent;
					leftroate(root, b);
				}
				//case3条件： 叔叔是黑色，且当前节点是左孩子
				else if (nn == nn->parent->leftchild)
				{
					node *t = nn->parent;
					rightroate(root, t);
					rbinsertfixup(root, t);
				}
			}
		}
	}
	//将根节点设为黑色
	root->color = black;
}

void insert(node * &root, node* nn)//newnode  插入节点
{
	node *y = NULL;
	node *x = root;
	//1.将红黑树看作一颗普通的二叉搜索树，将节点插入到二叉树中

	//找出要插入的结点nn在二叉树T中的父亲y
	while (x != NULL)
	{
		y = x;
		if (nn->key < x->key)
		{
			x = x->leftchild;
		}
		else
			x = x->rightchild;
	}
	nn->parent = y;// 设置 “nn的父亲” 为 “y”
	if (y == NULL)
	{
		root = nn;
	}
	else if (nn->key < y->key)//nn小于父亲的值
	{
		y->leftchild = nn;//父亲的左孩子设为nn
	}
	else if (nn->key > y->key)//nn大于父亲的值
	{
		y->rightchild = nn;//父亲的右孩子设为nn
	}
	nn->leftchild = NULL;
	nn->rightchild = NULL;

	//2设置节点颜色为红色
	nn->color = red;
	//3将他修正为一颗二叉搜索树
	rbinsertfixup(root, nn);
	//printfront(root);
	//cout <<"#"<< endl;
}

//后继节点：在二叉树的中序遍历序列中，node的下一个节点叫做node的后继节点
//1.有右子树，那它的下一个节点就是它右子树的最左的节点（若它的右子树没有左子树，那就是右子树本身）
//2.没有右子树，那它是某一个左子树的最后一个节点，然后找到这个左子树的parent即可，找它的parent，直到当前节点是parent的左子树为止

node *findleft(node *p) //寻找最左节点
{
	while (p->leftchild != NULL)
	{
		p = p->leftchild;
	}
	return p;
}
node *findpostnode(node *p)//寻找后继节点
{
	node *parent_p;
	if (p->rightchild != NULL)
	{
		return (findleft(p->rightchild ));
	}
	else
	{
		parent_p = p->parent;
		while (parent_p != NULL)
		{
			if (parent_p->leftchild == p)return parent_p;
			p=parent_p;
			parent_p = p->parent;
		}
		return parent_p;
	}
}
void rbdeletefixup(node *&root, node *x, node *pa)//删除修正
{
	node *z1;
	if (x != root && (x == NULL || x->color == black))//如果x不是根节点并且x是黑色（或者不存在）
	{
		if (pa->leftchild == x)//当前节点是父亲的左孩子
		{
			//case1：x的兄度节点是红色
			if (pa->rightchild != NULL&&pa->rightchild->color == red)//x是"黑+黑"节点，x的兄弟节点是红色,将“Case 1”转换为“Case 2”、“Case 3”或“Case 4”
			{
				pa->rightchild->color = black;
				pa->color = red;
				if (root) {
					root->parent = NULL;
				}
				leftroate(root, pa);
				rbdeletefixup(root, x, pa);
			}
			else if (pa->rightchild != NULL&&pa->rightchild->color == black && (pa->rightchild->leftchild == NULL || pa->rightchild->leftchild->color == black) && (pa->rightchild->rightchild == NULL || pa->rightchild->rightchild->color == black))
			{//case2：x是“黑+黑”节点，x的兄弟节点是黑色，x的兄弟节点的两个孩子都是黑色。
					//将“x中多余的一个黑色属性上移(往根方向移动)”
				pa->rightchild->color = red;
				z1 = pa;
				pa = z1->parent;
				rbdeletefixup(root, z1, pa);
			}
			else if (pa->rightchild != NULL&&pa->rightchild->color == black&&pa->rightchild ->leftchild !=NULL&&pa->rightchild->leftchild->color == red && (pa->rightchild->rightchild == NULL || pa->rightchild->rightchild->color == black))
				//case3：x是“黑+黑”节点，x的兄弟节点是黑色；x的兄弟节点的左孩子是红色，右孩子是黑色的。
				//将“Case 3”进行转换，转换成“Case 4”
			{
				pa->rightchild->leftchild->color = black;
				pa->rightchild->color = red;
				if (root) {
					root->parent = NULL;
				}
				rightroate(root, pa->rightchild);
				rbdeletefixup(root, x, pa);
			}
			else if (pa->rightchild != NULL&&pa->rightchild->color == black&&pa->rightchild ->rightchild !=NULL&&pa->rightchild->rightchild->color == red)
			{//case4：x的兄弟节点是黑色，兄弟节点的右孩子是红色
				pa->rightchild->color = pa->color;
				pa->color = black;
				pa->rightchild->rightchild->color = black;
				if (root) {
					root->parent = NULL;
				}
				leftroate(root, pa);
				x = root;
				rbdeletefixup(root, x, pa);
			}

		}
		else if (pa->rightchild == x)//x是其父亲的右孩子
		{
			//case1：//x是"黑+黑"节点，x的兄弟节点是红色,将“Case 1”转换为“Case 2”、“Case 3”或“Case 4”
			if (pa->leftchild != NULL&&pa->leftchild->color == red)
			{
				pa->leftchild->color = black;
				pa->color = red;
				if (root) {
					root->parent = NULL;
				}
				rightroate(root, pa);
				rbdeletefixup(root, x, pa);
			}
			else if (pa->leftchild != NULL&&pa->leftchild->color == black &&  (pa->leftchild->leftchild == NULL || pa->leftchild->leftchild->color == black)&& (pa->leftchild->rightchild == NULL || pa->leftchild->rightchild->color == black))
			{//case2：x是“黑+黑”节点，x的兄弟节点是黑色，x的兄弟节点的两个孩子都是黑色。																									   //将“x中多余的一个黑色属性上移(往根方向移动)”

				pa->leftchild->color = red;
				z1 = pa;
				pa = pa->parent;;
				rbdeletefixup(root, z1, pa);

			}
			else if (pa->leftchild != NULL&&pa->leftchild->color == black &&pa->leftchild ->rightchild !=NULL&&pa->leftchild->rightchild->color == red && (pa->leftchild->leftchild == NULL || pa->leftchild->leftchild->color == black))
				//case3：x是“黑+黑”节点，x的兄弟节点是黑色；x的兄弟节点的右孩子是红色，左孩子是黑色的。	
				//将“Case 3”进行转换，转换成“Case 4”
			{
				pa->leftchild->rightchild->color = black;
				pa->leftchild->color = red;
				if (root) {
					root->parent = NULL;
				}
				leftroate(root, pa->leftchild);
				rbdeletefixup(root, x, pa);
			}
			else if (pa->leftchild != NULL&&pa->leftchild->color == black &&pa->leftchild ->leftchild !=NULL&&pa->leftchild->leftchild->color == red)
			{//case4：兄弟节点为黑色，兄弟节点左孩子为红色，右孩子随意
				pa->leftchild->color = pa->color;
				pa->color = black;
				pa->leftchild->leftchild->color = black;
				if (root) {
					root->parent = NULL;
				}
				rightroate(root, pa);
				x = root;
				rbdeletefixup(root, x, pa);
			}
		}
	}
	if (x)
	{
		x->color = black;
	}
}
void rbdelete(node * &root,node * z)
{
	node *child,*parent;
	nodecolor col;
	if (z->leftchild == NULL || z->rightchild == NULL)//有1个孩子或者没有孩子
	{
		parent = z->parent;
		if (z->leftchild != NULL)//如果存在非空孩子，寻找孩子赋给child
		{
			child = z->leftchild;
		}
		else
		{
			child = z->rightchild;
		}
		if (child)//如果孩子存在，将z的父亲设置为child的父亲
		{
			child->parent = z->parent;
		}
		if (z->parent)//z的父亲存在，将z父亲的孩子设置为child
		{
			if (z == z->parent->leftchild)
			{
				z->parent->leftchild = child;
			}
			else
				z->parent->rightchild = child;
			
		}
		else//如果z为根节点，将child设置为根
		{
			root = child;
		}
		if (root) {
			root->parent = NULL;
		}
		if (z->color == black)//如果z是黑色的，修正颜色
		{
				rbdeletefixup(root, child,parent);
		}
		delete z;
	}
	else//有双子节点  用后继节点y替换z 然后把y删除
	{
		node *y= findpostnode(z);//y是后继节点
		if (z!=root)//z不是根，设置z父亲的相应孩字为y
		{
			if (z == z->parent->leftchild)
			{
				z->parent->leftchild = y;
			}
			else
				z->parent->rightchild = y;
		}
		else//z是根，将根设置为y
		{
			root = y;
		}
		
		child = y->rightchild;//child 是替代节点的右孩子，
		//后继节点最多只有右节点 肯定不存在左孩子，因为它是一个后继节点，如果存在，那么一定先检索到左孩子，它是右子树最小节点
		col = y->color;//保存节点颜色
		parent = y->parent;//如果child为空，后面再找它的父亲是找不到的
		//删除替代节点 y
		if (y->parent == z)//被删除节点是它后继节点的父节点
		{
			parent = y;
		}
		else
		{
			if (child)//后继节点要么没有儿子要么只有一个。如果有1个儿子，直接删除该节点，并用该节点的唯一子节点顶替它的位置。
			{
				child->parent = y->parent;
			}
			y->parent->leftchild = child;
			y->rightchild = z->rightchild;
			z->rightchild->parent = y;
		}
		//替换节点y变成删除节点
		y->parent = z->parent;
		y->color = z->color;
		y->leftchild = z->leftchild;
		z->leftchild->parent = y; 
		if (root) {
			root->parent = NULL;
		}
		if (col == black)
				rbdeletefixup(root, child,parent);

		delete z;
	}
}
node *search(node *&root,int a)//查找关键字为a的节点
{//使用层序输出的方法，逐层比较节点的关键值
	queue<node *>u;
	if (root != NULL)
	{
		u.push(root);
		while (!u.empty())
		{
			if (a == u.front()->key)
			{
				return u.front();
			}
			node *o = u.front();
			u.pop();
			if (o->leftchild != NULL)
			{
				u.push(o->leftchild);
			}
			if (o->rightchild != NULL)
			{
				u.push(o->rightchild);
			}
		}
	}
	return NULL;
}
void rbremovekey(node *&root,node *p)//查找p->value对应的节点，找到就删除
{
	node *z=new node;
	if ((z = search(root, p->key)) != NULL)
	{
		rbdelete(root, z);
	}
}
void findmax(node *root)//寻找最大值
{
	int max = root->key;
	queue<node *>a;
	a.push(root);
	while (!a.empty())
	{
		if (a.front()->key > max)
		{
			max = a.front()->key;
		}
		node *f;
		f = a.front();
		a.pop();
		if (f->leftchild != NULL)
		{
			a.push(f->leftchild);
		}
		if (f->rightchild != NULL)
		{
			a.push(f->rightchild);
		}
	}
	cout << max;
}
void findmin(node *root)//寻找最小值
{
	int min = root->key;
	queue<node *>a;
	a.push(root);
	while (!a.empty())
	{
		if (a.front()->key < min)
		{
			min = a.front()->key;
		}
		node *f;
		f = a.front();
		a.pop();
		if (f->leftchild != NULL)
		{
			a.push(f->leftchild);
		}
		if (f->rightchild != NULL)
		{
			a.push(f->rightchild);
		}
	}
	cout << min;
}
void swap(int a[], int i, int j)
{
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}
int main()
{
	int size;
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
			m[i] = i + 1;
			n[i] = i + 1;
		}
		for (int i = size - 1; i >= 1; --i) {
			swap(m, i, rand() % i);
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
		//RB树1 递增插入 相同顺序删除
		/*for (int i = 0; i < size; i++)
		{
			node *p = new node;
			p->key = up[i];
			insert(root, p);
		}
		for (int i = 0; i < size; i++)
		{
			node *p = new node;
			p->key = up[i];
			rbremovekey(root, p);
		}*/
		//RB树2 递增插入相反删除
		for (int i = 0; i < size; i++)
		{
			node *p = new node;
			p->key = up[i];
			insert(root, p);
		}
		for (int i = 0; i < size; i++)
		{
			node *p = new node;
			p->key = down[i];
			rbremovekey(root, p);
		}
		//RB树3 随机插入随机删除 10000Use Time:139.314663
		/*
		for (int i = 0; i < size; i++)
		{
			node *p = new node;
			p->key = m[i];
			if (root)
				root->parent = NULL;
			insert(root, p);
		}
		for (int i = 0; i < size; i++)
		{
			node *p = new node;
			p->key = n[i];
			if (root)
				root->parent = NULL;
			rbremovekey(root, p);
		}*/
		QueryPerformanceCounter(&t2);
		printf("%f", (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart);
		cout << endl;
	}
	system("pause");
	return 0;
}