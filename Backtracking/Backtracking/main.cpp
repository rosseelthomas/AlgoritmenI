//
//  main.cpp
//  Backtracking
//
//  Created by Thomas Rosseel on 17/05/15.
//  Copyright (c) 2015 trosseel. All rights reserved.
//
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <stdio.h>
#include <iostream>
#include "backtrackflex.h"


int main(int argc, const char * argv[]) {
    srand (time(NULL));
    Backtrackflex<std::pair<int,int>> b;
    b.losOp(false);
    
    return 0;
}
