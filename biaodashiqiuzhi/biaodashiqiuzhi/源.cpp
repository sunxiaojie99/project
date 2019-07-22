/*
描述:
设计一个表达式求值的程序。该程序必须可以接受包含（，），+，-，*，/，%和^(求幂)的中缀表达式，并求出结果。如果表达式正确，则输出表达式的值，如果表达式非法，则输出错误信息。
注意2^2^3转为后缀应为223^^
输入要求：
多个表达式，每个表达式占一行。
输出要求：
对每个表达式，如果为正确表达式则输出结果（精确到小数点后两位），如果为错误表达式则输出“ERROR IN INFIX NOTATION”.

示例测试集:
- 第1组
输入：
(2-4)^3
输出：
-8.00
*/
//1.double atof(const char *nptr);
//把字符串转换成浮点数值。
//<math.h>或<stdlib.h>
//nptr：带转换的字符串。
//若无溢出，返回字符串的双精度浮点数值。
//
//int atoi(const char* nptr);
//把字符串转换成整型数。
//<stdlib.h>
//nptr:带转换的字符串。
//	成功转换，返回字符串的整数值；若无法转换返回0.
//
/*
2.数字转化为字符串
● itoa()：将整型值转换为字符串。
● ltoa()：将长整型值转换为字符串。
● ultoa()：将无符号长整型值转换为字符串。
● gcvt()：将浮点型数转换为字符串，取四舍五入。
● ecvt()：将双精度浮点型值转换为字符串，转换结果中不包含十进制小数点。
● fcvt()：指定位数为转换精度，其余同ecvt()。
*/
#include<iostream>
#include<stack>
#include<string>
#include<cmath>
#include<queue>
#include<iomanip>//保留2位输出头文件
using namespace std;
int judge(char a1, char a2)//a1为栈内的操作符（栈顶元素），a2为栈外的，1为<，-1为>=,栈内的运算符如果大于等于栈外的则需要弹出，然后小的压栈
{
	int x1, x2;
	if (a1 == '+' || a1 == '-')
		x1 = 1;
	else if (a1 == '*' || a1 == '/' || a1 == '%')
		x1 = 3;
	else if (a1 == '^')
		x1 = 5;
	else if (a1 == '(')
		x1 = -2;
	else if (a1 == '#')
		x1 = -3;

	if (a2 == '+' || a2 == '-')
		x2 = 1;
	else if (a2 == '*' || a2 == '/' || a2 == '%')
		x2 = 3;
	else if (a2 == '^')
		x2 = 5;

	if (x2 <= x1) return -1;//是符号则判断和栈顶符号的优先级，是右括号或者优先级不高于（小于等于）栈顶符号则栈顶元素一次出栈并输出
	else if (x1<x2)return 1;//优先级高于栈顶元素
}
//(6+7)/1.3-2^0.5*4
//(90-88)/2*3
//符号运算
double run(char c, double d1, double d2)
{
	double d=0.0;
	if (c == '+')
		d = d1 + d2;
	if (c == '-')
		d = d1 - d2;
	if (c == '*')
		d = d1*d2;
	if (c == '/')
		d = d1 / d2;
	if (c == '%')
		d = int(d1) % int(d2);
	if (c == '^')
	{
		d = pow(d1, d2);
	}
	return d;	
}
int main()
{
	string str;
	while(cin >> str)
	{
		queue<char>back;
		stack<char>fuhao;
		int length = str.length();
		fuhao.push('#');
		int i = 0, j = 0;
		int flag = 1;

		//检验括号匹配问题
		stack<char>skuohao;
		skuohao.push('#');
		int w = 0;
		int res1 = 1;
		for (w = 0; w < length; w++)
		{
			if (str[w] == '(')
			{
				skuohao.push('(');
			}
			else if (str[w] == ')')
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
		if (res1 == 0 || skuohao.top() != '#')
		{
			cout << "ERROR IN INFIX NOTATION"<<endl;
			flag = 0;
		}

		if (flag != 0)//a/b b不能为0  a%b b不能为0  0的0次方没有意义
		{
			for (int y = 0; y < length; y++)
			{
				if (str[y] == '/')
				{
					if (str[y + 1] == '0')
					{
						cout << "ERROR IN INFIX NOTATION" << endl;
						flag = 0;
						break;
					}
				}
				if (str[y] == '%')
				{
					if (str[y + 1] == '0')
					{
						cout << "ERROR IN INFIX NOTATION" << endl;
						flag = 0;
						break;
					}
				}
				if (str[y] == '^')
				{
					if (str[y - 1] == '0')
					{
						cout << "ERROR IN INFIX NOTATION" << endl;
						flag = 0;
						break;
					}
				}
			}
		}
		//检查是否有两个运算符连着
		if (flag != 0)
		{
			int count = 0;
			for (int p = 0; p < length; p++)
			{
				if (str[p] == '+' || str[p] == '-' || str[p] == '*' || str[p] == '/' || str[p] == '%' || str[p] == '^')
				{
					count++;
				}
				else if (str[p] >= '0'&&str[p] <= '9')
				{
					count = 0;
				}
				else if (str[p] != '.'&&str[p] != '('&&str[p] != ')') //是否有不能运算的特殊符号
				{
					cout << "ERROR IN INFIX NOTATION"<<endl;
					flag = 0;
					break;
				}

				if (str[p] == '(')//对于4+(-2)这种情况，不是连续两个运算符连着
				{
					if (str[p + 1] == '-')
					{
						count--;
					}
				}
				if (count == 2)
				{
					cout << "ERROR IN INFIX NOTATION"<<endl;
					flag = 0;
				}
			}
		}
		//检查第一个是否为数字或者括号
		if (flag != 0)
		{
			if (str[0] != '('&&str[0] != '+'&&str[0] != '-')
			{
				if (str[0]<'0' || str[0]>'9')
				{
					cout << "ERROR IN INFIX NOTATION" << endl;
					flag = 0;
				}
			}
		}
		//检查是否存在运算符可以运算  特殊情况 (-2)3
		if (flag != 0) {
			int flagdo = 0;
			for (int r = 0; r < length; r++)
			{
				if (str[r] == '*' || str[r] == '/' || str[r] == '%' || str[r] == '^')
				{
					flagdo = 1;//可以运算
					break;
				}
				else if (str[r] == '+' || str[r] == '-')
				{
					if (r != 0)
					{
						if (str[r - 1] == '(')//为了保证r不等于0 出现	先检测str[0]不能为符号的情况（检查第一个是否为数字或者括号）移到这个错误检测之前			
						{
							flagdo = 0;
						}
						else {
							flagdo = 1;//可以运算
							break;
						}
					}
					else
					{
						flagdo = 1;//可以运算
						break;
					}

				}
			}
			if (flagdo == 0)
			{
				cout << "ERROR IN INFIX NOTATION" << endl;
				flag = 0;
			}
		}

		//检查输入末尾是否为数字
		if (flag != 0)
		{
			if (str[length - 1]<'0' || str[length - 1]>'9')
			{
				if (str[length - 1] != ')')
				{
					cout << "ERROR IN INFIX NOTATION" << endl;
					flag = 0;
				}
			}
		}

		if (flag != 0)
		{
			//字符串第一位为+ or - 则先压入一个0  例子 -2+4

			if (str[0] == '+' || str[0] == '-')
			{
				back.push('0');
				back.push('@');
			}
		
			//中缀表达式转后缀表达式，用back队列存放，每两个数字之间用@分割，）不进入存放
			for (i = 0; i < length; i++)
			{

				if (str[i] >= '0'&&str[i] <= '9')
				{
					back.push(str[i]);
					if (i == length - 1)
					{
						back.push('@');
					}
				}
				else if (str[i] == '.')
				{
					back.push('.');
				}
				else if (str[i] == '(')
				{
					if (i != 0)
					{
						if (str[i - 1] >= '0'&&str[i - 1] <= '9')
						{
							back.push('@');
						}
					}
					fuhao.push(str[i]);
					if (str[i + 1] == '-')
					{
						back.push('0');
						back.push('@');
					}
				}
				else if (str[i] == ')')
				{
					if (i != 0)
					{
						if (str[i - 1] >= '0'&&str[i - 1] <= '9')
						{
							back.push('@');
						}

					}
					while (fuhao.top() != '(')
					{
						char x = fuhao.top();
						back.push(x);
						fuhao.pop();
					}
					fuhao.pop();//把‘(’删掉
				}
				else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '%' || str[i] == '^')
				{
					if (i != 0)
					{
						if (str[i - 1] >= '0'&&str[i - 1] <= '9')
						{
							back.push('@');
						}
					}
					if (fuhao.top() == '#' || judge(fuhao.top(), str[i]) == 1)
					{
						fuhao.push(str[i]);
					}
					else if (judge(fuhao.top(), str[i]) == -1)
					{

						do
						{
							char c = fuhao.top();
							fuhao.pop();
							back.push(c);
						}while (judge(fuhao.top(), str[i]) != 1);//一直弹出到大于
						fuhao.push(str[i]);
					}
				}
				else
				{
					cout << "ERROR IN INFIX NOTATION"<<endl;
					break;
				}
			}
			while (fuhao.top() != '#')
			{
				char c = fuhao.top();
				fuhao.pop();
				back.push(c);
			}

			//输出存放的后缀表达式
				/*while (!back.empty())
				{
					cout << back.front()<<" ";
					back.pop();
				}
				cout << endl;*/

				//计算存放在back队列里的后缀表达式 如果是数字则进栈，如果遇到运算符，则出栈两个数字，进行运算后，将运算结果进栈
			stack<double>num;
			double res = 0.0, xiaoshu = 0.0, ten = 1.0;
			double d;
			int count2 = 0;//小数的位数 看乘以0.1 还是0.01……
			while (!back.empty())
			{
				char k;
				if (back.front() >= '0'&&back.front() <= '9')
				{
					while (back.front() != '@')
					{
						char f = back.front();
						back.pop();
						res = res * 10.0 + (f - '0');
						if (back.front() == '.')
						{
							back.pop();//把‘.’删除
							while (back.front() != '@')
							{
								count2++;
								for (int e = 0; e < count2; e++)
								{
									ten = 0.1 * ten;
								}
								char q = back.front();
								back.pop();
								xiaoshu = xiaoshu + (q - '0')*ten;
								ten = 1.0;
							}
						}
					}
					if (back.front() == '@')
					{
						back.pop();
					}
					//cout << res << endl;
					//cout << res + xiaoshu << endl;
					num.push(res + xiaoshu);
					//cout << num.top() << endl;
					res = 0.0;
					count2 = 0;
					xiaoshu = 0.0;
				}
				else if (back.front() == '+' || back.front() == '-' || back.front() == '*' || back.front() == '/' || back.front() == '%' || back.front() == '^')
				{
					double a1 = num.top();
					num.pop();
					double a2 = num.top();
					num.pop();
					d = run(back.front(), a2, a1);
					//cout << d<<endl;
					back.pop();//把这个运算符号删除
					num.push(d);
				}
				else if (back.front() == '(')
				{
					back.pop();
				}
			}
			cout << fixed << setprecision(2) << num.top() << endl;
		}
	}
	system("pause");
	return 0;
}


