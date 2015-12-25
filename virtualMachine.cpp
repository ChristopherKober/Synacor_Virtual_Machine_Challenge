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




void virtualMachine::getChars() {
    ifstream file ("challenge.bin", ios::in|ios::binary);
    char letter;
    file.get(letter);
    cout << (unsigned short) letter << endl;
}



