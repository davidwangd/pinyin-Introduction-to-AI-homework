#include "jsoncpp/json.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;
int main(){
	ifstream fin("sina_news/2016-01.txt");
	ofstream fout("test.txt");
	string str;
	for (int i = 0;i < 3;i++){
		getline(fin, str);
		Json::Reader reader;
		Json::Value input;
		reader.parse(str, input);
		fout << input["html"].asString() << endl;
	}
}