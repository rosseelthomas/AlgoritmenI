#ifndef __SORTVECTOR
#define __SORTVECTOR

//sortvector is een klasse van sorteerbare vectoren

#include <iostream>
   using std::istream;
   using std::ostream;
#include <iomanip>   // voor setw
#include <cstdlib>   // voor rand - opletten!! 
#include "sorteermethode.h"

template<class T>
class Sortvector{                                       
  public:

    // Constructor: het argument geeft de grootte aan
    // bij constructie zal de tabel opgevuld worden met 
	// n verschillende getallen in random volgorde
    // (zie hulplidfunctie)
    Sortvector(int);
    
    // Geeft onderstaande code compileerfouten of warnings?
    // Zorg dat de compiler C++11-code aankan.
    // In Dev-C++: 
	// in menubalk: Tools - compiler options - general - 
	// 'add the following commands when calling the compiler': -std=c++11
    Sortvector(const Sortvector<T>& v) = delete;
    Sortvector<T>& operator=(const Sortvector<T>& v) = delete;
    Sortvector<T>& operator=(Sortvector<T>&& v) = delete;
    Sortvector(Sortvector<T>&& v) = delete;

    const T &operator[](int i) const { return tab[i]; }  // voor rechterlid
          T &operator[](int i)       { return tab[i]; }  // voor linkerlid

    // sorteer sorteert de tabel.
    // Het argument geeft de sorteermethode aan
    void sorteer(const Sorteermethode<T> & methode);
    
    void vul_range();
    void draai_om();
    void vul_omgekeerd();
    void shuffle();
    void vul_random_zonder_dubbels();
    void vul_random(); // nog niet implementeren
    
    bool is_gesorteerd() const;
	bool is_range() const;

    friend ostream& operator<<(ostream& os, const Sortvector<T>& s){
  	    s.schrijf(os);
  	    return os;
    }

  private: 
    vector<T> tab;
    
    void schrijf(ostream & os)const;
    
};

template <class T>
void Sortvector<T>::schrijf(ostream & os)const{
	for(int i=0; i<tab.size(); i++){
		os<<tab[i]<<" ";
	}
	os<<endl;
}

template <class T>
Sortvector<T>::Sortvector(int a):tab(a){
    

}

template<class T>
void Sortvector<T>::draai_om(){

    for(int i=0;i<=tab.size()/2;++i){
        T temp = tab[i];
        tab[i]=tab[tab.size()-1-i];
        tab[tab.size()-1-i] = temp;
    
    }

}


// Het volgende is geen lidfunctie van een klasse.
// Deze externe procedure schrijft naar os een overzicht (met de nodige ornamenten) 
// met de snelheid van de opgegeven sorteermethode sm. Er wordt 1 lijn uitgedrukt voor elke mogelijke
// grootte. Deze groottes zijn kleinste, 10*kleinste, 100*kleinste,
// enzovoorts, tot aan grootste.
// Op een lijn staat de snelheid van de methode toegepast op
// (1) een random tabel
// (2) een al gesorteerde tabel.
// (3) een omgekeerd gesorteerde tabel.

// Deze functie werkt alleen als T een toekenning van een int toelaat,
// zodat bv.
//    T a=5;
// geldig is.
template<class T>
void meet(int kortste, int langste, const Sorteermethode<T> &  sm, ostream& os);

template <class T>
void Sortvector<T>::vul_range(){
    int size = tab.size();
    
    for(int i=0;i<size;++i){
        tab[i]=i;
    }

}
template <class T>
void Sortvector<T>::vul_omgekeerd(){
    int size = tab.size();
    
    for(int i=0;i<size;++i){
        tab[i]=size-1-i;
    }
    
}

template <class T>
void Sortvector<T>::shuffle(){

    for(int i=0;i<tab.size();++i){
        int j = (rand()%(tab.size()-i))+i;
        T temp = tab[i];
        tab[i]=tab[j];
        tab[j]=temp;
    
    }

}


#endif
