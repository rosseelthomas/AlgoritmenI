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
    
}

