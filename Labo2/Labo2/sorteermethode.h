#ifndef __SORTEERMETHODE
#define __SORTEERMETHODE

#include <iostream>
    using std::endl;
    using std::cout;
#include <vector>
	using std::vector;
#include <algorithm>   // voor sort()-methode uit STL

template <typename T>
class Sorteermethode{
	public:
		virtual void operator()(vector<T> & v) const = 0;
};

/*
 *   STANDARD TEMPLATE LIBRARY SORT
 */
template <typename T>
class STLSort : public Sorteermethode<T>{
	public:
		void operator()(vector<T> & v) const;
};

template <typename T>
void STLSort<T>::operator()(vector<T> & v) const{
	sort(v.begin(),v.end());
}

/*
 *   INSERTION SORT
 */
template <typename T>
class InsertionSort : public Sorteermethode<T>{
	public:
		void operator()(vector<T> & v) const;	
};

template <typename T>
void InsertionSort<T>::operator()(vector<T> & v) const{
	for(int i=1; i<v.size(); i++){
		T h = v[i];
		int j=i-1;
		while(j>=0 && h<v[j]){
			v[j+1] = v[j];   
			j--;
		}
		v[j+1] = h;
	}
}

/*
 *   SHELLSORT
 */
 
template <typename T>
class ShellSort : public Sorteermethode<T>{
	public:
		void operator()(vector<T> & v) const;
};

#endif 
