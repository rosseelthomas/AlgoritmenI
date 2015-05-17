#ifndef __BINBOOM_H
#define __BINBOOM_H

#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
#include <fstream>
using std::ostream;
using std::istream;
#include <string>
using std::string;
#include <memory>
#include <sstream>
using std::stringstream;

#include <fstream>
using std::ifstream;

#include <vector>
using std::vector;



template <class T>
class Binknoop;


template<class T>
using Binknoopptr=std::unique_ptr<Binknoop<T> >;



template <class T>
class BinaireBoom: protected Binknoopptr<T> {
    using std::unique_ptr<Binknoop<T> >::unique_ptr;
public:
    static int aantal_boom_constructor;
    static int aantal_boom_destructor;
    
//private:
    void lees(const string &);  // leest bestand in en bouwt boom op
    
    void schrijf_inorder(ostream & os) const;
    void schrijf_preorder(ostream & os) const{};
    void schrijf_postorder(ostream & os) const{};
				
public:
    BinaireBoom<T>(){aantal_boom_constructor++;}
    BinaireBoom<T>(const string &);   // construeert boom aan de hand van gegevens in bestand
    BinaireBoom<T>(const BinaireBoom &);
    ~BinaireBoom<T>(){
        aantal_boom_destructor++;
        //...
    }
    void schrijf(ostream & os, const string & volgorde="in")const{
        if(volgorde == "inorder" || volgorde == "in") schrijf_inorder(os);
        else if(volgorde == "preorder" || volgorde == "pre") schrijf_preorder(os);
        else schrijf_postorder(os);
    }
    
    friend ostream& operator<< (ostream & os, const BinaireBoom<T> & b){
        b.schrijf(os,"inorder", true);
        return os;
    }
    
};

template <class T>
class Binknoop{
    
public:
    static int aantal_knoop_constructor_default;
    static int aantal_knoop_constructor_param;
    static int aantal_knoop_destructor;
    
    friend class BinaireBoom<T>;
    const T inhoud;
    BinaireBoom<T> links,rechts;
    
    Binknoop<T>(){aantal_knoop_constructor_default++;}
    Binknoop<T>(const T & geg):inhoud(geg){aantal_knoop_constructor_param++;}
    ~Binknoop<T>(){aantal_knoop_destructor++;}
    
};

//________________________________________________________________________________________________



template <class T>
int BinaireBoom<T>::aantal_boom_constructor = 0;
template <class T>
int BinaireBoom<T>::aantal_boom_destructor = 0;

template <class T>
void BinaireBoom<T>::lees(const string& s) {

    ifstream stream(s);
    string aantal;
    stream>>aantal;
    int a = atoi(aantal.c_str());
    vector<BinaireBoom<T>> v(a);
    
    
    string titel,links, rechts;
    while(stream>>titel){
        stream >> links;
        stream >> rechts;
        
        
        Binboom<T> hulp((std::unique_ptr<Binknoop<T>>)new Binknoop(sleutel));
        
        
    }

};




//________________________________________________________________________________________________

template <class T>
int Binknoop<T>::aantal_knoop_constructor_default = 0;
template <class T>
int Binknoop<T>::aantal_knoop_constructor_param = 0;
template <class T>
int Binknoop<T>::aantal_knoop_destructor = 0;


#endif

