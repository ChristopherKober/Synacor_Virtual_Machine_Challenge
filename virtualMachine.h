//
//  virtualMachine.h
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
    void run(string f);
    
private:
    int interpretCommand(unsigned short command);
    unsigned short getWord();
    
    int set(unsigned short reg, unsigned short val);
    int eq(unsigned short dest, unsigned short val1, unsigned short val2);
    int gt(unsigned short dest, unsigned short val1, unsigned short val2);
    int jmp(unsigned short loc);
    int jt(unsigned short val, unsigned short dest);
    int jf(unsigned short val, unsigned short dest);
    
    int wmem(unsigned short dest, unsigned short val);
    
    fstream file;
    unsigned short r[8];
    int eip;
    unsigned short flags;
};

