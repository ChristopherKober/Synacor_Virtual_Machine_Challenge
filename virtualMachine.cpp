//
//  virtualMachine.cpp
//  Synacor Virtual Machine Challenge
//
//  Created by Kent on 12/24/15.
//
//

#include "virtualMachine.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;


//commands
#define HALT 0
#define SET 1
#define PUSH 2
#define POP 3
#define EQ 4
#define GT 5
#define JMP 6
#define JT 7
#define JF 8
#define ADD 9
#define MULT 10
#define MOD 11
#define AND 12
#define OR 13
#define NOT 14
#define RMEM 15
#define WMEM 16
#define CALL 17
#define RET 18
#define OUT 19
#define IN 20
#define NOP 21





virtualMachine::virtualMachine() {
    for (int i = 0; i<8;i++) {
        r[i] = 0;
    }
    
    clearBreaks();
}


unsigned short virtualMachine::getWord() {
    
    if (file.eof()) {
        return -1;
    }
    char firstByte;
    char secondByte;
    
    file.get(firstByte);
    file.get(secondByte);
    
    return (((unsigned short) (firstByte)) & 255) + ((((unsigned short) secondByte) << 8) & ~(255));
}

void virtualMachine::run(string f) {
    
    file = fstream(f, fstream::in | fstream::out | ios::binary);
    
    
    
    unsigned short val = 0;
    int running = 0;

    while (running == 0) {
        val = getWord();
        running = interpretCommand(val);
    }
    
    cout << val << endl;
}

void virtualMachine::runProtected(string f) {
    
    remove("curr.bin");
    
    ifstream  src(f, ios::binary);
    ofstream  dst("curr.bin", std::ios::binary);
    
    dst << src.rdbuf();
    
    src.close();
    dst.close();
    
    file = fstream("curr.bin", fstream::in | fstream::out | ios::binary);
    
    unsigned short val = 0;
    int running = 0;
    
    while (running == 0) {
        val = getWord();
        running = interpretCommand(val);
    }
    
    cout << val << endl;
}

int virtualMachine::interpretCommand(unsigned short command) {
    
    unsigned short firstVal;
    unsigned short secondVal;
    unsigned short thirdVal;
    
    switch (command) {
        case HALT:
            return 1;
        case SET:
            firstVal = getWord();
            secondVal = getWord();
            return set(firstVal,secondVal);
        case PUSH:
            firstVal = getWord();
            return push(firstVal);
        case POP:
            firstVal = getWord();
            return pop(firstVal);
        case EQ:
            firstVal = getWord();
            secondVal = getWord();
            thirdVal = getWord();
            return eq(firstVal, secondVal, thirdVal);
        case GT:
            firstVal = getWord();
            secondVal = getWord();
            thirdVal = getWord();
            return gt(firstVal, secondVal, thirdVal);
        case JMP:
            firstVal = getWord();
            return jmp(firstVal);
        case JT:
            firstVal = getWord();
            secondVal = getWord();
            return jt(firstVal, secondVal);
        case JF:
            firstVal = getWord();
            secondVal = getWord();
            return jf(firstVal, secondVal);
        case ADD:
            firstVal = getWord();
            secondVal = getWord();
            thirdVal = getWord();
            return add(firstVal, secondVal, thirdVal);
        case MULT:
            firstVal = getWord();
            secondVal = getWord();
            thirdVal = getWord();
            return mult(firstVal, secondVal, thirdVal);
        case MOD:
            firstVal = getWord();
            secondVal = getWord();
            thirdVal = getWord();
            return mod(firstVal, secondVal, thirdVal);
        case AND:
            firstVal = getWord();
            secondVal = getWord();
            thirdVal = getWord();
            return And(firstVal, secondVal, thirdVal);
        case OR:
            firstVal = getWord();
            secondVal = getWord();
            thirdVal = getWord();
            return Or(firstVal, secondVal, thirdVal);
        case NOT:
            firstVal = getWord();
            secondVal = getWord();
            return Not(firstVal, secondVal);
        case RMEM:
            firstVal = getWord();
            secondVal = getWord();
            return rmem(firstVal, secondVal);
        case WMEM:
            firstVal = getWord();
            secondVal = getWord();
            return wmem(firstVal, secondVal);
        case CALL:
            firstVal = getWord();
            return call(firstVal);
        case RET:
            return ret();
        case OUT:
            firstVal = getWord();
            return Out(firstVal);
        case IN:
            firstVal = getWord();
            return In(firstVal);
        case NOP:
            break;
        default:
            cout << "ERROR: Unknown Command" << endl;
            return 1;
            break;
    }
    
    
    return 0;
}

unsigned short virtualMachine::getAddress() {
    return (unsigned short) (file.tellg() >> 1);
}

virtualMachine::~virtualMachine() {
    remove("curr.bin");
}
