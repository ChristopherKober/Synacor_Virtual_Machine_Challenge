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



virtualMachine::virtualMachine() {
    //ifstream temp("challenge.bin", ios::in|ios::binary);
    file = ifstream("challenge.bin", ios::in|ios::binary);
}


unsigned short virtualMachine::getWord() {
    if (file.eof()) {
        return -1;
    }
    char firstByte;
    char secondByte;
    file.get(firstByte);
    file.get(secondByte);
    unsigned short retval;
    //retval = (((unsigned short) (firstByte) << 8)) + ((unsigned short) secondByte);
    retval = (((unsigned short) (firstByte))) + (((unsigned short) secondByte) << 8);
    return retval;
}



