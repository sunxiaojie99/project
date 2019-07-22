/*
描述:
你来到一个陌生的外国城市，那里的人们说着一种让人费解的外国语言，不过幸运的是，
你有一本词典可以帮助你来理解这些语言。请利用散列表来把外国语言翻译成英文。
要求：

用hash函数来建立字典，解决地址冲突。
输入：
首先输入一个词典，其中包含不超过1000个词条，每个词条占据一行。每一个词条包括一个英文单词和一个外语单词，
两个单词之间用一个空格隔开。而且在词典中不会有某个外语单词出现两次以上的情况。
之后是一个空行。下一行输入待查询的一个外语单词。输入中出现的单词只包括小写字母，而且长度不会超过10。
输出：
你需要把输入的待查询单词翻译成英文单词。如果某个外语单词不在词典中，就把这个单词翻译成 “eh”。
输入：
dog ogday
cat atcay
pig igpay
froot ottfray
loops oopsla

atcay
输出：
cat
*/

#include<iostream>
#include<string>

using namespace std;
class hashtable
{
public:
	int m,count1=0;
	string *eng;//存放正确的英文
	string *other;//存放外文
	bool *empty;
	hashtable(int n) {//将字典长度传入
		eng = new string[100];
		other = new string[100];
		empty = new bool[100];
		m = n;
		for (int g = 0; g<100; g++)
		{
			empty[g] = true;
		}
	}
	void search(string check)
	{
		int i = 0, sum = 0, loc;
		for (i = 0; i<3; i++)//哈希函数：将输入的字符串前3位的ASCII码-‘a’的相加 对字典长度取余  结果即为存储位置
		{
			if (check[i] == '\0')
			{
				break;
			}
			sum = sum + (check[i] - 'a');
		}
		loc = sum%m;
		if (!empty[loc])//如果哈希的位置不为空，在对应的other找是否为要查找的外文，如果不是，查找下一个位置
		{
			while (1) {
				if (other[loc]==check)//string str1; string str2; str1.compare(str); str1>str2返回整数,相等返回0 小于返回负数
				{
					int x = 0;
					while (eng[loc][x] != '\0')
					{
						cout << eng[loc][x];
						x++;
					}
					if (eng[loc][x] == '\0')
						break;
				}
				else
				{
					loc++;
					count1++;
				}
				if (count1 >= m)
				{
					cout << "eh";
					break;
				}
			}
		}
		else if (empty[loc])
		{
			cout << "eh";
		}
	}
};
int main()
{
	string a[100], b[100];
	string c;
	int i = 0, count;
	while (1)
	{
		getline(cin, c);
		if (c == "\0")
		{
			break;
		}
		for (int j = 0; j<c.length(); j++)
		{
			if (c[j] == ' ')
			{
				a[i] = c.substr(0, j);
				b[i] = c.substr(j + 1, c.length() - j);
				i++;
				break;
			}
		}
	}
	count = i;
	hashtable hh(count);
	int sum = 0, loc;
	for (int p = 0; p<count; p++)
	{
		sum = 0;
		for (int y = 0; y<3; y++)
		{
			if (b[p][y] == '\0')
			{
				break;
			}
			sum = sum + (b[p][y] - 'a');
			//cout << b[p][y] - 'a'<<" "<<sum<<endl;
		}
		loc = sum % count;
		//cout <<sum <<" "<<loc << endl;
		while (1)
		{
			if (hh.empty[loc])//如果哈希位置为空 改为不空 在相应的other和eng中插入相应字符串
			{
				hh.empty[loc] = false;
				hh.other[loc] = b[p];
				hh.eng[loc] = a[p];
				break;
			}
			else//如果位置不为空，判断是否和需要插入的外文一样，不一样，就在下一个位置寻找
			{
				if (hh.other[loc] == b[p])
				{
					break;
				}
				else
				{
					loc++;
				}
			}

		}
	}
	//int r = 0;
	//while (r<=count)
	//{
	//	cout << hh.eng[r] <<" "<< hh.other[r] << endl;
	//	r++;
	//}

	string check;
	cin >> check;
	hh.search(check);
	system("pause");
	return 0;
}