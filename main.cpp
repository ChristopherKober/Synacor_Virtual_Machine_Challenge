//
//  main.cpp
//  Synacor Virtual Machine Challenge
//
//  Created by Kent on 12/24/15.
//
//

#include <iostream>
#include "virtualMachine.h"

int main(int argc, const char * argv[]) {
    
    virtualMachine x;
    unsigned short y;
    y = x.getWord();
    
    cout << y << endl;
    
    return 0;
}
