/*
定义：m阶B-树（B-Tree of order m）是一棵m叉搜索树，如果B-树非空，那么相应的扩充树满足下列特征：
√根节点至少有2个孩子
√除根节点外，所有内部节点至少有ceil[m/2]个孩子 (ceil(m/2)-1个元素)
√所有外部节点（叶节点）位于同一层上

二阶B-树：满二叉树 //所有叶节点在同一层，必须是满二叉树
三阶B-树：2-3树 //可以有2、3个叉 孩子
四阶B-树：2-3-4树

B 树又叫平衡多路查找树。一棵m阶的B 树 (m叉树)的特性如下：
	树中每个结点最多含有m个孩子（m>=2）；
	除根结点和叶子结点外，其它每个结点至少有[ceil(m / 2)]个孩子（其中ceil(x)是一个取上限的函数）；
	若根结点不是叶子结点，则至少有2个孩子（特殊情况：没有孩子的根结点，即根结点为叶子结点，整棵树只有一个根节点）；
	所有叶子结点都出现在同一层，叶子结点不包含任何关键字信息(可以看做是外部接点或查询失败的接点，实际上这些结点不存在，
指向这些结点的指针都为null)；
	每个非终端结点中包含有n个关键字信息： (n，P0，K1，P1，K2，P2，......，Kn，Pn)。其中：
a)   Ki (i=1...n)为关键字，且关键字按顺序升序排序K(i-1)< Ki。
b)   Pi为指向子树根的接点，且指针P(i-1)指向子树种所有结点的关键字均小于Ki，但都大于K(i-1)。
c)   关键字的个数n必须满足： [ceil(m / 2)-1]<= n <= m-1。
https://blog.csdn.net/jesseshen/article/details/6643747
*/
/*
typedef struct Student
　　　　{
	　　　　int a;
		　　　　}Stu;
			　　　　于是在声明变量的时候就可：Stu stu1;(如果没有typedef就必须用struct Student stu1;来声明)
				　　　　这里的Stu实际上就是struct Student的别名。Stu==struct Student
*/
#include<iostream>
#include<Queue>
#include<vector>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<functional>
#include<Windows.h>
#define Keytype int
#define Record string
using namespace std;
const int m = 4;//阶数
typedef struct btnode {
public:
	int keynum;//节点关键字个数
	Keytype key[m + 1];//关键字数组 key[0]未用 4阶 最多有3个元素
	//1<=n<=3
	struct btnode *parent;//双亲结点指针
	struct btnode *ptr[m + 1];//孩子结点指针数组 最多有4个孩子指针 从0开始
	Record *recptr[m + 1];
	btnode()
	{
		keynum = 0;
		parent = NULL;
		for (int i = 0; i < m + 1; i++)
		{
			ptr[i] = NULL;
		}
	}
}btnode,*btree;
btree t = NULL;
class result {//b树查找的结果类型
public:
	btree pt;//指向找到的节点
	int i;//1<=i<=m 在节点中关键字位序
	int tag;//1 查找成功 0查找失败
};
int search(btree p,int k)//在p->key[1..p->keynum]找k 
{
	int i = 1;
	while (i <= p->keynum &&k > p->key[i])i++;
	return i;
}
void searchbtree(btree t,int k,result &r)
{
	//在m阶B树t上查找关键字k，用r返回(pt,i,tag).
	//若查找成功，则标记tag=1，指针pt所指结点中第i个关键字等于k；
	//否则tag=0，若要插入关键字为k的记录，应位于pt结点中第i-1个和第i个关键字之间
	int i = 0,found = 0;
	btree p = t, q = NULL;
	//初始，p指向根节点，p将用于指向待查找结点，q指向其双亲
	while (p != NULL && found == 0)
	{
		i = search(p, k);
		if (i <= p->keynum &&p->key[i] == k)//在关键字范围内 并且值相等
		{
			found = 1;
		}
		else
		{
			q = p;
			p = p->ptr[i - 1];//指针下移
		}
	}
	if (found == 1)
	{
		r = { p,i,1 };
	}
	else
	{
		r = { q,i,0 };
	}
}
void split(btree &q, int s, btree &ap) {
	//将q结点分裂成两个结点，前一半保留在原结点，
	//后一半移入ap所指新结点
	int n = q->keynum;
	ap = (btnode*)malloc(sizeof(btnode));//生成新的节点
	ap->ptr[0] = q->ptr[s];
	for (int i = 1, j = s + 1; j <= n; j++, i++)//后一半移入ap
	{
		ap->ptr[i] = q->ptr[j];
		ap->key[i] = q->key[j];
	}
	ap->keynum = n - s;
	q->keynum = s - 1;
	ap->parent = q->parent;//新节点的父亲指针
	for (int i = 0; i <= ap->keynum; i++)//孩子节点的父亲重新赋值
	{
		if (ap->ptr[i]!=NULL)
		{
			ap->ptr[i]->parent = ap;
		}
	}
}
void newroot(btree &t, btree p,int x, btree ap)//生成新的根 只有2个孩子
{
	t = (btnode*)malloc(sizeof(btnode));
	t->keynum = 1; t->ptr[0] = p; t->ptr[1] = ap;
	t->key[1] = x;
	if (p!=NULL)p->parent = t;
	if (ap!=NULL)ap->parent = t;
	t->parent = NULL;
}
void insert(btree &q, int i, int x, btree ap)
{
	//关键字x和新结点指针ap分别插到q->key[i]和q->ptr[i]
	int n = q->keynum;
	for (int j = n; j >= i; j--)
	{
		q->key[j + 1] = q->key[j];
		q->ptr[j + 1] = q->ptr[j + 1];
	}
	q->key[i] = x;
	q->ptr[i] = ap;
	if (ap!=NULL)ap->parent = q;
	q->keynum++;
}
void insertbtree(btree &t,int k, btree q,int i)
{
	//在B树中q结点的key[i-1]和key[i]之间插入关键字k
	//若插入后结点关键字个数等于b树的阶，则沿着双亲指针链进行结点分裂，使得t仍是m阶B树
	int x, s, finished = 0, neednewroot = 0;
	btree ap;
	if (q == NULL)
		newroot(t, NULL, k, NULL);
	else
	{
		x = k; ap =NULL;
		while (neednewroot == 0 && finished == 0)
		{
			insert(q, i, x, ap);//x和ap分别插到q->key[i]和q->ptr[i]
			if (q->keynum < m)finished = 1;//插入完成
			else
			{
				s = (m + 1) / 2;//最小元素个数
				split(q, s, ap);
				x = q->key[s];
				if (q->parent!=NULL)
				{
					q = q->parent;
					i = search(q, x);
					//在双亲结点中查找x的插入位置
				}
				else
				{
					neednewroot = 1;
				}
			}
		}
		if (neednewroot == 1)
		{
			//t是空树或者根结点已经分裂成为q和ap结点
			newroot(t, q, x, ap);
		}
	}
}
void successor(btree &p,int i)//由后继最下层非终端结点的最小关键字代替结点中关键字key[i]
{
	btree child = p->ptr[i];
	while (p->ptr[0]!=NULL)child = child->ptr[0];
	p->key[i] = child->key[i];
	p = child;
}
void remove(btree &p,int i)
{
	int j, n = p->keynum;
	for (j = i; j < n; j++)
	{
		p->key[j] = p->key[j + 1];
		p->ptr[j] = p->ptr[j + 1];
	}
	p->keynum--;
}
void restore(btree &p, int i, btree &t)//对b树进行调整
{
	int j;
	btree ap = p->parent;
	if (ap == NULL)//如果调整后出现空的根节点，则删除该根节点，树高减1
	{
		t = p; //根节点向下移
		p = p->parent;
		return;
	}
	btree lc, rc, pr;//左兄弟右兄弟
	int finished = 0, r = 0;
	while (!finished)
	{
		r = 0;
		while (ap->ptr[r] != p)r++;//确定p在ap子树中的位置
		if (r == 0)
		{
			r++;
			lc = NULL; rc = ap->ptr[r];
		}
		else if (r == ap->keynum)
		{
			rc = NULL; lc = ap->ptr[r - 1];
		}
		else
		{
			lc = ap->ptr[r - 1];
			rc = ap->ptr[r + 1];
		}
		if (r > 0 && lc != NULL && (lc->keynum > (m - 1) / 2))//向左兄弟借关键字
		{
			p->keynum++;
			for (j = p->keynum; j > 1; j--)//关键字右移
			{
				p->key[j] = p->key[j - 1];
				p->ptr[j] = p->ptr[j - 1];
			}
			p->key[1] = ap->key[r];//父亲插入到节点
			p->ptr[1] = p->ptr[0];
			p->ptr[0] = lc->ptr[lc->keynum];//把左兄弟的最右孩子赋给节点的最左孩子
			if (p->ptr[0]!=NULL)//修改p中的子女的父节点为p
				p->ptr[0]->parent = p;
			ap->key[r] = lc->key[lc->keynum];//左兄弟上移到父亲位置
			lc->keynum--;
			finished = 1;
			break;
		}
		else if(ap->keynum >r&&rc!=NULL&&(rc->keynum >(m-1)/2))//向右节点借
		{
			p->keynum++;
			rc->ptr[0] = rc->ptr[1];//key是从1 开始的，所以单独把ptr0拎出来
			for (j = 1; j < rc->keynum; j++)//右兄弟节点关键字左移
			{
				p->key[j] = p->key[j+1];
				p->ptr[j] = p->ptr[j + 1];
			}
			p->key[p->keynum] = ap->key[r];//父亲插入到节点
			p->ptr[p->keynum] = rc->ptr[0];//右兄弟节点最左孩子赋值给该节点的最右孩子
			if (p->ptr[p->keynum]!=NULL)//修改p中子女的父节点
			{
				p->ptr[p->keynum]->parent = p;
			}
			ap->key[r] = rc->key[1];//右兄弟上移到父亲位置
			rc->keynum--;
			finished = 1;
			break;
		}
		r = 0;
		while (ap->ptr[r] != p)//重新确定p在ap中的位置
			r++;
		if (r > 0 && (ap->ptr[r - 1]->keynum <= (m - 1) / 2))//与左兄弟合并
		{
			lc = ap->ptr[r - 1];
			p->keynum++;
			for (j = p->keynum; j > 1; j--)//将p结点关键字和指针右移一位
			{
				p->key[j] = p->key[j - 1];
				p->ptr[j] = p->ptr[j - 1];
			}
			p->ptr[1] = p->ptr[0];
			p->key[1] = ap->key[r];
			ap->ptr[r] = lc;
			for (j = 1; j <= lc->keynum + p->keynum; j++) //将结点p中关键字和指针移到p左兄弟中
			{
				lc->key[lc->keynum + j] = p->key[j];
				lc->ptr[lc->keynum + j] = p->ptr[j];
			}
			if (p->ptr[0])//修改p中子女的父节点lc
			{
				for (j = 1; j <= p->keynum; j++)//////////////////////////////////
					if (p->ptr[p->keynum + j])
						p->ptr[p->keynum + j]->parent = lc;
			}
			ap->keynum--;
			pr = p;
			free(pr);
			pr = NULL;
			p = lc;
		}
		else//与右兄弟合并
		{
			rc = ap->ptr[r + 1];
			if (r == 0)
				r++;
			p->keynum++;
			p->key[p->keynum] = ap->key[r];//父结点的关键字与p合并
			p->ptr[p->keynum] = rc->ptr[0]; //从右兄弟左移一个指针
			rc->keynum = p->keynum + rc->keynum;//合并后关键字的个数
			ap->ptr[r - 1] = rc;
			for (j = 1; j <= (rc->keynum - p->keynum); j++)//将p右兄弟关键字和指针右移
			{
				rc->key[p->keynum + j] = rc->key[j];
				rc->ptr[p->keynum + j] = rc->ptr[j];
			}
			for (j = 1; j <= p->keynum; j++)//将结点p中关键字和指针移到p右兄弟
			{
				rc->key[j] = p->key[j];
				rc->ptr[j] = p->ptr[j];
			}
			rc->ptr[0] = p->ptr[0];//修改p中子女父节点为rc
			if (p->ptr[0])
			{
				for (j = 1; j <= p->keynum; j++)//////////////////////////////////////
				{
					if (p->ptr[p->keynum + j])
						p->ptr[p->keynum + j]->parent = rc;
				}
			}
			for (j = r; j<ap->keynum; j++)//将父结点中关键字和指针左移
			{
				ap->key[j] = ap->key[j + 1];
				ap->ptr[j] = ap->ptr[j + 1];
			}
			ap->keynum--;//父结点的关键字个数减1
			pr = p;
			free(pr);
			pr = NULL;
			p = rc;
		}
		ap = ap->parent;
		if (p->parent->keynum >= (m - 1) / 2 || (NULL == ap&&p->parent->keynum > 0))
		{
			finished = 1;
		}
		else if (ap == NULL)//若调整后出现空的根结点，则删除该根结点，树高减1
		{
			pr = t;
			t = p;//根结点下移
			free(pr);
			pr = NULL;
			finished = 1;
		}
		p = p->parent;
	}
}
void deletebtree(btree &p,int i, btree &t)//删除B树上p结点的第i个关键字
{
	if (p->ptr[i] != NULL)//若不是在最下层非终端结点
	{
		successor(p, i);//在Ai子树中找出最下层非终端结点的最小关键字替代ki
		deletebtree(p, 1, t);//转换为删除最下层非终端结点的最小关键字
	}
	else {//若是最下层非终端结点
		remove(p, i);
		if (p->keynum<(m - 1) / 2)//删除后关键字个数小于(m-1)/2
			restore(p, i, t);//调整B树
	}
}
void show_Btree(btree &p)
{
	if (p == NULL) { puts("B tree does not exist"); return; }
	bool have_child = false;
	cout << "[";
	for (int i = 1; i <= p->keynum; i++)
	{
		if (i == 1);
		else cout << " ";
		cout << p->key[i];
	}
	cout << "]";
	for (int i = 0; i <= p->keynum; i++)
	{
		if (p->ptr[i] != NULL)
		{
			if (i == 0) cout << "<";
			else cout << ",";
			show_Btree(p->ptr[i]);
			have_child = true;
		}
	}
	if (have_child) cout<< ">";
}
void show_Btree2(btree &p, int deep)
{
	if (p == NULL) { return; }
	int i;
	for (i = 0; i < p->keynum; i++)
	{
		show_Btree2(p->ptr[i], deep + 1);
		for (int i = 0; i<deep; i++)
		{
			printf("\t");
		}
		printf("%d\n", p->key[i + 1]);
	}
	show_Btree2(p->ptr[i], deep + 1);

}
void destory(btree &t)
{
	int i = 0;
	if (t!=NULL)
	{
		while (i < t->keynum)
		{
			destory(t->ptr[i]);
			free(t->ptr[i]);
			i++;
		}
	}
	free(t);
	t = NULL;
}
void insert_keytype()
{
	Keytype temp;
	cin >> temp;
	result p;
	searchbtree(t, temp, p);
	if (p.tag == 0)
	{
		insertbtree(t, temp, p.pt, p.i);
		puts("Insert success"); show_Btree(t);
		puts("");
	}
	else
		puts("The element is already in the B tree.");
}
void find_keytype()
{
	puts("enter an element to find");
	Keytype temp;
	cin >> temp;
	result p;
	searchbtree(t, temp, p);
	if (p.tag)
	{
		puts("find success");
	}
	else
		puts("lookup failure");
}
void delete_keytype()
{
	puts("enter an element to be deleted");
	Keytype temp;
	cin >> temp;
	result p;
	searchbtree(t, temp, p);
	if (p.tag)
	{
		deletebtree(p.pt, p.i, t);
		puts("delete success");
		show_Btree(t);
		puts("");
	}
	else
		puts("The element does not exist in the B tree.");
}
void swap(int a[], int i, int j)
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
		//计时函数

		LARGE_INTEGER t1, t2, tc;
		QueryPerformanceFrequency(&tc);
		QueryPerformanceCounter(&t1);

		btree T = new btnode;
		T->keynum = 0;
		result p;
		//BTree1 递增插入 相同顺序删除
		for (int i = 0; i < size; i++)
		{
			searchbtree(t, up[i], p);
			insertbtree(t, up[i], p.pt, p.i);
		}
		for (int i = 0; i<size; i++)
		{
			searchbtree(T, up[i], p);
			if (p.tag)
			{
				deletebtree(p.pt, p.i, T);
			}
			else
			{
				printf("%d is not in the tree\n", up[i]);
			}
		}
		//BTree2 递增插入，相反顺序删除
		for (int i = 0; i < size; i++)
		{
			searchbtree(t, up[i], p);
			insertbtree(t, up[i], p.pt, p.i);
		}
		for (int i = 0; i<size; i++)
		{
			searchbtree(T, down[i], p);
			if (p.tag)
			{
				deletebtree(p.pt, p.i, T);
			}
			else
			{
				printf("%d is not in the tree\n", down[i]);
			}
		}
		//BTree3 随机插入随机删除
		for (int i = 0; i < size; i++)
		{
			searchbtree(t, m[i], p);
			insertbtree(t, m[i], p.pt, p.i);
		}
		for (int i = 0; i<size; i++)
		{
			searchbtree(T, n[i], p);
			if (p.tag)
			{
				deletebtree(p.pt, p.i, T);
			}
			else
			{
				printf("%d is not in the tree\n", n[i]);
			}
		}

		QueryPerformanceCounter(&t2);
		printf("%f", (t2.QuadPart - t1.QuadPart)*1.0 / tc.QuadPart);
		cout << endl;
	}
	system("pause");
	return 0;
}