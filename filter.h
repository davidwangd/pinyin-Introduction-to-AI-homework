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
	RETURN_TYPE FUNCNAME(const singleBlock<length, type> &x) CONST_FLAG;	\
	template <int length>													\
	RETURN_TYPE FUNCNAME(const relatedBlock<length> &x) CONST_FLAG


/*

This part is using #DEFINE to Define all function except_ RemoveIf

*/
#define DEFINE_FUNC_NAME(RETURN_TYPE,FUNCNAME,CONST_FLAG,RETURN_FLAG)				\
	template<int length, Type type>													\
	RETURN_TYPE Filter::FUNCNAME(const singleBlock<length, type>&x) CONST_FLAG{		\
		if (type == e_Py){															\
			if (length == 1) RETURN_FLAG Py1 -> FUNCNAME(x);						\
			if (length == 2) RETURN_FLAG Py2 -> FUNCNAME(x);						\
			if (length == 3) RETURN_FLAG Py3 -> FUNCNAME(x);						\
			if (length == 4) RETURN_FLAG Py4 -> FUNCNAME(x);						\
		}else{																		\
			if (length == 1) RETURN_FLAG Char1 -> FUNCNAME(x);						\
			if (length == 2) RETURN_FLAG Char2 -> FUNCNAME(x);						\
			if (length == 3) RETURN_FLAG Char3 -> FUNCNAME(x);						\
			if (length == 4) RETURN_FLAG Char4 -> FUNCNAME(x);						\
		}																			\
	}																				\
	template <int length>															\
	RETURN_TYPE Filter::FUNCNAME(const relatedBlock<length> &x) CONST_FLAG{			\
		if (length == 1) RETURN_FLAG Re1 -> FUNCNAME(x);							\
		if (length == 2) RETURN_FLAG Re2 -> FUNCNAME(x);							\
		if (length == 3) RETURN_FLAG Re3 -> FUNCNAME(x);							\
		if (length == 4) RETURN_FLAG Re4 -> FUNCNAME(x);							\
	}																				


#define DEFINE_REMOVEALLIF_FUNC(TYPE,POINTER)								\
	void removeAllIf(int (*func)(const PossiModel<TYPE> &x)){  	\
		POINTER -> removeAllIf(func);										\
	}
/*

#define 

*/

class Filter{
public:
	Filter();
	~Filter() = default;

	DECLARE_FUNC_NAME(int, getTotal, const);
	DECLARE_FUNC_NAME(int, getCount, const);
	DECLARE_FUNC_NAME(void, Add, );
	DECLARE_FUNC_NAME(void, Remove, );
	DECLARE_FUNC_NAME(double, getPossi, const);
	DECLARE_FUNC_NAME(void, removeAll, );

	void removeAllIf(int (*func)(const PossiModel<(singleBlock<1, e_Py>::possiModel)> &x)){ Py1 -> removeAllIf(func); };
	void removeAllIf(int (*func)(const PossiModel<(singleBlock<2, e_Py>::possiModel)> &x)){ Py2 -> removeAllIf(func); };
	void removeAllIf(int (*func)(const PossiModel<(singleBlock<3, e_Py>::possiModel)> &x)){ Py3 -> removeAllIf(func); };
	void removeAllIf(int (*func)(const PossiModel<(singleBlock<4, e_Py>::possiModel)> &x)){ Py4 -> removeAllIf(func); };

	void removeAllIf(int (*func)(const PossiModel<(singleBlock<1, e_Char>::possiModel)> &x)){ Char1 -> removeAllIf(func); };
	void removeAllIf(int (*func)(const PossiModel<(singleBlock<2, e_Char>::possiModel)> &x)){ Char2 -> removeAllIf(func); };
	void removeAllIf(int (*func)(const PossiModel<(singleBlock<3, e_Char>::possiModel)> &x)){ Char3 -> removeAllIf(func); };
	void removeAllIf(int (*func)(const PossiModel<(singleBlock<4, e_Char>::possiModel)> &x)){ Char4 -> removeAllIf(func); };

	void removeAllIf(int (*func)(const PossiModel<(relatedBlock<1>::possiModel)> &x)){ Re1 -> removeAllIf(func); };
	void removeAllIf(int (*func)(const PossiModel<(relatedBlock<2>::possiModel)> &x)){ Re2 -> removeAllIf(func); };
	void removeAllIf(int (*func)(const PossiModel<(relatedBlock<3>::possiModel)> &x)){ Re3 -> removeAllIf(func); };
	void removeAllIf(int (*func)(const PossiModel<(relatedBlock<4>::possiModel)> &x)){ Re4 -> removeAllIf(func); };

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

private:
	void * getPointer(int length, Type type) const{
		if (type == e_Char){
			if (length == 1) return (void *)Char1;
			if (length == 2) return (void *)Char2;
			if (length == 3) return (void *)Char3;
			if (length == 4) return (void *)Char4;
		}else if (type == e_Py){
			if (length == 1) return (void *)Py1;
			if (length == 2) return (void *)Py2;
			if (length == 3) return (void *)Py3;
			if (length == 4) return (void *)Py4;
		}else if (type == e_Total){
			if (length == 1) return (void *)Re1;
			if (length == 2) return (void *)Re2;
			if (length == 3) return (void *)Re3;
			if (length == 4) return (void *)Re4;
		}
	}

};

#include "filter.cpp"

#endif