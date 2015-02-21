#include <iostream>
#include "sortvector.h"
using namespace std;

int main(){
    srand(time(0));
    Sortvector<int> v(11);
    cout << v ;
    v.vul_omgekeerd();
    cout << v;
    v.draai_om();
    cout<<v;
    v.shuffle();
    cout<<v;
    
}

