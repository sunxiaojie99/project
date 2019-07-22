/*
Z=<a,b,f,c> is a subsequence of the sequence X=<a,b,c,f,b,c>, and the index of the subsequence in X is <1,2,4,6>. Z里面的元素在X里全都出现，且顺序不变，
那么Z是X的子序列
先给出两个字符串，求他们最长的共同的子序列
*/
/*
c[i][j]代表字符串x的第i-1个字符和字符串y中第j-1个字符（因为是从0开始的索引）的lcs
引进一个二维数组c[][]，用c[i][j]记录X[i]与Y[j] 的LCS 的长度，b[i][j]记录c[i][j]是通过哪一个子问题的值求得的，以决定搜索的方向。
我们是自底向上进行递推计算，那么在计算c[i,j]之前，c[i-1][j-1]，c[i-1][j]与c[i][j-1]均已计算出来。
此时我们根据X[i] = Y[j]还是X[i] != Y[j]，就可以计算出c[i][j]。
*/
/*令给定的字符序列X=“x0，x1，…，xm-1”，序列Y=“y0，y1，…，yk-1”是X的子序列，存在X的一个严格递增下标序列<i0，i1，…，ik-1>，使得对所有的j=0，1，…，k-1，有xij=yj。例如，X=“ABCBDAB”，Y=“BCDB”是X的一个子序列。

考虑最长公共子序列问题如何分解成子问题，设A=“a0，a1，…，am-1”，B=“b0，b1，…，bm-1”，并Z=“z0，z1，…，zk-1”为它们的最长公共子序列。不难证明有以下性质：

（1） 如果am-1=bn-1，则zk-1=am-1=bn-1，且“z0，z1，…，zk-2”是“a0，a1，…，am-2”和“b0，b1，…，bn-2”的一个最长公共子序列；

（2） 如果am-1!=bn-1，则若zk-1!=am-1，蕴涵“z0，z1，…，zk-1”是“a0，a1，…，am-2”和“b0，b1，…，bn-1”的一个最长公共子序列；

（3） 如果am-1!=bn-1，则若zk-1!=bn-1，蕴涵“z0，z1，…，zk-1”是“a0，a1，…，am-1”和“b0，b1，…，bn-2”的一个最长公共子序列。

这样，在找A和B的公共子序列时，如有am-1=bn-1，则进一步解决一个子问题，找“a0，a1，…，am-2”和“b0，b1，…，bm-2”的一个最长公共子序列；
如果am-1!=bn-1，则要解决两个子问题，找出“a0，a1，…，am-2”和“b0，b1，…，bn-1”的一个最长公共子序列
和找出“a0，a1，…，am-1”和“b0，b1，…，bn-2”的一个最长公共子序列，再取两者中较长者作为A和B的最长公共子序列。
*/
#include<iostream>
#include<string>
#include<stack>
using namespace std;
void printlac(string x, string y,int i,int j, int flag[200][200]) {
	stack<char>l;
	if (i == 0 || j == 0)
		return;
	if (flag[i][j] == 1) {
		l.push(x[i - 1]);
		printlac(x, y, i - 1, j - 1, flag);
	}
	else if (flag[i][j] == 2) {
		printlac(x, y, i - 1, j, flag);
	}
	else if (flag[i][j] == 3) {
		printlac(x, y, i, j - 1, flag);
	}
	while (!l.empty()) {
		cout << l.top()<<" ";
		l.pop();
	}
}
int max(int a, int b) {
	if (a > b)
		return a;
	else return b;
}
int LCS(int a[200][200], string x, string y, int flag[200][200]) {
	int xsize = x.length();
	int ysize = y.length();
	for (int i = 0; i <= xsize; i++) {
		a[i][0] = 0;
	}
	for (int j = 0; j <= ysize; j++) {
		a[0][j] = 0;
	}
	for (int i = 1; i <= xsize; i++) {
		for (int j = 1; j <= ysize; j++) {
			if (x[i-1] == y[j-1]) {
				a[i][j] = a[i - 1][j - 1] + 1;
				flag[i][j] = 1;
			}
			else {
				a[i][j] = max(a[i - 1][j], a[i][j - 1]);
				if (a[i][j] == a[i - 1][j])
					flag[i][j] = 2;
				else flag[i][j] = 3;
			}
		}
	}
	return a[xsize][ysize];
}
int main() {
	int a[200][200];
	int flag[200][200];
	string x;
	string y;
	cin >> x>>y;
	cout<<LCS(a, x, y, flag)<<endl;
	//printlac(x, y, x.size(), y.size(), flag);
	system("pause");
	return 0;
}