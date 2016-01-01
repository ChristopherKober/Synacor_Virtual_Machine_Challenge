//
//  main.cpp
//  Synacor Virtual Machine Challenge
//
//  Created by Kent on 12/24/15.
//
//

#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;
#include "virtualMachine.h"

int main(int argc, const char * argv[]) {
    virtualMachine x;
    
    x.runProtected("challenge.bin");
    
    return 0;
}
