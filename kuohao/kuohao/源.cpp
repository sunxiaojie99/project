/*
功能：利用栈来检查一个字符串中的括号是否左右匹配。字符串长度不超过100，含有三种括号(),[],{},字母及其他符号。
规定任何一个左括号都从内到外与在它右边且距离最近的对应右括号相匹配。
程序输入：一个带括号的字符串，不超过100个字符
程序输出：如果输入的字符串中括号匹配，输出1，如果不匹配，输出0。
要求：利用栈来判断括号是否匹配
注意：出栈时，考虑栈是否为空；最后匹配的结果应该是栈为空。
示例测试集:
- 第1组
输入：
{ab[c(de)f]g}hi
输出：
1
- 第2组
输入：
while(){i++[a=3;(C++]);};)
输出：
0
- 第3组
输入：
{ab{c[d[(h(i)j)k]l}}{
输出：
0
*/

#include<iostream>
#include<stack>
#include<string>
#include<cstdlib>
using namespace std;
int main()
{
	stack<char> skuohao;
	stack<char> mkuohao;
	stack<char> bkuohao;
	skuohao.push('#');
	mkuohao.push('#');
	bkuohao.push('#');
	string a;
	int res0 = 1, res1 = 1, res2 = 1;
	cin >> a;
	for (int i = 0; i < a.length(); i++)
	{
		if (a[i] == '(')
		{
			skuohao.push('(');
		}
		if (a[i] == ')')
		{
			if (skuohao.top() == '(')
			{
				skuohao.pop();
			}
			else if (skuohao.top() == '#')
			{
				res1 = 0;
				break;
			}
		}
	}
	for (int i = 0; i < a.length(); i++)
	{
		if (a[i] == '[')
		{
			mkuohao.push('[');
		}
		if (a[i] == ']')
		{
			if (mkuohao.top() == '[')
			{
				mkuohao.pop();
			}
		 else if (mkuohao.top() == '#')
			{
				res1 = 0;
				break;
			}
		}
	}
	for (int i = 0; i < a.length(); i++)
	{
		if (a[i] == '{')
		{
			bkuohao.push('{');
		}
		if (a[i] == '}')
		{
			if (bkuohao.top() == '{')
			{
				bkuohao.pop();
			}
		    else if (bkuohao.top() == '#')
			{
				res2 = 0;
				break;
			}
		}
	}
	if (res0 == 0||res1==0||res2==0||skuohao.top() != '#' || mkuohao.top() != '#' || bkuohao.top() != '#')
		cout << 0;
	else cout << 1;
	system("pause");
	return 0;
}