#include <cstdio>
#include <cstring>
#include <iostream>
#include "filter.h"
#include <fstream>
using namespace std;

PossiModel<singleBlock<1, e_Py>::possiModel> PsPy1;
PossiModel<singleBlock<2, e_Py>::possiModel> PsPy2;

PossiModel<singleBlock<1, e_Char>::possiModel> PsCh1;
PossiModel<singleBlock<2, e_Char>::possiModel> PsCh2;

PossiModel<relatedBlock<1>::possiModel> PsRe1;
PossiModel<relatedBlock<2>::possiModel> PsRe2;

singleBlock<1, e_Char> Ch1;
singleBlock<2, e_Char> Ch2;

relatedBlock<1> Re1;
relatedBlock<2> Re2;

singleBlock<1, e_Py> Py1;
singleBlock<2, e_Py> Py2;

const int MaxLen = 30;
int py[MaxLen];
string ch[MaxLen];
const int ThisMaxChar = 7000;
double dp[MaxLen][ThisMaxChar];
int pre[MaxLen][ThisMaxChar];

int state[5]; 
int state2[5];

Filter filter;

void readLearnedOjb(const char *filename);
int getPys(const string &s){
	int Count = 0, previous = -1;
	for (int i = 0;i < s.length();i++){
		if (s[i]<'a' || s[i]>'z'){
			if (i == previous + 1) continue;
			auto it = py2int.find(s.substr(previous + 1, i - previous - 1));
			if (it == py2int.end()){
				fprintf(stderr, "Pinyin %s unrecognized, ignored!\n", s.substr(previous + 1, i - previous - 1).c_str());
			}else{
				py[Count++] = it->second;
			}
			previous = i;
		}
	}
	return Count;
}

void getDp(int N){
	int state[3];
	for (int i = 0;i < N;i++)
		for (int j = 0;j < ThisMaxChar;j++)
			dp[i][j] = -1;
	double lam = 0.3;
	double lam2 = 0.7;
	for (int x:py2char[py[0]]){
		state[0] = x;
		Ch1.set(state);
		Py1.set(py);
		dp[0][x] = lam * (filter.getPossi(Ch1));
	}
//	printf("%d\n", N);
	for (int i = 0;i < N - 1;i++){
		Py1.set(py + i + 1);
		Py2.set(py + i);
//		cout << Py1 << " X2: " << Py2 << endl;
		for (int j:py2char[py[i]]){
			if (dp[i][j] <= 0 || dp[i][j] >= 10000) continue;
//			printf("dp[%s][%s] : %.6lf\n", int2py[py[i]].c_str(),int2char[j].c_str(),dp[i][j]);
			for (int k:py2char[py[i+1]]){
				state[0] = j;
				state[1] = k;
				Ch1.set(state);
				Ch2.set(state);

				double currPossi = (filter.getPossi(Ch2))-(filter.getPossi(Ch1));

				Ch1.set(state + 1);
//				cout << Ch1 << " Possi: " << filter.getPossi(Ch1) << endl;
//				cout << Ch2 << " Possi: " << filter.getPossi(Ch2) << endl;
				currPossi = lam2 * currPossi + lam * filter.getPossi(Ch1);
				if (currPossi < 0 || currPossi >= 10000) continue;
//				printf("\t->%s %lf\n",int2char[k].c_str(), currPossi);
				if (dp[i][j] + currPossi < dp[i+1][k] || dp[i+1][k] < 0){
					dp[i+1][k] = dp[i][j] + currPossi;
					pre[i+1][k] = j;
				}
			}
		}
	}
}

void getCh(int Count){
	double curMin = 1e100;
	int curPos = -1;
	for (int i = 0;i < ThisMaxChar;i++){
		if (dp[Count - 1][i] > 0 && dp[Count - 1][i] < curMin){
			curMin = dp[Count - 1][i];
			curPos = i;
		}
	}
	
	for (int i = Count - 1;i >= 0;i--){
		ch[i] = int2char[curPos];
		curPos = pre[i][curPos];
	}
	return;
}

int main(int argc, char *argv[]){
	loadDict();
	fprintf(stderr, "start To Read learned Object!\n");
	readLearnedOjb("obj.txt");
	fprintf(stderr, "End Read Learned Object!\n");
	if (argc == 2){
		freopen(argv[1], "r", stdin);
	}else{
		fprintf(stderr, " No file inputed! currently Use input.txt as read");
		freopen("input.txt", "r", stdin);
	}

	freopen("output.txt", "w", stdout);
	
//	filter.Py1 -> show(//cout);
//	filter.Py2 -> show(//cout);
//	filter.Char1 -> show(//cout);
//	filter.Char2 -> show(//cout);

	string str;
	while (getline(cin, str)){
		fprintf(stderr, "%s\n", str.c_str());
		str = str + " ";
		int Count = getPys(str);
		getDp(Count);
		getCh(Count);
		for (int i = 0;i < Count;i++){
			cout << ch[i];
		}
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
		//cout << ch << py << endl;
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
	int cnt;
	while (fin >> st){
		cnt++;
		int num = st.length() / 2;
		for (int i = 0;i < st.length();i += 2){
			state[i/2] = char2int[st.substr(i, 2)];
		}
		if (cnt % 1000 == 0){
//			printf("read %d obj!\n", cnt);
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
	}
}
