#ifndef DICT_H
#define DICT_H
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <string>
#include <map>
#include <vector>

using namespace std;
namespace Dict{
	const int MaxPY = 500;
	const int MaxChar = 10000;

	int countPy = 0, countChar = 0;
	// transform pinyin to integer 
	map<string, int> py2int; 

	// transform integer to corresponding pinyin string
	string int2py[MaxPY];

	// transform integer to character 
	map<string, int> char2int;

	// transform integer to corresponding character
	string int2char[MaxChar];

	// character of corresponding pinyins'
	vector<int> char2py[MaxChar];

	// pinyin of corresponding characters'
	vector<int> py2char[MaxPY];

	void loadDict(){
		// dictionary file
		FILE *dict = fopen("dict.txt", "r");

		//sample file, this program will and only will process character in sample file
		FILE *sample = fopen("sample.txt", "r");
		FILE *LOG = fopen("log.txt", "w");
		// two char 1 character in chinese
		static char buffer[MaxChar * 2];
		// load from sample all available characters that will process.
		fscanf(sample, "%s", buffer);
		for (int i = 0;buffer[i];i += 2){
			char tmp = buffer[i + 2];
			buffer[i + 2] = 0;
			int2char[countChar] = string(buffer + i);
			char2int[string(buffer + i)] = countChar;

			countChar ++;
			buffer[i + 2] = tmp;
		}

		printf("load complete!\n");
		//load from dict 

		fscanf(dict, "%s", buffer);
		string py = string(buffer);
		for (int i = 0;i < 406;i++){
			int2py[i] = py;
			py2int[py] = i;

			char c = 0;
			c = fgetc(dict);
			// process characters
			fprintf(LOG, "%s:\n", py.c_str());
			while (c == ' '){
				if (fscanf(dict, "%s", buffer) == EOF) break;
				if (buffer[0] > 0){
					py = string(buffer);
					break;
				}
				string C = string(buffer);
				// in sample
				fprintf(LOG, "%s\n", C.c_str());
				if (char2int.find(C) != char2int.end()){
					int id = char2int[C];
					py2char[i].push_back(id);
					char2py[id].push_back(i);
				}
			}
			countPy++;
		}
		printf("load complete!\n");
	}
}

#endif // ! DICT_H