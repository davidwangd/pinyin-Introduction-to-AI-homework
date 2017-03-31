all: pinyin
pinyin: pinyin.cpp filter.cpp dictionary.h possibility.h words.h
	g++ -g -o2 -std=c++11 pinyin.cpp -o pinyin 
