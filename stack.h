//
//  stack.hpp
//  Synacor Virtual Machine Challenge
//
//  Created by Kent on 12/29/15.
//
//

#include <stdio.h>

class stackMember;

class stack {
public:
    stack();
    void push(unsigned short val);
    unsigned short pop();
    ~stack();
    
private:
    stackMember *head;
};

class stackMember {
public:
    stackMember();
    friend class stack;
private:
    unsigned short data;
    stackMember *next;
};