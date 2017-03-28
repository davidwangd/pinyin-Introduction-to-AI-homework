#include <cstdio>
#include <cstring>
#include <iostream>
#include "filter.h"
#include <fstream>
using namespace std;

PossiModel<singleBlock<1, e_Py>::possiModel> PsPy1;
PossiModel<singleBlock<2, e_Py>::possiModel> PsPy2;
PossiModel<singleBlock<3, e_Py>::possiModel> PsPy3;
PossiModel<singleBlock<4, e_Py>::possiModel> PsPy4;

PossiModel<singleBlock<1, e_Char>::possiModel> PsCh1;
PossiModel<singleBlock<2, e_Char>::possiModel> PsCh2;
PossiModel<singleBlock<3, e_Char>::possiModel> PsCh3;
PossiModel<singleBlock<4, e_Char>::possiModel> PsCh4;

PossiModel<relatedBlock<1>::possiModel> PsRe1;
PossiModel<relatedBlock<2>::possiModel> PsRe2;
PossiModel<relatedBlock<3>::possiModel> PsRe3;
PossiModel<relatedBlock<4>::possiModel> PsRe4;

singleBlock<1, e_Char> Ch1;
singleBlock<2, e_Char> Ch2;
singleBlock<3, e_Char> Ch3;
singleBlock<4, e_Char> Ch4;

relatedBlock<1> Re1;
relatedBlock<2> Re2;
relatedBlock<3> Re3;
relatedBlock<4> Re4;

singleBlock<1, e_Py> Py1;
singleBlock<2, e_Py> Py2;
singleBlock<3, e_Py> Py3;
singleBlock<4, e_Py> Py4;

string py[20], ch[20];
double dp[20];
int pre[20];

int state[5]; 
int state2[5];

Filter filter;

void readLearnedOjb(const char *filename);
int readLinedPy();
int dpGetSplit();
string getChString(string start[], int size);

int main(int argc, char *argv[]){
	loadDict();
	freopen("mp.txt", "w", stdout);
	readLearnedOjb("learn-obj.txt");

	filter.Re1 -> show(cout);
	filter.Re2 -> show(cout);
	filter.Re3 -> show(cout);
	filter.Re4 -> show(cout);

	return 0;

	while (1){
		int len = readLinedPy();
		int tot = dpGetSplit();
		for (int i = tot - 1, cur = len; i >= 0;i--, cur = pre[cur]){
			ch[i] = getChString(py + pre[cur] + 1, cur - pre[cur]);
		}
		for (int i = 0;i < tot;i++)
			cout << ch[i];
		cout << endl;
	}
}

template <int len>
void dfsPush(int cur){
	if (cur == len + 1){
		singleBlock<len, e_Py> py;
		singleBlock<len, e_Char> ch;
		ch.set(state);
		py.set(state2);
		cout << ch << py << endl;
		relatedBlock<len> re(py, ch);
		if (len == 1){
			filter.Char1 -> mp[ch] = PsCh1;
			filter.Re1 -> mp[re] = PsRe1;
			filter.Py1 -> addCount(py, PsPy1);
		}
		if (len == 2){
			filter.Char2 -> mp[ch] = PsCh2;
			filter.Re2 -> mp[re] = PsRe2;
			filter.Py2 -> addCount(py, PsPy2);
		}
		if (len == 3){
			filter.Char3 -> mp[ch] = PsCh3;
			filter.Re3 -> mp[re] = PsRe3;
			filter.Py3 -> addCount(py, PsPy3);
		}
		if (len == 4){
			filter.Char4 -> mp[ch] = PsCh4;
			filter.Re4 -> mp[re] = PsRe4;
			filter.Py4 -> addCount(py, PsPy4);
		}
		return;
	}
	for (int i = 0;i < char2py[state[cur - 1]].size();i++){
		state2[cur - 1] = char2py[state[cur - 1]][i];
		dfsPush<len>(cur + 1);
	}
}

void readLearnedOjb(const char *filename){
	ifstream fin(filename);
	char c;
	string st;
	int Count, Total;
	while (fin >> st){
		int num = st.length() / 2;
		for (int i = 0;i < st.length();i += 2){
			state[i/2] = char2int[st.substr(i, 2)];
		}
		fin >> c >> Count >> c >> Total;
		fin >> st;
		if (num == 1){
			PsCh1.setTotal(Total);
			PsCh1.setCount(Count);
			PsPy1.setTotal(Total);
			PsPy1.setCount(Count);
			PsRe1.setTotal(Total);
			PsRe1.setCount(Count);
			dfsPush<1>(1);
		}
		if (num == 2){
			PsCh2.setTotal(Total);
			PsCh2.setCount(Count);
			PsPy2.setTotal(Total);
			PsPy2.setCount(Count);
			PsRe2.setTotal(Total);
			PsRe2.setCount(Count);
			dfsPush<2>(1);
		}
		if (num == 3){
			PsCh3.setTotal(Total);
			PsCh3.setCount(Count);
			PsPy3.setTotal(Total);
			PsPy3.setCount(Count);
			PsRe3.setTotal(Total);
			PsRe3.setCount(Count);
			dfsPush<3>(1);
		}
		if (num == 4){
			PsCh4.setTotal(Total);
			PsCh4.setCount(Count);
			PsPy4.setTotal(Total);
			PsPy4.setCount(Count);
			PsRe4.setTotal(Total);
			PsRe4.setCount(Count);
			dfsPush<4>(1);
		}
	}
}

int readLinedPy(){}
int dpGetSplit(){}
string getChString(string start[], int size){}