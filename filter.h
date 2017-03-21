#ifndef FILTER_H
#define FILTER_H
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <algorithm>

#include "possibility.h"
#include "words.h"
#include "dictionary.h"

using namespace Dict;
using namespace Possi;
using namespace std;


#define DECLARE_FUNC_NAME(RETURN_TYPE,FUNCNAME,CONST_FLAG)					\
	template <int length, Type type>										\
	RETURN_TYPE FUNCNAME(const singleBlock<length, type> &x) CONST_FLAG		\
	template <int length>													\
	RETURN_TYPE FUNCNAME(const relatedBlock<length> &x) CONST_FLAG


/*

This part is using #DEFINE to Define all function except_ RemoveIf

*/
#define DEFINE_FUNC_NAME(RETURN_TYPE,FUNCNAME,CONST_FLAG)							\
	template<int length, Type type>													\
	RETURN_TYPE Filter::FUNCNAME(const singleBlock<length, type>&x) CONST_FLAG{		\
		if (type == e_Py){															\
			if (length == 1) return Py1 -> FUNCNAME(x);								\
			if (length == 2) return Py2 -> FUNCNAME(x);								\
			if (length == 3) return Py3 -> FUNCNAME(x);								\
			if (length == 4) return Py4 -> FUNCNAME(x);								\
		}else{																		\
			if (length == 1) return Char1 -> FUNCNAME(x);							\
			if (length == 2) return Char2 -> FUNCNAME(x);							\
			if (length == 3) return Char3 -> FUNCNAME(x);							\
			if (length == 4) return Char4 -> FUNCNAME(x);							\
		}																			\
	}																				\
	template <int length>															\
	RETURN_TYPE Filter::FUNCNAME(const relatedBlock<length> &x) CONST_FLAG{			\
		if (length == 1) return Re1 -> FUNCNAME(x);									\
		if (length == 2) return Re2 -> FUNCNAME(x);									\
		if (length == 3) return Re3 -> FUNCNAME(x);									\
		if (length == 4) return Re4 -> FUNCNAME(x);									\
	}																				

/*

#define 

*/
class Filter{
public:
	Filter();
	~Filter();

	DECLARE_FUNC_NAME(int, getTotal, const);
	DECLARE_FUNC_NAME(int, getCount, const);
	DECLARE_FUNC_NAME(void, Add, );
	DECLARE_FUNC_NAME(void, Remove, );
	DECLARE_FUNC_NAME(double, getPossi, const);


private:
	// possifield recorded pinyin of all length available
	PossiField<singleBlock<1, e_Py>, singleBlock<1, e_Py>::possiModel>* Py1;
	PossiField<singleBlock<2, e_Py>, singleBlock<2, e_Py>::possiModel>* Py2;
	PossiField<singleBlock<3, e_Py>, singleBlock<3, e_Py>::possiModel>* Py3;
	PossiField<singleBlock<4, e_Py>, singleBlock<4, e_Py>::possiModel>* Py4;


	// possifield recorded character of all length available
	PossiField<singleBlock<1, e_Char>, singleBlock<1, e_Char>::possiModel>* Char1;
	PossiField<singleBlock<2, e_Char>, singleBlock<2, e_Char>::possiModel>* Char2;
	PossiField<singleBlock<3, e_Char>, singleBlock<3, e_Char>::possiModel>* Char3;
	PossiField<singleBlock<4, e_Char>, singleBlock<4, e_Char>::possiModel>* Char4;


	// posssifield recorded all relation of all length available
	PossiField<relatedBlock<1>, relatedBlock<1>::possiModel>* Re1;
	PossiField<relatedBlock<2>, relatedBlock<2>::possiModel>* Re2;
	PossiField<relatedBlock<3>, relatedBlock<3>::possiModel>* Re3;
	PossiField<relatedBlock<4>, relatedBlock<4>::possiModel>* Re4;
};

#endif