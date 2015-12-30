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
    
    //virtualMachine x;
    
    //x.run("challenge.bin");
    
    stack x;
    for (int i = 0;i<10;i++) {
        x.push(i);
        
    }
    
    for (int i = 0;i<10;i++) {
        cout << x.pop() << endl;
        
    }
    
    return 0;
}
