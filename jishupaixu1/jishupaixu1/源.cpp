#include<iostream>
using namespace std;
int findmax(int a[],int num)//找出最大元素
{
	int max;
	max = a[0];
	for (int i = 0; i < num; i++)
	{
		if (a[i] > max)
			max = a[i];
	}
	return max;
}
int findlength(int x)//找出元素的位数
{
	int len=1;
	while (x >= 10)
	{
		x /= 10;
		len++;
	}
	return len;
}
void sort(int a[],int len,int num)//len为最大数的位数，num为数组元素个数
{
	int bucket[10][100] = {0};//按照个位存放在桶子里
	int num10=1;
	for (int h = 1; h < len; h++)//10的len次方
	{
		num10 = num10 * 10;
	}
	//cout << len << endl;
	//cout << num10<<endl;
	for (int l = 1; l <= num10; l *= 10)//根据最大数位数刷新桶子顺序
	{
			for (int k = 0; k < 10; k++)//桶子列数指引
			{
				int g = 0;//二维数组每一层的指引
				for (int j = 0; j < num; j++)//原数组指引
				{
					if (((a[j] / l)%10) == k)
					{
						bucket[k][g] = a[j];
						//cout << bucket[k][g] << " ";
						g++;
					}
				}
				//cout << endl;
			}
		
		for (int j = 0, i = 0; j < 10; j++)//集合 刷新原数组，j为bucket横坐标，m为纵坐标
		{
			for (int m=0; m < 100; m++)
			{
				
				if (bucket[j][m] != 0)
				{
					//cout << bucket[j][m]<<" ";
					a[i] = bucket[j][m];
					bucket[j][m] = 0;//再次置空
					i++;
				}
			}
			//cout << endl;
		}
		for (int h = 0; h < num; h++)
		{
			cout << a[h] << " ";
		}
		cout << endl;
	}
}
int main()
{
	int n,max,len;
	cin >> n;
	int a[100];
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	max = findmax(a, n);
	len=findlength(max);
	sort(a, len, n);
	/*for (int h = 0; h < n; h++)
	{
		cout << a[h]<<" ";
	}*/
	system("pause");
	return 0;
}
