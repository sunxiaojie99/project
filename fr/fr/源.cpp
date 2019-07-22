#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <io.h>
#include<iostream>
#include <windows.h>

using namespace std;

struct Record
{
	string word;
	int count;
};

class WordStatic
{
public:
	map <string, string> stopword;

	bool stopinit(const char *filename);
	bool count(const char *inpath);
	static bool sortType(const Record &v1, const Record &v2)
	{
		return v1.count > v2.count;//逆序排列
	}
	void find_keyword()
	{
		sort(_words.begin(), _words.end(), sortType);
		for (int i = 0; i < 1000 && i<_words.size(); i++)
		{
			keywords.insert(make_pair(_words[i].word, _words[i].word));
		}
	}
	bool outToFile(const char *inpath, const char *outpath);

private:
	vector<Record> _words;
	map<string, string> keywords;
};

bool WordStatic::stopinit(const char *filename)//c++的string类无法作为open的参数
{
	ifstream stopfile(filename);//打开文件流
	if (!stopfile.good())//打开不正常
	{
		cout << "ifstream open file error" << endl;
		return false;
	}
	string line;
	//   WordStatic sta;
	while (getline(stopfile, line))//一次读取一行
	{
		istringstream iss(line);//获取一行
		string tmp;
		iss >> tmp;

		stopword.insert(make_pair(tmp, tmp));

	}
	stopfile.close();
	return true;
}

bool WordStatic::count(const char *inpath)//c++的string类无法作为open的参数
{
	_words.clear();
	keywords.clear();
	ifstream ifs(inpath);//打开文件流
	if (!ifs.good())//打开不正常
	{
		cout << "ifstream open file error" << endl;
		return false;
	}
	string line;
	int i;
	//   WordStatic sta;
	while (getline(ifs, line))//一次读取一行
	{
		istringstream iss(line);//获取一行
		string word;
		while (iss >> word) //每次拿到一个单词
		{
			if (stopword.find(word) != stopword.end())
				continue;
			for (i = 0; i < _words.size(); ++i)
			{
				if (word == _words[i].word)
				{
					++_words[i].count;
					break;
				}
			}
			if (i == _words.size())
			{
				Record record;
				record.word = word;
				record.count = 1;
				_words.push_back(record);
			}
		}
	}
	ifs.close();
	return true;
}

bool WordStatic::outToFile(const char *inpath, const char *outpath)//c++的string类无法作为open的参数
{
	ifstream ifs(inpath);
	ofstream ofs(outpath);

	string line;
	//   WordStatic sta;
	while (getline(ifs, line))//一次读取一行
	{
		istringstream iss(line);//获取一行
		string word;
		while (iss >> word) //每次拿到一个单词
		{
			if (keywords.find(word) != keywords.end())
				ofs << word << ' ';
		}
	}
	ifs.close();
	ofs.close();
	return true;
}

bool read_files(std::vector<string> &filepaths, std::vector<string> &filenames, const string &directory)
{
	HANDLE dir;
	WIN32_FIND_DATA file_data;

	if ((dir = FindFirstFile((directory + "/*").c_str(), &file_data)) == INVALID_HANDLE_VALUE)
		return false; /* No files found */

	do {
		const string file_name = file_data.cFileName;
		const string file_path = directory + "/" + file_name;
		const bool is_directory = (file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

		if (file_name[0] == '.')
			continue;

		if (is_directory)
			continue;

		filepaths.push_back(file_path);
		filenames.push_back(file_name);
	} while (FindNextFile(dir, &file_data));

	FindClose(dir);
	return true;
}

int main()
{
	WordStatic ws;
	ws.stopinit("D:\\python\\kmeans\\nk2019mcm\\stopwords.txt");
	for (int i = 2055; i <= 15000; i = i + 30)
	{
		if (i == 5535 || i == 9445 || i == 2395 || i == 1775 || i == 3245 || i == 4275 || i == 11705)
			continue;
		string inpath = "D:\\python\\kmeans\\nk2019mcm\\gc\\" + to_string(i) + ".txt";
		string outpath = "D:\\python\\kmeans\\nk2019mcm\\gf\\" + to_string(i) + "_count" + ".txt";
		ws.count(inpath.c_str());
		ws.find_keyword();
		ws.outToFile(inpath.c_str(), outpath.c_str());
	}
	system("pause");
	return 0;

}