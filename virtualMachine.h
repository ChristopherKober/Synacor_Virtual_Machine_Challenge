//
//  virtualMachine.hpp
//  Synacor Virtual Machine Challenge
//
//  Created by Kent on 12/24/15.
//
//

#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

class virtualMachine {
public:
    virtualMachine();
    unsigned short getWord();
    
private:
    ifstream file;
    unsigned short r1;
    unsigned short r2;
    unsigned short r3;
    unsigned short r4;
    unsigned short r5;
    unsigned short r6;
    unsigned short r7;
    unsigned short r8;
};