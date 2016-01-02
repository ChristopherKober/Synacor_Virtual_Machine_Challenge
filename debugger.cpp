//
//  debugger.cpp
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

#define RUN_MODE 0
#define STEP_MODE 1


void virtualMachine::debug(string f){
    
    file = fstream(f, fstream::in | fstream::out | ios::binary);
    
    string command = "";
    
    cout << "Welcome to the Virtual Machine debugger:" << endl << endl;
    
    while (command != "run"){
        cout << "> ";
        getline(cin, command);
        if (command[0] == 'b' && command[1] == ' ') {
            addBreak(command.substr(2));
        } else if (command.substr(0,3) == "rb "){
            removeBreak(command.substr(3));
        } else if (command == "pb") {
            printBreaks();
        } else if (command == "cb") {
            clearBreaks();
        } else if (command == "help") {
            printHelp();
        } else if (command == "q"){
            return;
        } else if (command == "run") {
            continue;
        } else if (command == "ps") {
            s.printStack();
        } else if (command != "") {
            cout << "Unknown debugger command. Type help for more information" << endl;
        }
    }
    
    int mode = RUN_MODE;
    unsigned short val = 0;
    
    int running = 0;
    while (running == 0) {
        if (mode == RUN_MODE) {
            
            unsigned short adr = getAddress();
            
            for (int i = 0; i < numLineBreaks;i++){
                if (lineBreaks[i] == 0) {
                    continue;
                } else if (lineBreaks[i] == adr) {
                    mode = STEP_MODE;
                    break;
                }
            }
            
            if (mode == STEP_MODE){
                continue;
            }
            
            val = getWord();
            if (opBreaks[val] == 1) {
                mode = STEP_MODE;
                jmp(getAddress() - 1);
                continue;
            }
            running = interpretCommand(val);
        } else {
            command = "";
            
            while (command != "ni") {
                cout << "> ";
                getline(cin, command);
                if (command[0] == 'b' && command[1] == ' ') {
                    addBreak(command.substr(2));
                } else if (command.substr(0,3) == "rb "){
                    removeBreak(command.substr(3));
                } else if (command == "pb") {
                    printBreaks();
                } else if (command == "cb") {
                    clearBreaks();
                } else if (command == "disas") {
                    printCommands("20");
                } else if (command.substr(0,6) == "disas ") {
                    printCommands(command.substr(6));
                } else if (command == "ir") {
                    dumpRegisters();
                } else if (command == "help") {
                    printHelp();
                } else if (command.substr(0,4) == "jmp ") {
                    debugJmp(command.substr(4));
                } else if (command == "q"){
                    return;
                } else if (command == "run") {
                    mode = RUN_MODE;
                    break;
                } else if (command == "ni") {
                    continue;
                } else if (command == "ps") {
                    s.printStack();
                } else if (command != "") {
                    cout << "Unknown debugger command. Type help for more information" << endl;
                }
            }
            interpretCommand(getWord());
        }
    }
    return;
}


void virtualMachine::debugProtected(string f){
    remove("curr.bin");
    
    ifstream  src(f, ios::binary);
    ofstream  dst("curr.bin", std::ios::binary);
    
    dst << src.rdbuf();
    
    src.close();
    dst.close();
    
    file = fstream("curr.bin", fstream::in | fstream::out | ios::binary);
    
    string command = "";
    
    cout << "Welcome to the Virtual Machine debugger:" << endl << endl;
    
    while (command != "run"){
        cout << "> ";
        getline(cin, command);
        if (command[0] == 'b' && command[1] == ' ') {
            addBreak(command.substr(2));
        } else if (command.substr(0,3) == "rb "){
            removeBreak(command.substr(3));
        } else if (command == "pb") {
            printBreaks();
        } else if (command == "cb") {
            clearBreaks();
        } else if (command == "help") {
            printHelp();
        } else if (command == "q"){
            return;
        } else if (command == "run") {
            continue;
        } else if (command == "ps") {
            s.printStack();
        } else if (command != "") {
            cout << "Unknown debugger command. Type help for more information" << endl;
        }
    }
    
    int mode = RUN_MODE;
    unsigned short val = 0;
    
    int running = 0;
    while (running == 0) {
        if (mode == RUN_MODE) {
            
            unsigned short adr = getAddress();
            
            for (int i = 0; i < numLineBreaks;i++){
                if (lineBreaks[i] == 0) {
                    continue;
                } else if (lineBreaks[i] == adr) {
                    mode = STEP_MODE;
                    break;
                }
            }
            
            if (mode == STEP_MODE){
                continue;
            }
            
            val = getWord();
            if (opBreaks[val] == 1) {
                mode = STEP_MODE;
                jmp(getAddress() - 1);
                continue;
            }
            running = interpretCommand(val);
        } else {
            command = "";
            
            while (command != "ni") {
                cout << "> ";
                getline(cin, command);
                if (command[0] == 'b' && command[1] == ' ') {
                    addBreak(command.substr(2));
                } else if (command.substr(0,3) == "rb "){
                    removeBreak(command.substr(3));
                } else if (command == "pb") {
                    printBreaks();
                } else if (command == "cb") {
                    clearBreaks();
                } else if (command == "disas") {
                    printCommands("20");
                } else if (command.substr(0,6) == "disas ") {
                    printCommands(command.substr(6));
                } else if (command == "ir") {
                    dumpRegisters();
                } else if (command == "help") {
                    printHelp();
                } else if (command.substr(0,4) == "jmp ") {
                    debugJmp(command.substr(4));
                } else if (command == "q"){
                    return;
                } else if (command == "run") {
                    mode = RUN_MODE;
                    break;
                } else if (command == "ni") {
                    continue;
                } else if (command == "ps") {
                    s.printStack();
                } else if (command == "pa"){
                    cout << getAddress() << endl;
                } else if (command != "") {
                    cout << "Unknown debugger command. Type help for more information" << endl;
                }
            }
            interpretCommand(getWord());
        }
    }
    return;
}

