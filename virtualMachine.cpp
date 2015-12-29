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
    
    file.get(firstByte);
    file.get(secondByte);
    
    return (((unsigned short) (firstByte))) + (((unsigned short) secondByte) << 8);
}

void virtualMachine::run(string f) {
    file = fstream(f, fstream::in | fstream::out | ios::binary);
    
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
    
    switch (command) {
        case HALT:
            return 1;
        case SET:
            firstVal = getWord();
            secondVal = getWord();
            cout << "SET" << endl;
            return set(firstVal,secondVal);
        case PUSH:
            return 1;
        case POP:
            return 1;
        case EQ:
            firstVal = getWord();
            secondVal = getWord();
            thirdVal = getWord();
            cout << "EQ" << endl;
            return eq(firstVal, secondVal, thirdVal);
        case GT:
            firstVal = getWord();
            secondVal = getWord();
            thirdVal = getWord();
            cout << "GT" << endl;
            return gt(firstVal, secondVal, thirdVal);
        case JMP:
            firstVal = getWord();
            cout << "JMP" << endl;
            
            cout << firstVal << endl;
            return jmp(firstVal);
        case JT:
            firstVal = getWord();
            secondVal = getWord();
            cout << "JT" << endl;
            return jt(firstVal, secondVal);
        case JF:
            firstVal = getWord();
            secondVal = getWord();
            cout << "JF" << endl;
            return jf(firstVal, secondVal);
        case ADD:
            return 1;
        case MULT:
            return 1;
        case MOD:
            return 1;
        case AND:
            return 1;
        case OR:
            return 1;
        case NOT:
            return 1;
        case RMEM:
            return 1;
        case WMEM:
            firstVal = getWord();
            secondVal = getWord();
            cout << "WMEM" << endl;
            return wmem(firstVal, secondVal);
        case CALL:
            return 1;
        case RET:
            return 1;
        case OUT:
            firstVal = getWord();
            cout << (char) firstVal;
            break;
        case IN:
            return 1;
        case NOP:
            break;
        default:
            cout << "ERROR: Unknown Command" << endl;
            return 1;
            break;
    }
    
    
    return 0;
}

int virtualMachine::set(unsigned short reg, unsigned short val) {
    if (reg < 32768 || reg > 32775) {
        cout << "Command Set: Invalid register value" << endl;
        return 1;
    }
    if (val > 32775) {
        cout << "Command Set: Invalid set value" << endl;
        return 1;
    }
    
    if (val < 32768) {
        r[reg - 32768] = val;
    } else {
        r[reg - 32768] = r[val - 32768];
    }
    return 0;
}

int virtualMachine::eq(unsigned short dest, unsigned short val1, unsigned short val2) {
    if (val1 > 32775 || val2 > 32775) {
        cout << "Command Eq: Invalid test values" << endl;
        return 1;
    }
    if (dest > 32775) {
        cout << "Command Eq: Invalid destination value" << endl;
        return 1;
    }
    
    if (val1 < 32768) {
        val1 = r[val1 - 32768];
    }
    if (val2 < 32768) {
        val2 = r[val2 - 32768];
    }
    
    unsigned short destVal = 0;
    if (val1 == val2) {
        destVal = 1;
    }
    
    if (dest > 32767) {
        r[dest - 32768] = destVal;
    } else {
        wmem(dest,destVal);
    }
    
    return 0;
}

int virtualMachine::gt(unsigned short dest, unsigned short val1, unsigned short val2) {
    if (val1 > 32775 || val2 > 32775) {
        cout << "Command Gt: Invalid test values" << endl;
        return 1;
    }
    if (dest > 32775) {
        cout << "Command Gt: Invalid destination value" << endl;
        return 1;
    }
    
    if (val1 >= 32768) {
        val1 = r[val1 - 32768];
    }
    if (val2 >= 32768) {
        val2 = r[val2 - 32768];
    }
    
    unsigned short destVal = 0;
    if (val1 > val2) {
        destVal = 1;
    }
    
    if (dest > 32767) {
        r[dest - 32768] = destVal;
    } else {
        wmem(dest,destVal);
    }
    
    return 0;
}

int virtualMachine::jmp(unsigned short loc) {
    if (loc > 32775) {
        cout << "Command Jmp: Invalid jump location" << endl;
        return 1;
    }
    
    if (loc < 32768) {
        file.seekg(loc << 1);
    } else {
        file.seekg(r[loc - 32768] << 1);
    }
    
    
    return 0;
}

int virtualMachine::jt(unsigned short val, unsigned short dest) {
    if (val > 32775) {
        cout << "Command Jt: Invalid test value" << endl;
        return 1;
    }
    if (val > 32767) {
        val = r[val - 32768];
    }
    
    if (val != 0) {
        return jmp(dest);
    }
    return 0;
}

int virtualMachine::jf(unsigned short val, unsigned short dest) {
    if (val > 32775) {
        cout << "Command Jf: Invalid test value" << endl;
        return 1;
    }
    if (val > 32767) {
        val = r[val - 32768];
    }
    
    if (val == 0) {
        return jmp(dest);
    }
    return 0;
}

int virtualMachine::wmem(unsigned short dest, unsigned short val) {
    if (val > 32775) {
        cout << "Command Wmem: Invalid write value" << endl;
        return 1;
    }
    
    long long start = file.tellg();
    
    file.seekg(((long long) dest)*2);
    
    file.put((char) val & 255);
    file.put((char) val >> 8);
    
    file.seekg(start);
    
    return 0;
}
