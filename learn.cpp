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
singleBlock<3, e_Char> ch3;
singleBlock<4, e_Char> ch4;

int state[5];
int state2[5];

singleBlock<1, e_Py> py1;
singleBlock<2, e_Py> py2;
singleBlock<3, e_Py> py3;
singleBlock<4, e_Py> py4;

relatedBlock<1> re1;
relatedBlock<2> re2;
relatedBlock<3> re3;
relatedBlock<4> re4;
	
Filter filter;

int maxSize = 0;
int cur = 0;

void dfs(int x){
	auto &pyList = char2py[state[x]];
	for (vector<int>::iterator it = pyList.begin();it != pyList.end();it++){
		state2[x] = *it;
		if (x == maxSize - 1){ 
			py1.set(state2 + maxSize - 1); 
			filter.Add(py1);
			re1 = relatedBlock<1>(py1, ch1);
			filter.Add(re1);
			if (x) dfs(x - 1); 
		}
		
		if (x == maxSize - 2){
			py2.set(state2 + maxSize - 2); 
			filter.Add(py2);
			re2 = relatedBlock<2>(py2, ch2);
			filter.Add(re2); 
			if (x) dfs(x - 1);
		}
		
		if (x == maxSize - 3){
			py3.set(state2 + maxSize - 3); 
			filter.Add(py3);
			re3 = relatedBlock<3>(py3, ch3);
			filter.Add(re3); 
			if (x) dfs(x - 1);
		}

		if (x == maxSize - 4){
			py3.set(state2 + maxSize - 3); 
			filter.Add(py3);
			re3 = relatedBlock<3>(py3, ch3);
			filter.Add(re3); 
			if (x) dfs(x - 1);
		}


	}
}

void push(){
	if (maxSize >= 4){ ch4.set(state); filter.Add(ch4); }
	if (maxSize >= 3){ ch3.set(state + maxSize - 3); filter.Add(ch3); }
	if (maxSize >= 2){ ch2.set(state + maxSize - 2); filter.Add(ch2); }
 	if (maxSize >= 1){ ch1.set(state + maxSize - 1); filter.Add(ch1); }
	cur = 0;
	dfs(maxSize - 1);
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
		if (maxSize == 4){
			for (int i = 0;i <= 2;i++) state[i] = state[i + 1];
		}else{
			maxSize++;
		}
		state[maxSize - 1] = pos -> second;
		push();
	}
}

template <int type>
int filterFunc(const PossiModel<type> &x){
	int threshold;
	if (type == singleBlock<1, e_Char>::possiModel || singleBlock<1, e_Py>::possiModel || relatedBlock<1>::possiModel) threshold = 2;
	if (type == singleBlock<2, e_Char>::possiModel || singleBlock<2, e_Py>::possiModel || relatedBlock<2>::possiModel) threshold = 6;
	if (type == singleBlock<3, e_Char>::possiModel || singleBlock<3, e_Py>::possiModel || relatedBlock<3>::possiModel) threshold = 4;
	if (type == singleBlock<4, e_Char>::possiModel || singleBlock<4, e_Py>::possiModel || relatedBlock<4>::possiModel) threshold = 2;
	return x.getCount() < threshold;
}

void filterless(){
	filter.removeAllIf(filterFunc<singleBlock<1, e_Py>::possiModel>);
	filter.removeAllIf(filterFunc<singleBlock<2, e_Py>::possiModel>);
	filter.removeAllIf(filterFunc<singleBlock<3, e_Py>::possiModel>);
	filter.removeAllIf(filterFunc<singleBlock<4, e_Py>::possiModel>);

	filter.removeAllIf(filterFunc<singleBlock<1, e_Char>::possiModel>);
	filter.removeAllIf(filterFunc<singleBlock<2, e_Char>::possiModel>);
	filter.removeAllIf(filterFunc<singleBlock<3, e_Char>::possiModel>);
	filter.removeAllIf(filterFunc<singleBlock<4, e_Char>::possiModel>);

	filter.removeAllIf(filterFunc<relatedBlock<1>::possiModel>);
	filter.removeAllIf(filterFunc<relatedBlock<2>::possiModel>);
	filter.removeAllIf(filterFunc<relatedBlock<3>::possiModel>);
	filter.removeAllIf(filterFunc<relatedBlock<4>::possiModel>);
}

void learn(const char *file){
	ifstream fin(file);
	string str, data;
	int count;
	for (int i = 1;i <= 50;i++){
		getline(fin, str);
		Json::Reader reader;
		Json::Value input;

		reader.parse(str, input);
		data = input["html"].asString();
	}
}

int main(){
	learn("sina_news_gbk/2016-01.txt");
	filter.Char2 -> show(cout);
	filter.Char3 -> show(cout);
	filter.Char4 -> show(cout);
}