void virtualMachine::addBreak(string op) {
    
    if ( (((int)op[0]) >= ((int) '0')) &&   (((int)op[0]) <= ((int) '9')) ) {
        
        int line;
        
        try {
            line = stoi(op);
        } catch (exception& e) {
            cout << "Invalid line number. No breakpoint set" << endl;
            return;
        }
        
        if (line == 0) {
            cout << "Cannot create break for line 0" << endl;
            return;
        }
        
        if (numLineBreaks == 50) {
            cout << "There are too many line breaks" << endl;
        } else {
            lineBreaks[numLineBreaks] = line;
            numLineBreaks++;
            
            cout << "Breakpoint set for line " << op << endl;
        }
        return;
    }
    
    if (op == "halt"){
        opBreaks[0] = 1;
    } else if (op == "set"){
        opBreaks[1] = 1;
    } else if (op == "push"){
        opBreaks[2] = 1;
    } else if (op == "pop"){
        opBreaks[3] = 1;
    } else if (op == "eq"){
        opBreaks[4] = 1;
    } else if (op == "gt"){
        opBreaks[5] = 1;
    } else if (op == "jmp"){
        opBreaks[6] = 1;
    } else if (op == "jt"){
        opBreaks[7] = 1;
    } else if (op == "jf"){
        opBreaks[8] = 1;
    } else if (op == "add"){
        opBreaks[9] = 1;
    } else if (op == "mult"){
        opBreaks[10] = 1;
    } else if (op == "mod"){
        opBreaks[11] = 1;
    } else if (op == "and"){
        opBreaks[12] = 1;
    } else if (op == "or"){
        opBreaks[13] = 1;
    } else if (op == "not"){
        opBreaks[14] = 1;
    } else if (op == "rmem"){
        opBreaks[15] = 1;
    } else if (op == "wmem"){
        opBreaks[16] = 1;
    } else if (op == "call"){
        opBreaks[17] = 1;
    } else if (op == "ret"){
        opBreaks[18] = 1;
    } else if (op == "out"){
        opBreaks[19] = 1;
    } else if (op == "in") {
        opBreaks[20] = 1;
    } else if (op == "r"){
        clearBreaks();
        cout << "Breakpoints have been reset" << endl;
        return;
    } else {
        cout << "Unknown Op, no breakpoint set" << endl;
        return;
    }
    
    cout << "Breakpoint set for command " << op << endl;
}

void virtualMachine::removeBreak(string op) {
    if ( (((int)op[0]) >= ((int) '0')) &&   (((int)op[0]) <= ((int) '9')) ) {
        
        int line;
        
        try {
            line = stoi(op);
        } catch (exception& e) {
            cout << "Invalid line number. No breakpoint removed" << endl;
            return;
        }
        
        if (line == 0) {
            cout << "Cannot remove break for line 0" << endl;
            return;
        }
        
        int i = 0;
        
        while ( i < numLineBreaks){
            if (lineBreaks[i] == line) {
                for (int j = i; j < numLineBreaks - 1;j++) {
                    lineBreaks[j] = lineBreaks[j+1];
                }
                numLineBreaks--;
                continue;
            } else {
                i++;
            }
        }
        
        cout << "Breakpoint removed for line " << op << endl;
        
        return;
    }
    
    if (op == "halt"){
        opBreaks[0] = 0;
    } else if (op == "set"){
        opBreaks[1] = 0;
    } else if (op == "push"){
        opBreaks[2] = 0;
    } else if (op == "pop"){
        opBreaks[3] = 0;
    } else if (op == "eq"){
        opBreaks[4] = 0;
    } else if (op == "gt"){
        opBreaks[5] = 0;
    } else if (op == "jmp"){
        opBreaks[6] = 0;
    } else if (op == "jt"){
        opBreaks[7] = 0;
    } else if (op == "jf"){
        opBreaks[8] = 0;
    } else if (op == "add"){
        opBreaks[9] = 0;
    } else if (op == "mult"){
        opBreaks[10] = 0;
    } else if (op == "mod"){
        opBreaks[11] = 0;
    } else if (op == "and"){
        opBreaks[12] = 0;
    } else if (op == "or"){
        opBreaks[13] = 0;
    } else if (op == "not"){
        opBreaks[14] = 0;
    } else if (op == "rmem"){
        opBreaks[15] = 0;
    } else if (op == "wmem"){
        opBreaks[16] = 0;
    } else if (op == "call"){
        opBreaks[17] = 0;
    } else if (op == "ret"){
        opBreaks[18] = 0;
    } else if (op == "out"){
        opBreaks[19] = 0;
    } else if (op == "in") {
        opBreaks[20] = 0;
    } else if (op == "r"){
        clearBreaks();
        cout << "Breakpoints have been reset" << endl;
        return;
    } else {
        cout << "Unknown Op, no breakpoint removed" << endl;
        return;
    }
    
    cout << "Breakpoint removed for command " << op << endl;
}

