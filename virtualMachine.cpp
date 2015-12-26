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

//flags
#define JUMPED 1


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
    file = ifstream("challenge.bin", ios::in|ios::binary);
    eip = 0;
    flags = 0;
    for (int i = 0; i<8;i++) {
        r[i] = 0;
    }
}


unsigned short virtualMachine::getWord() {
    if (file.eof()) {
        return -1;
    }
    char firstByte;
    char secondByte;
    if (flags & JUMPED) {
        flags = flags | ~JUMPED;
        file.seekg(eip*2);
    }
    file.get(firstByte);
    file.get(secondByte);
    return (((unsigned short) (firstByte))) + (((unsigned short) secondByte) << 8);
}

void virtualMachine::run() {
    unsigned short val;
    int running = 0;
    
    while (running == 0) {
        val = getWord();
        running = interpretCommand(val);
    }
}

int virtualMachine::interpretCommand(unsigned short command) {
    
    unsigned short firstVal;
    unsigned short secondVal;
    unsigned short thirdVal;
    
    if (!(command == HALT || command == OUT || command == NOP)) {
        return 1;
    }
    
    switch (command) {
        case HALT:
            return 1;
            break;
        case SET:
            break;
        case PUSH:
            break;
        case POP:
            break;
        case EQ:
            break;
        case GT:
            break;
        case JMP:
            break;
        case JT:
            break;
        case JF:
            break;
        case ADD:
            break;
        case MULT:
            break;
        case MOD:
            break;
        case AND:
            break;
        case OR:
            break;
        case NOT:
            break;
        case RMEM:
            break;
        case WMEM:
            break;
        case CALL:
            break;
        case RET:
            break;
        case OUT:
            firstVal = getWord();
            cout << (char) firstVal;
            break;
        case IN:
            break;
        case NOP:
            break;
        default:
            cout << "ERROR: Unknown Command" << endl;
            return 1;
            break;
    }
    
    
    return 0;
}
