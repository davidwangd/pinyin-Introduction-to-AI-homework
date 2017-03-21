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
};

class singleMerge;
class relatedMerge;

static const int MaxLength = 4;
// save the data of length with type of char of py.
template <int length, Type type>
class singleBlock{
public:

	friend class singleMerge;

	singleBlock() = default;
	virtual ~singleBlock() = default;
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
	static const int possiModel;
private:
	// save the data
	int block[length];

};

template <int length, Type type>
const int singleBlock<length, type>::possiModel = length * e_Total + type;

//certian length of PY relected to certain characters.
template <int length>
class relatedBlock{
	friend class relatedMerge;
public:
	
	relatedBlock() = default;

	// Construct a related block according to single PY block and single Character block
	relatedBlock(const singleBlock<length, e_Py> &A, const singleBlock<length, e_Char> &B){
		for (int i = 0;i < length;i++){
			block[i]   = A.block[i];
			related[i] = B.block[i];
		}
	}	
	friend class merge;
	int getPossiModel() const {
		return possiModel;
	}
	static const int possiModel;
private:
	int block[length];
	int related[length];
};

template <int length>
const int relatedBlock<length>::possiModel = MaxLength * e_Total + length;

// this class operates merge for these two kinds
class singleMerge{
	template<int l1, int l2, Type type>
	singleBlock<l1 + l2, type> operator()(const singleBlock<l1, type> &A, const singleBlock<l2, type> &B){
		singleBlock<l1 + l2, type> ret;
		for (int i = 0;i < l1;i++)
			ret.block[i] = A.block[i];
		for (int i = 0;i < l2;i++)
			ret.block[i + l1] = B.block[i];
		return ret;
	}
};

class relatedMerge{
	template<int l1, int l2>
	relatedBlock<l1 + l2> operator()(const relatedBlock<l1> &A, const relatedBlock<l2> &B){
		relatedBlock<l1 + l2> ret;
		for (int i = 0;i < l1;i++){
			ret.block[i] = A.block[i];
			ret.related[i] = A.related[i];
		}

		for (int i = 0;i < l2;i++){
			ret.block[i + l1] = B.block[i];
			ret.related[i + l1] = B.related[i];
		}
		
		return ret;
	}
};

#endif // ! WORDS_H