void virtualMachine::printBreaks() {
    cout << "Breakpoints set for following commands" << endl;
    for (int i = 0; i < 22;i++) {
        if (opBreaks[i] == 1) {
            cout << "    " << getString(i) << endl;
        }
    }
    cout << "Breakpoints set for following lines" << endl;
    for (int i=0;i<numLineBreaks;i++) {
        cout << "    " << (int)lineBreaks[i] << endl;
    }
}

void virtualMachine::clearBreaks() {
    for (int i = 0; i<22;i++) {
        opBreaks[i] = 0;
    }
    
    for (int i = 0; i<50;i++) {
        lineBreaks[i] = 0;
    }
    
    numLineBreaks = 0;
}

void virtualMachine::printCommands(string num){
    unsigned short start = getAddress();
    
    int len;
    
    try {
        len = stoi(num);
    } catch (exception& e) {
        cout << "Invalid number" << endl;
        return;
    }
    
    unsigned short cmd;
    unsigned short args[3];
    for (int i = 0; i < len; i++) {
        printf( "%05i", getAddress());
        cout << ": ";
        cmd = getWord();
        printf("%6i",cmd);
        unsigned short temp;
        for (int j = 0; j < numArgs(cmd);j++){
            temp = getWord();
            printf("%6i",temp);
            args[j] = temp;
        }
        
        for (int j = 0; j < (3 - numArgs(cmd));j++){
            cout << "      ";
        }
        cout << " | ";
        
        string c = getString(cmd);
        printf("%6s",c.c_str());
        
        for (int j = 0; j < numArgs(cmd);j++) {
            if (args[j] > 32767) {
                printf("    r%1i",args[j]- 32768);
            } else {
                printf("%6i",args[j]);
            }
        }
        
        cout << endl;
    }
    
    jmp(start);
    
}

void virtualMachine::dumpRegisters() {
    for (int i = 0; i < 8; i++){
        cout << "r" << i << ": ";
        printf("%6i\n",r[i]);
    }
}

void virtualMachine::printHelp() {
    cout << "List of all debugger commands:" << endl;
    cout << "    run: Will execute the binary file" << endl;
    cout << "    b [line number/command]: Will add a breakpoint at specified destination" << endl;
    cout << "    rb [line number/command]: Will remove specific breakpoint" << endl;
    cout << "    pb: Will print all current breaks" << endl;
    cout << "    cb: Will clear all current breaks" << endl;
    cout << "    disas [number of commands (optional)]: Will print out next number of commands" << endl;
    cout << "    ir: Will print out values of each register" << endl;
    cout << "    ps: Will print out the current stack" << endl;
    cout << "    jmp: Will jump to specific address" << endl;
    cout << "    ni: Will step one command forward in program" << endl;
    cout << "    q: Will quit out of program" << endl;
    
    return;
}

void virtualMachine::debugJmp(string adr) {
    unsigned short dest;
    try {
        dest = stoi(adr);
    } catch (exception& e) {
        cout << "Invalid jump address, no jump was performed" << endl;
        return;
    }
    jmp(dest);
}

int virtualMachine::numArgs(unsigned short cmd) {
    if (cmd == 0 || cmd == 18 || cmd == 21) {
        return 0;
    } else if (cmd == 2 || cmd == 3 || cmd == 6 || cmd == 17 || cmd == 19 || cmd == 20) {
        return 1;
    } else if (cmd == 4 || cmd == 5 || cmd == 9 || cmd == 10 || cmd == 11 || cmd == 12 || cmd == 13) {
        return 3;
    }
    return 2;
}

string virtualMachine::getString(unsigned short cmd){
    switch (cmd) {
        case 0:
            return "halt";
        case 1:
            return "set";
        case 2:
            return "push";
        case 3:
            return "pop";
        case 4:
            return "eq";
        case 5:
            return "gt";
        case 6:
            return "jmp";
        case 7:
            return "jt";
        case 8:
            return "jf";
        case 9:
            return "add";
        case 10:
            return "mult";
        case 11:
            return "mod";
        case 12:
            return "and";
        case 13:
            return "or";
        case 14:
            return "not";
        case 15:
            return "rmem";
        case 16:
            return "wmem";
        case 17:
            return "call";
        case 18:
            return "ret";
        case 19:
            return "out";
        case 20:
            return "in";
        case 21:
            return "noop";
    }
    return "n/a";
}