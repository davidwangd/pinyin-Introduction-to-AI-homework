#ifndef WORDS_H
#define WORDS_H
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

enum Type{
	e_Char = 0,
	e_Py = 1,
	e_Total = 2
}

class merge;

static const int MaxLength = 4;
// save the data of length with type of char of py.
template <int length, Type type>
class singleBlock{
public:

	friend class merge;
	// set the data of list
	void set(int *list){
		for (int i = 0;i < length;i++) block[i] = list[i];
	}

	// for map usage
	int operator<(const singleBlock<length, type> &x) const{
		for (int i = 0;i < length;i++){
			if (block[i] != x.block[i]) return block[i] < x.block[i];
		}
	}

	// for map usage
	int operator==(const singleBlock<length, type> &x) const{
		for (int i = 0;i < length;i++)
			if (block[i] != x.block[i]) return 0;
		return 1;
	}

	int getPossiModel() const {
		return possiModel;
	}
private:
	// save the data
	int block[length];

	static const int possiModel;
};

template <int length, Type type>
const int singleBlock<length, type>::possiModel = length * e_Total + type;

template <int length, Type type>
// inheritage set, opeartor< and operaotr==
class relatedBlock : public singleBlock<length, type>{

	friend class merge;
	int getPossiModel() const {
		return possiModel;
	}

	// insert a possible corresponding relation between this type and opposite one.
	void insert(int *list){
		for (int i = 0;i < related.size();i++){
			int flag = 1;
			for (int j = 0;j < length;j++){
				if (list[j] != related[i][j]){
					flag = 0;
					break;
				} 
			}
			if (flag) return;
		}
		int *curr = new int[length];
		
		for (int i = 0;i < length;i++)
			curr[i] = list[i];

		related.push_back(const_cast<const int *>curr);
	}
private:
	static const int possiModel;
	vector<const int[length]> related;
};

template <int length, Type type>
const int relatedBlock<length, type>::possiModel = maxLenght * e_Total + length * e_Total + type;

// this class operates merge for these two kinds
class merge{
	template<int l1, int l2, Type type>
	singleBlock<l1 + l2, type> operator()(const singleBlock<l1, type> &A, const singleBlock<l2, type> &B){
		// TODO
	}

	relatedBlock<l1 + l2, type> oeprator()(const relatedBlock<l1, type> &A, const relatedBlock<l2, type> &B){
		// TODO
	}
};

#endif // ! WORDS_H
