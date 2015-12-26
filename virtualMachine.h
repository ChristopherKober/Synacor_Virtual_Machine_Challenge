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
    void run();
    
private:
    int interpretCommand(unsigned short command);
    unsigned short getWord();
    
    ifstream file;
    unsigned short r[8];
    int eip;
    short flags;
};