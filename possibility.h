#ifndef POSSI_H
#define POSSI_H
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>

enum pyPossiModelType{
	e_pinyinPossi = 0,
	e_characterPossi,
	e_2pinyinPossi,
	e_2characterPossi,
	e_possiModelTypeCount,
	e_testPossi
};

// a class hold the possibility of a certain things in certain field.
// static int Total is declared in each concrete class
template<pyPossiModelType type>
class pyPossiModel{
public:
	pyPossiModel() = default;
	~pyPossiModel() = default;

	// Add this one to all this field
	void Add(){
		Count++;
		Total++;
	}

	// remove an data of this one to all this field.
	void Remove(){
		Count--;
		Total--;
	}
	// return -log(P) = -log(Count / Total)
	double getPossi() const {
		return -log((double)Count / (double)Total);
	}

	// get the Count;
	int getCount() const {
		return Count;
	}

	int getTotal() const {
		return Total;
	}

private:
	int Count;
	static int Total;
};

template<pyPossiModelType type>
int pyPossiModel<type>::Total = 0;

// Tp is the struct solve filed data
// Model is inherited from pyPossiModel
// Which is Unique in Field.
// Singleton model is used

template <typename Tp, pyPossiModelType type>
class pyPossiField{
	typedef pyPossiModel<type> Model;
	typedef std::map<Tp, Model> Map;
public:
	static pyPossiField* Instance(){
		if (_instance == nullptr){
			_instance = new pyPossiField<Tp, type>();
		}
		return _instance;
	}
	// Add an certain data to this field.
	void Add(const Tp &data);

	// Remove an certain data to this field.
	void Remove(const Tp &data);

	// return the -log(P) of this data to this field.
	double getPossi(const Tp &data) const;

	// return total sample of this field
	int getTotal() const;

	// return Count of certain data of this field
	int getCount(const Tp &data) const;

	// remove all element with possibility than threshold, -log(P) > -log(threshold);
	void removeElementsLessThan(double threshold);
private:
	pyPossiField() = default;
	~pyPossiField() = default;
	Map mp;
	static pyPossiField* _instance;
};

template <typename Tp, pyPossiModelType type>
pyPossiField<Tp, type>* pyPossiField<Tp, type>::_instance = nullptr;

template <typename Tp, pyPossiModelType type>
inline void pyPossiField<Tp, type>::Add(const Tp &data){
	auto it = mp.find(data);
	if (it == mp.end()){
		auto res = mp.insert(std::make_pair(data, Model()));

		// unsuccessfully add
		if (!res.second){
			fprintf(stderr, "%s\n", "pyPossiField::ADDERROR");
			throw std::string("pyPossiField::ADDERROR");
		}
		res.first -> second.Add();
		return;
	}
	it -> second.Add();
}

template <typename Tp, pyPossiModelType type>
inline void pyPossiField<Tp, type>::Remove(const Tp &data){
	auto it = mp.find(data);
	if (it == mp.end()){
		auto res = mp.insert(std::make_pair(data, Model()));

		// unsuccessfully add
		if (!res.second){
			fprintf(stderr, "%s\n", "pyPossiField::ADDERROR");
			throw std::string("pyPossiField::ADDERROR");
		}
		res.first -> second.Remove();
		return;
	}
	it -> second.Remove();
}

template <typename Tp, pyPossiModelType type>
inline double pyPossiField<Tp, type>::getPossi(const Tp &data) const{
	auto it = mp.find(data);
	// not exists
	if (it == mp.end()) return 0.0f;
	return it -> second.getPossi();
}

template <typename Tp,pyPossiModelType type>
inline int pyPossiField<Tp, type>::getCount(const Tp &data) const{
	auto it = mp.find(data);

	if (it == mp.end()) return 0;
	return it -> second.getCount();
}

template <typename Tp, pyPossiModelType type>
inline int pyPossiField<Tp, type>::getTotal() const {
	// no samples at all
	if (mp.begin() == mp.end()) return 0;

	// at least one sample
	return mp.begin() -> second.getTotal();
}

template <typename Tp, pyPossiModelType type>
inline void pyPossiField<Tp, type>::removeElementsLessThan(double threshold){
	double mlog = -log(threshold);
	for (auto it = mp.begin(); it != mp.end(); it++){
		if (it -> second.getPossi() > mlog){
			auto j = it;
			it--;
			mp.erase(j);
		}
	}
}

#endif //! POSSI_H