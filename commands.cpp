//
//  commands.cpp
//  Synacor Virtual Machine Challenge
//
//  Created by Kent on 12/30/15.
//
//

#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;

#include "virtualMachine.h"


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
    
    if (val > 32767) {
        s.push(r[val - 32768]);
    } else {
        s.push(val);
    }
    
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
    
    if (file.eof()){
        file.clear();
        file.seekg(0, ios::beg);
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

int virtualMachine::rmem(unsigned short dest, unsigned short adr) {
    if (dest > 32775) {
        cout << "Command Rmem: Invalid destination" << endl;
        return 1;
    }
    
    if (adr > 32775) {
        cout << "Command Rmem: Invalid memory address" << endl;
        return 1;
    }
    
    if (adr > 32767) {
        adr = r[adr - 32768];
    }
    
    long long start = file.tellg();
    
    jmp(adr);
    unsigned short val = getWord();
    
    if (dest > 32767) {
        r[dest - 32768] = val;
    } else {
        wmem(dest,val);
    }
    
    jmp(start >> 1);
    
    return 0;
}

int virtualMachine::wmem(unsigned short dest, unsigned short val) {
    
    if (val > 32775) {
        cout << "Command Wmem: Invalid write value" << endl;
        return 1;
    }
    
    long long start = file.tellp();
    
    if (dest > 32767) {
        dest = r[dest - 32768];
    }
    
    if (val > 32767) {
        val = r[val - 32768];
    }
    
    file.seekp(dest << 1);
    
    file.put((char) (val & 255));
    file.put((char) ((val >> 8) & 255));
    
    file.seekp(start);
    
    return 0;
}

int virtualMachine::call(unsigned short start) {
    if (start > 32775) {
        cout << "Command Call: Invalid destination address" << endl;
        return 1;
    }
    
    long long val = file.tellg();
    
    if (start > 32767) {
        start = r[start - 32768];
    }
    
    return push(((unsigned short) (val/2))) & jmp(start);
}

int virtualMachine::ret() {
    unsigned short dest = s.pop();
    
    if (dest == (unsigned short) -1) {
        return 1;
    }
    
    return jmp(dest);
}

int virtualMachine::Out(unsigned short chr) {
    cout << (char) chr;
    return 0;
}

int virtualMachine::In(unsigned short dest) {
    if (dest > 32775) {
        cout << "Command In: Invalid memory address" << endl;
        return 1;
    }
    
    if (inBuf == "") {
        getline(cin, inBuf);
        inBuf.append("\n");
    }

    if (dest > 32767) {
        r[dest - 32768] = (unsigned short) inBuf[0];
    } else {
        wmem(dest, (unsigned short) inBuf[0]);
    }
    
    inBuf = inBuf.substr(1);
    
    return 0;
}