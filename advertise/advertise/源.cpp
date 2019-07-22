#include<iostream>
#include<vector>
using namespace std;
class Item
{
public:
	int Wi = 0;
	double Vi = 0;
	bool selected = false;
};
vector<Item> vecItem;
double dp[200][5001];
double getMaxValue(int itemSize, int maxWeight);
void findSelectedItems(int itemSize, int maxWeight);
double max(double a, double b) {
	if (a > b)
		return a;
	return b;
}
int main() {
	int n, maxW;
	cin >> n >> maxW;
	for (size_t i = 0; i < n; i++) {
		Item item;
		cin >> item.Wi >> item.Vi;
		if (item.Wi <= maxW)
			vecItem.push_back(item);
	}
	double maxValue = getMaxValue(vecItem.size(), maxW);
	findSelectedItems(vecItem.size(), maxW);
	cout << "max value :" << maxValue << endl << "selected items :" << endl;
	for (size_t i = 0; i < vecItem.size(); ++i)
	{
		if (vecItem[i].selected)
			cout << "index " << i << " : " << vecItem[i].Wi << " - " << vecItem[i].Vi << endl;
	}
	system("pause");
	return 0;
}

double getMaxValue(int itemSize, int maxWeight) {
	for (int j = 1; j <= maxWeight; ++j) {
		if (vecItem[itemSize - 1].Wi <= j)
			dp[itemSize - 1][j] = vecItem[itemSize - 1].Vi;
		for (int i = itemSize - 2; i >= 0; --i) {
			if (j < vecItem[i].Wi) {
				dp[i][j] = dp[i + 1][j];
			}
			else
				dp[i][j] = max(dp[i + 1][j], dp[i + 1][j - vecItem[i].Wi] + vecItem[i].Vi);
		}
	}
	return dp[0][maxWeight];
}

void findSelectedItems(int itemSize, int maxWeight) {
	int k = maxWeight;
	for (int i = 0; i < itemSize;i++) {
		if (dp[i][k] > dp[i + 1][k]) {
			vecItem[i].selected = true;
			k -= vecItem[i].Wi;
		}
	}
}