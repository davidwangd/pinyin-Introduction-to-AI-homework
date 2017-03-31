#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "jsoncpp/json.h"
using namespace std;

// all namespace using..
#include "filter.h"
using namespace Dict;
using namespace Possi;

singleBlock<1, e_Char> ch1;
singleBlock<2, e_Char> ch2;

int state[4];

Filter filter;

int maxSize = 0;
int cur = 0;

void push(){
	if (maxSize >= 2){ ch2.set(state + maxSize - 2); filter.Add(ch2); }
 	if (maxSize >= 1){ ch1.set(state + maxSize - 1); filter.Add(ch1); }
//	cur = 0;
//	dfs(maxSize - 1);
} 

void parse(string data){
	maxSize = 0;
	memset(state, 0, sizeof(state));
	for (int i = 0;i < data.length();i += 2){
		if (data[i] > 0){
			maxSize = 0;
			i--;
			continue;
		}
		auto pos = char2int.find(data.substr(i, 2));
		if (pos == char2int.end()){
			maxSize = 0;
			continue;
		}
		if (maxSize <= 1) state[maxSize++] = pos->second;
		else state[0] = state[1], state[1] = pos->second;
		push();
	}
}

void learn(const char *file){
	ifstream fin(file);
	string str, data;
	static int count = 0;
	
	while (getline(fin, str)){
		Json::Reader reader;
		Json::Value input;

		reader.parse(str, input);
		data = input["html"].asString();
//		cerr << data << endl;
		count++;
		if (count % 100 == 0){
			printf("learned %d objects\n", count);
		}
		parse(data);
	}
}

int main(){
//	freopen("log.txt", "w", stdout);
	freopen("obj.txt", "w", stderr);
	loadDict();
	learn("sina_news_gbk/2016-01.txt");
	learn("sina_news_gbk/2016-02.txt");
	learn("sina_news_gbk/2016-03.txt");
	learn("sina_news_gbk/2016-04.txt");
	learn("sina_news_gbk/2016-05.txt");
	learn("sina_news_gbk/2016-06.txt");
	learn("sina_news_gbk/2016-07.txt");
	learn("sina_news_gbk/2016-08.txt");
	learn("sina_news_gbk/2016-09.txt");
	learn("sina_news_gbk/2016-10.txt");
	learn("sina_news_gbk/2016-11.txt");
	filter.Char1 -> show(cerr);
	filter.Char2 -> show(cerr);
}