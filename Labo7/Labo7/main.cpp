//
//  main.cpp
//  Labo7
//
//  Created by Thomas Rosseel on 30/03/15.
//  Copyright (c) 2015 trosseel. All rights reserved.
//

#include <iostream>
#include <vector>
#include "backtrackflex.h";
using namespace std;

template <class knoop>
class Trackback : Backtrackflex<knoop>{
    bool controle(){
        return true;
    }

};







int main(int argc, const char * argv[]) {
    vector<int> v(5);
    for(int i=0;i<5;++i){
        v[i]=i;
    }
    random_shuffle(v.begin(),v.end());
    
    
    if(v[0]>v[1])iter_swap(v.begin()+0,v.begin()+1);
    
    if(v[3]>v[4])iter_swap(v.begin()+3,v.begin()+4);
    
    
    
    
    for(int i=0;i<v.size();++i){
        cout << i<<": "<<v[i]<<endl;
    }
}
