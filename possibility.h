#ifndef POSSI_H
#define POSSI_H
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <cmath>
#include <iostream>
#include <map>
#include <set>

namespace Possi{

	// a class hold the possibility of a certain things in certain field.
	// static int Total is declared in each concrete class
	template<int type>
	class PossiModel{
	public:
		PossiModel(){
			Count = 0;
		}

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

		void removeAll(){
			Total -= Count;
			Count = 0;
		}

		// return -log(P) = -log(Count / Total)
		double getPossi() const {
			return -log((double)Count / (double)Total);
		}

		// get the Count;
		int getCount() const {
			return Count;
		}

		// get Total count of this field
		int getTotal() const {
			return Total;
		}

	private:
		int Count;
		static int Total;
	};

	template<int type>
	int PossiModel<type>::Total = 0;

	// Tp is the struct solve filed data
	// Model is inherited from PossiModel
	// Which is Unique in Field.
	// Singleton model is used

	template <typename Tp, int type>
	class PossiField{
		typedef PossiModel<type> Model;
		typedef std::map<Tp, Model> Map;
		typedef std::set<Tp> Set;
	public:
		static PossiField* Instance(){
			if (_instance == nullptr){
				_instance = new PossiField<Tp, type>();
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

		// remove all elemetns with a checker function
		void removeAllElementsIf(int (* func)(const Tp &data));

		void removeAllIf(int (* func)(const PossiModel<type> &x));

		// remove all elements of certain type
		void removeAll(const Tp &data);

		// for debugging usage;
		void show(std::ostream &out){
			for (auto x:mp){
				out << x.first << ":" << x.second.getCount() << "/" << x.second.getTotal() << "  " << x.second.getPossi() << std::endl;
			}
			out << "==========================" << std::endl;
			out << "Show Over " << std::endl;
			out << "==========================" << std::endl;
		}

	private:
		PossiField() = default;
		~PossiField() = default;
		Map mp;
		Set st;
		static PossiField* _instance;
	};

	template <typename Tp, int type>
	PossiField<Tp, type>* PossiField<Tp, type>::_instance = nullptr;

	template <typename Tp, int type>
	inline void PossiField<Tp, type>::Add(const Tp &data){
		if (st.count(data) == 0){
			auto res = mp.insert(std::make_pair(data, Model()));
			st.insert(data);
			// unsuccessfully add
			if (!res.second){
				fprintf(stderr, "%s\n", "PossiField::ADDERROR");
				throw std::string("PossiField::ADDERROR");
			}
			res.first -> second.Add();
			return;
		}else mp[data].Add();
	}

	template <typename Tp, int type>
	inline void PossiField<Tp, type>::Remove(const Tp &data){
		auto it = mp.find(data);
		if (it == mp.end()){
			auto res = mp.insert(std::make_pair(data, Model()));

			// unsuccessfully add
			if (!res.second){
				fprintf(stderr, "%s\n", "PossiField::ADDERROR");
				throw std::string("PossiField::ADDERROR");
			}
			res.first -> second.Remove();
			return;
		}
		it -> second.Remove();
	}

	template <typename Tp, int type>
	inline double PossiField<Tp, type>::getPossi(const Tp &data) const{
		auto it = mp.find(data);
		// not exists
		if (it == mp.end()) return 0.0f;
		return it -> second.getPossi();
	}

	template <typename Tp,int type>
	inline int PossiField<Tp, type>::getCount(const Tp &data) const{
		auto it = mp.find(data);

		if (it == mp.end()) return 0;
		return it -> second.getCount();
	}

	template <typename Tp, int type>
	inline int PossiField<Tp, type>::getTotal() const {
		// no samples at all
		if (mp.begin() == mp.end()) return 0;

		// at least one sample
		return mp.begin() -> second.getTotal();
	}

	template <typename Tp, int type>
	inline void PossiField<Tp, type>::removeElementsLessThan(double threshold){
		double mlog = -log(threshold);
		for (auto it = mp.begin(); it != mp.end(); it++){
			if (it -> second.getPossi() > mlog){
				auto j = it;
				it--;
				j -> second.removeAll();
				mp.erase(j);
			}
		}
	}

	template <typename Tp, int type>
	inline void PossiField<Tp, type>::removeAll(const Tp &x){
		auto it = mp.find(x);
		if (it == mp.end()) return;
		it -> second.removeAll();
		mp.erase(it);
	}

	template <typename Tp, int type>
	inline void PossiField<Tp, type>::removeAllElementsIf(int (* func)(const Tp &x)){
		for (auto it = mp.begin();it != mp.end();){
			if (func(it -> first)){
				auto j = it;
				j -> second.removeAll();
				if (it == mp.begin()){
					mp.erase(j);
					it = mp.begin();
				}else{
					it--;
					mp.erase(j);
					it++;
				}
			}else it++;
		}
	}

	template <typename Tp, int type>
	inline void PossiField<Tp, type>::removeAllIf(int (* func)(const PossiModel<type> &x)){
		for (auto it = mp.begin();it != mp.end(); ){
			if (func(it -> second)){
				auto j = it;
				j -> second.removeAll();
				if (it == mp.begin()){
					mp.erase(j);
					it = mp.begin();
				}else{
					it--;
					mp.erase(j);
					it++;
				}
			}else it++;
		}
	}
}
// namespace Possi
#endif //! POSSI_H