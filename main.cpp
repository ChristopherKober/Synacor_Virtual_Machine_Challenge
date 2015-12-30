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
    
    x.run("challenge.bin");
    
    x.r[0] = 0;
    for (int i = 0; i< 10;i++){
        x.set(32768, i);
        cout << x.r[0] << endl;
    }

    return 0;
}
