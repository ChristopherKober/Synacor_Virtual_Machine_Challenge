//
//  stack.cpp
//  Synacor Virtual Machine Challenge
//
//  Created by Kent on 12/29/15.
//
//

#include "stack.h"

stack::stack() {
    head = NULL;
}

void stack::push(unsigned short val) {
    
    stackMember *temp = new stackMember;
    
    temp->data = val;
    temp->next = head;
    
    head = temp;
}

unsigned short stack::pop() {
    if (head) {
        stackMember *temp = head;
        head = head->next;
        
        unsigned short retVal = temp->data;
        delete temp;
        
        return retVal;
    }
    
    return -1;
}

stack::~stack() {
    while (head) {
        pop();
    }
}

stackMember::stackMember() {
    next = NULL;
}