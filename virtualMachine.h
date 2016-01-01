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

#include "stack.h"

using namespace std;

class virtualMachine {
public:
    virtualMachine();
    void runProtected(string f);
    void run(string f);
    void debugProtected(string f);
    void debug(string f);
    ~virtualMachine();
    
private:
    int interpretCommand(unsigned short command);
    unsigned short getWord();
    unsigned short getAddress();
    
    int set(unsigned short reg, unsigned short val);
    int push(unsigned short val);
    int pop(unsigned short dest);
    int eq(unsigned short dest, unsigned short val1, unsigned short val2);
    int gt(unsigned short dest, unsigned short val1, unsigned short val2);
    int jmp(unsigned short loc);
    int jt(unsigned short val, unsigned short dest);
    int jf(unsigned short val, unsigned short dest);
    int add(unsigned short dest, unsigned short val1, unsigned short val2);
    int mult(unsigned short dest, unsigned short val1, unsigned short val2);
    int mod(unsigned short dest, unsigned short val1, unsigned short val2);
    int And(unsigned short dest, unsigned short val1, unsigned short val2);
    int Or(unsigned short dest, unsigned short val1, unsigned short val2);
    int Not(unsigned short dest, unsigned short val);
    int rmem(unsigned short dest, unsigned short adr);
    int wmem(unsigned short dest, unsigned short val);
    int call(unsigned short start);
    int ret();
    int Out(unsigned short chr);
    int In(unsigned short dest);
    
    void addBreak(string op);
    void removeBreak(string op);
    void printBreaks();
    void clearBreaks();
    void printCommands(string num);
    void dumpRegisters();
    void printHelp();
    void debugJmp(string adr);
    int numArgs(unsigned short cmd);
    string getString(unsigned short cmd);
    
    fstream file;
    unsigned short r[8];
    stack s;
    unsigned char opBreaks[22];
    unsigned char lineBreaks[50];
    int numLineBreaks;
};