//int main()
//{
//	string a="23";
//	cout << a + "5";
//	system("pause");
//	return 0;
//}







//int main()
//{
//	stack <double>num;//存放数字
//	stack<char>fuhao;//存放符号
//	char *op = "+-*/%^()#";
//	string str;
//	double result;
//	cin>>str;
//	str.append(1, '#');//string append()用法：str.append(str2,11,7)从第11个字符开始，添加7个/str.append(str2)/str.append(5,'.')添加5个.
//	fuhao.push('#');//先将#入栈
//	int a = -1;
//	for (;;)
//	{
//		int b = a + 1;
//		a = str.find_first_of(op, a + 1);//从a+1开始查找str中的第一个与op中某个字符符合的字符，并返回它的位置，没找到就返回string::npos
//		if (a == string::npos)break;
//		if (a != b)
//		{
//			string ss(str, b, a - b);
//			double d = atof(ss.c_str());//将两个操作符之间的数字转换成浮点数（之前为string类型）
//			num.push(d);//存入数字的栈里
//		}
//
//		int f1= judge(fuhao.top(), str[a]);
//		if (f1 == 1)
//		{
//			double f2 = num.top();
//			num.pop();
//			double f3 = num.top();
//			num.pop();
//			double f4 = run(fuhao.top(), f2, f3);
//			num.push(f4);
//			a--;
//		}
//		if (f1 == -1)
//		{
//			fuhao.push(str[a]);
//		}
//		
//		str.erase(str.length() - 1, 1);
//		cout << str << "=" << num.top() << endl;
//	}
//	system("pause");
//	return 0;
//}





