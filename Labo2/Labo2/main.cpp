#include <iostream>
#include "sortvector.h"
using namespace std;

class Nstring : public string{
public:
    Nstring():string("0"){}
    Nstring(int i):string(to_string(i)){}
    friend bool operator<(const string s1, const string s2){
        return stoi(s1)<stoi(s2);
    }
    friend bool operator>(const string s1, const string s2){
        return stoi(s1)>stoi(s2);
    }

};

int main(){
    /*
    srand(time(0));
    Sortvector<Nstring> v(11);
    cout << v ;
    v.vul_omgekeerd();
    cout << v;
    v.draai_om();
    cout<<v;
    v.shuffle();
    cout<<v;
    v.sorteer(InsertionSort<Nstring>());
    cout << v;
     */
    
    //InsertionSort<int> sorteer;
    //meet(1000,100000, sorteer, cout);
    
    
    srand(time(0));
    Sortvector<int> v(100);
    v.vul_omgekeerd();
    v.draai_om();
    v.shuffle();
    //v[0]=0;v[1]=3;v[2]=2;v[3]=1;v[4]=3;v[4]=4;v[5]=4;v[6]=0;v[7]=5;v[8]=2;v[9]=100;
    cout <<v<<endl;
     v.sorteer(FancyQuickSort<int>());
    cout << v;
    
    
    
}

