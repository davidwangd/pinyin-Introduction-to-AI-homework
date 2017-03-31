#ifndef WORDS_H
#define WORDS_H
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include "dictionary.h"
enum Type{
	e_Char = 0,
	e_Py = 1,
	e_Total = 2
};

template <int length, Type type>
class singleBlock;

template <int length>
class relatedBlock;

static const int MaxLength = 4;
// save the data of length with type of char of py.
template <int length, Type type>
class singleBlock{
public:

	singleBlock() = default;
	
	template <int l, Type t>
	singleBlock(const singleBlock<l, t> &x){}

	int operator<(const singleBlock<length, type> &x) const{
		for (int i = 0;i < length;i++)
			if (block[i] != x.block[i]) return block[i] < x.block[i];
		return 0;
	}

	template <int l>
	singleBlock(const relatedBlock<l> &x){}
	virtual ~singleBlock() = default;
	// set the data of list
	void set(const int *list){
		for (int i = 0;i < length;i++) block[i] = list[i];
	}

	// for map usage

	// for map usage
	int operator==(const singleBlock<length, type> &x) const{
		for (int i = 0;i < length;i++)
			if (block[i] != x.block[i]) return 0;
		return 1;
	}

	int& operator[](const int &x) const {
		return block[x];
	}

	singleBlock<length - 1, type> suffix() const{
		singleBlock<length - 1, type> ret;
		ret.set(block + 1);
		return ret;
	}

	singleBlock<length - 1, type> prefix() const{
		singleBlock<length - 1, type> ret;
		ret.set(block);
		return ret;
	}

	int getPossiModel() const {
		return possiModel;
	}
	static const int possiModel;
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

	template <int l, Type t>
	relatedBlock(const singleBlock<l, t> &x){}

	template <int l>
	relatedBlock(const relatedBlock<l> &x){}
	
	relatedBlock() = default;

	// Construct a related block according to single PY block and single Character block
	relatedBlock(const singleBlock<length, e_Py> &A, const singleBlock<length, e_Char> &B){
		for (int i = 0;i < length;i++){
			block[i]   = A.block[i];
			related[i] = B.block[i];
		}
	}	

	int operator<(const relatedBlock<length> &x) const{
		for (int i = 0;i < length;i++)
			if (block[i] != x.block[i]) return block[i] < x.block[i];
		for (int i = 0;i < length;i++)
			if (related[i] != x.related[i]) return related[i] < x.related[i];
	}

	int operator==(const relatedBlock<length> &x) const{
		for (int i = 0;i < length;i++)
			if (block[i] != x.block[i]) return 0;
		for (int i = 0;i < length;i++)
			if (related[i] != x.related[i]) return 0;
		return 1;
	}

	friend class merge;
	int getPossiModel() const {
		return possiModel;
	}
	static const int possiModel;

	int block[length];
	int related[length];
};

template <int length>
const int relatedBlock<length>::possiModel = 233 + length;

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

template <int l1, int l2, Type type>
singleBlock<l1 + l2, type> operator+(const singleBlock<l1, type> &A, const singleBlock<l2, type> &B){
	singleBlock<l1 + l2, type> ret;
	for (int i = 0;i < l1;i++)
		ret.block[i] = A.block[i];
	for (int i = 0;i < l2;i++)
		ret.block[i + l1] = B.block[i];
	return ret;
}

template <int length, Type type>
std::ostream& operator<<(std::ostream &os, const singleBlock<length, type> &x){
	if (type == e_Char){
		for (int i = 0;i < length;i++) os << Dict::int2char[x.block[i]];
	}else if (type == e_Py)
		for (int i = 0;i < length;i++) os << Dict::int2py[x.block[i]];
	os << " ";
	return os;
}

template <int length>
std::ostream& operator<<(std::ostream &os, const relatedBlock<length> &x){
	for (int i = 0;i < length;i++) os << Dict::int2py[x.block[i]] << " ";
	for (int i = 0;i < length;i++) os << Dict::int2char[x.related[i]];
	os << " ";
	return os;
}

#endif // ! WORDS_H
