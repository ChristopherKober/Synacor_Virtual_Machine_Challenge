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
    
    return (((unsigned short) (firstByte)) & 255) + ((((unsigned short) secondByte) << 8) & ~(255));
}

void virtualMachine::run(string f) {
    file = fstream(f, fstream::in | fstream::out | ios::binary);
    
    unsigned short val;
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
            //cout << "SET" << endl;
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
            //cout << "EQ" << endl;
            return eq(firstVal, secondVal, thirdVal);
        case GT:
            firstVal = getWord();
            secondVal = getWord();
            thirdVal = getWord();
            //cout << "GT" << endl;
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
            return 1;
        case WMEM:
            firstVal = getWord();
            secondVal = getWord();
            //cout << "WMEM" << endl;
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

int virtualMachine::push(unsigned short val) {
    if (val > 32775) {
        cout << "Command Push: Invalid input value" << endl;
        return 1;
    }
    s.push(val);
    
    return 0;
}

int virtualMachine::pop(unsigned short dest) {
    if (dest > 32775) {
        cout << "Command Pop: Invalid destination value" << endl;
        return 1;
    }
    
    unsigned short retVal = s.pop();
    
    if (retVal == (unsigned short) -1) {
        cout << "Command Pop: Stack is Empty" << endl;
        return 1;
    }
    
    if (dest > 32767) {
        r[dest - 32768] = retVal;
    } else {
        wmem(dest, retVal);
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
    
    if (val1 > 32767) {
        val1 = r[val1 - 32768];
    }
    if (val2 > 32767) {
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
    
    if (val1 > 32767) {
        val1 = r[val1 - 32768];
    }
    if (val2 > 32767) {
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
        file.seekg((loc << 1) );
    } else {
        file.seekg((r[loc - 32768] << 1) );
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

int virtualMachine::add(unsigned short dest, unsigned short val1, unsigned short val2) {
    if (dest > 32775) {
        cout << "Command Add: Invalid destination" << endl;
        return 1;
    }
    
    if (val1 > 32775 || val2 > 32775) {
        cout << "Command Add: Invalid add value" << endl;
        return 1;
    }
    
    if (val1 > 32767) {
        val1 = r[val1 - 32768];
    }
    if (val2 > 32767) {
        val2 = r[val2 -  32768];
    }
    
    if (dest > 32767) {
        r[dest - 32768] = (val1 + val2) % 32768;
    } else {
        return wmem(dest, (val1 + val2) % 32768);
    }
    return 0;
}

int virtualMachine::mult(unsigned short dest, unsigned short val1, unsigned short val2) {
    if (dest > 32775) {
        cout << "Command Mult: Invalid destination" << endl;
        return 1;
    }
    
    if (val1 > 32775 || val2 > 32775) {
        cout << "Command Mult: Invalid multiply value" << endl;
        return 1;
    }
    
    if (val1 > 32767) {
        val1 = r[val1 - 32768];
    }
    if (val2 > 32767) {
        val2 = r[val2 -  32768];
    }
    
    unsigned int retVal = val1 * val2;
    
    if (dest > 32767) {
        r[dest - 32768] = (unsigned short) (retVal % 32768);
    } else {
        return wmem(dest, (unsigned short) (retVal % 32768));
    }
    return 0;
}

int virtualMachine::mod(unsigned short dest, unsigned short val1, unsigned short val2) {
    if (dest > 32775) {
        cout << "Command Mod: Invalid destination" << endl;
        return 1;
    }
    
    if (val1 > 32775 || val2 > 32775) {
        cout << "Command Mod: Invalid input value" << endl;
        return 1;
    }
    
    if (val1 > 32767) {
        val1 = r[val1 - 32768];
    }
    if (val2 > 32767) {
        val2 = r[val2 -  32768];
    }
    
    if (dest > 32767) {
        r[dest - 32768] = (val1 % val2);
    } else {
        return wmem(dest, (val1 % val2));
    }
    return 0;
}

int virtualMachine::And(unsigned short dest, unsigned short val1, unsigned short val2) {
    if (dest > 32775) {
        cout << "Command And: Invalid destination" << endl;
        return 1;
    }
    
    if (val1 > 32775 || val2 > 32775) {
        cout << "Command And: Invalid input value" << endl;
        return 1;
    }
    
    if (val1 > 32767) {
        val1 = r[val1 - 32768];
    }
    if (val2 > 32767) {
        val2 = r[val2 -  32768];
    }
    
    if (dest > 32767) {
        r[dest - 32768] = (val1 & val2);
    } else {
        return wmem(dest, (val1 & val2));
    }
    return 0;
}

int virtualMachine::Or(unsigned short dest, unsigned short val1, unsigned short val2) {
    if (dest > 32775) {
        cout << "Command Or: Invalid destination" << endl;
        return 1;
    }
    
    if (val1 > 32775 || val2 > 32775) {
        cout << "Command Or: Invalid input value" << endl;
        return 1;
    }
    
    if (val1 > 32767) {
        val1 = r[val1 - 32768];
    }
    if (val2 > 32767) {
        val2 = r[val2 -  32768];
    }
    
    if (dest > 32767) {
        r[dest - 32768] = (val1 | val2);
    } else {
        return wmem(dest, (val1 | val2));
    }
    return 0;
}

int virtualMachine::Not(unsigned short dest, unsigned short val) {
    if (dest > 32775) {
        cout << "Command Not: Invalid destination" << endl;
        return 1;
    }
    
    if (val > 32775) {
        cout << "Command Not: Invalid input value" << endl;
        return 1;
    }
    
    if (val > 32767) {
        val = r[val - 32768];
    }
    
    if (dest > 32767) {
        r[dest - 32768] = (~val & 32767);
    } else {
        return wmem(dest, (~val & 32767));
    }
    return 0;
}

int virtualMachine::wmem(unsigned short dest, unsigned short val) {
    
    cout << "wmem called" << endl;
    
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
