#include "filter.h"

DEFINE_FUNC_NAME(int, getTotal, const)	
DEFINE_FUNC_NAME(int, getCount, const)
DEFINE_FUNC_NAME(void, Add, )
DEFINE_FUNC_NAME(void, Remove, )
DEFINE_FUNC_NAME(double, getPossi, const)
DEFINE_FUNC_NAME(void, removeAll, )

template <int length, Type type>
void Filter::removeAllIf(int (*func)(const singleBlock<length, type> &x)){
	if (type == e_Py){
		if (length == 1) Py1->removeAllIf(func);
		if (length == 2) Py2->removeAllIf(func);
		if (length == 3) Py3->removeAllIf(func);
		if (length == 4) Py4->removeAllIf(func);
	}else if (type == e_Char){
		if (length == 1) Char1->removeAllIf(func);
		if (length == 2) Char2->removeAllIf(func);
		if (length == 3) Char3->removeAllIf(func);
		if (length == 4) Char4->removeAllIf(func);
	}
}

template <int length>
void Filter::removeAllIf(int (*func)(const relatedBlock<length> &x)){
	if (length == 1) Re1->removeAllIf(func);
	if (length == 2) Re2->removeAllIf(func);
	if (length == 3) Re3->removeAllIf(func);
	if (length == 4) Re4->removeAllIf(func);
}

template<int type>
void Filter::removeAllIf(int (*func)(const PossiModel<type> &x)){
	#define CHECK_PER(CLASS,NAME) \
		if (type == CLASS::possiModel) NAME -> removeAllIf(func);

	if (type == singleBlock<1, e_Py>::possiModel) Py1 -> removeAllIf(func);
	if (type == singleBlock<2, e_Py>::possiModel) Py2 -> removeAllIf(func);
	if (type == singleBlock<3, e_Py>::possiModel) Py3 -> removeAllIf(func);
	if (type == singleBlock<4, e_Py>::possiModel) Py4 -> removeAllIf(func);

	if (type == singleBlock<1, e_Char>::possiModel) Char1 -> removeAllIf(func);
	if (type == singleBlock<2, e_Char>::possiModel) Char2 -> removeAllIf(func);
	if (type == singleBlock<3, e_Char>::possiModel) Char3 -> removeAllIf(func);
	if (type == singleBlock<4, e_Char>::possiModel) Char4 -> removeAllIf(func);

	if (type == relatedBlock<1>::possiModel) Re1 -> removeAllIf(func);
	if (type == relatedBlock<2>::possiModel) Re2 -> removeAllIf(func);
	if (type == relatedBlock<3>::possiModel) Re3 -> removeAllIf(func);
	if (type == relatedBlock<4>::possiModel) Re4 -> removeAllIf(func);

} 