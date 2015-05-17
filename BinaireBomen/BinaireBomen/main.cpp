//
//  main.cpp
//  BinaireBomen
//
//  Created by Thomas Rosseel on 17/05/15.
//  Copyright (c) 2015 trosseel. All rights reserved.
//

#include <iostream>
#include "binboom.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    BinaireBoom<int> b;
    b.lees("/Users/thomasrosseel/Documents/AlgoritmenI/BinaireBomen/BinaireBomen/file.txt");
    
    std::cout << "Hello, World!\n";
    return 0;
}
