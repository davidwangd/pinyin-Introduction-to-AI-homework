
DEFINE_FUNC_NAME(int, getTotal, const, return);	
DEFINE_FUNC_NAME(int, getCount, const, return);
DEFINE_FUNC_NAME(void, Add, , );
DEFINE_FUNC_NAME(void, Remove, , );
DEFINE_FUNC_NAME(double, getPossi, const, return);
DEFINE_FUNC_NAME(void, removeAll, , );

Filter::Filter(){
	Py1 = PossiField<singleBlock<1, e_Py>, singleBlock<1, e_Py>::possiModel>::Instance();
	Py2 = PossiField<singleBlock<2, e_Py>, singleBlock<2, e_Py>::possiModel>::Instance();
	Py3 = PossiField<singleBlock<3, e_Py>, singleBlock<3, e_Py>::possiModel>::Instance();
	Py4 = PossiField<singleBlock<4, e_Py>, singleBlock<4, e_Py>::possiModel>::Instance();

	Char1 = PossiField<singleBlock<1, e_Char>, singleBlock<1, e_Char>::possiModel>::Instance();
	Char2 = PossiField<singleBlock<2, e_Char>, singleBlock<2, e_Char>::possiModel>::Instance();
	Char3 = PossiField<singleBlock<3, e_Char>, singleBlock<3, e_Char>::possiModel>::Instance();
	Char4 = PossiField<singleBlock<4, e_Char>, singleBlock<4, e_Char>::possiModel>::Instance();

	Re1 = PossiField<relatedBlock<1>, relatedBlock<1>::possiModel>::Instance();
	Re2 = PossiField<relatedBlock<2>, relatedBlock<2>::possiModel>::Instance();
	Re3 = PossiField<relatedBlock<3>, relatedBlock<3>::possiModel>::Instance();
	Re4 = PossiField<relatedBlock<4>, relatedBlock<4>::possiModel>::Instance();
}