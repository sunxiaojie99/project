/*
根据特定的分割符号，对字符串进行分割，按行输出分割后的字符串。
输入：第一行为单独一个分割符号，第二行为需要分割的字符串
输出：输出每个分割后的字符串，每个字符串占一行
示例：
输入：|
|AB|CD|
输出：AB
CD
输入：;
AB;CD
输出：AB
CD
*/
#include<iostream>
#include<sstream>
#include<stdio.h>
#include<string>
using namespace std;
int main()
{
	char c;
	c=getchar();
	string s;
	stringstream ss;
	getline(cin, s);//读取换行
	getline(cin, s);
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == c)
		{
			s[i] = ' ';
		}
	}
	ss << s;//把s cout了
	string s1;
	int flag = 0;
	while (ss >> s1)
	{ 
		if (flag != 0)
		{
			cout << endl;
		}
		cout << s1;
		flag++;
	}
	system("pause");
	return 0;
}