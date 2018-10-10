//*****************************************************************
//
//  Program:     Space Implementation File
//
//  Author:      Joey Cunningham
//  Email:       jc402615@ohio.edu
//
//  Assignment:  Project 6A
//
//  Date:        08.08.18
//
//*****************************************************************

#include <string>
#include <iostream>
#include "Space.h"

using namespace std;

Space::Space(){
    status = EMPTY;
}

state Space::get_status() const{
    return status;
}

void Space::set_status(state new_status){
    status = new_status;
}

void Space::flip(){
    if(status == WHITE){
        status = BLACK;
    }
    else if(status == BLACK){
        status = WHITE;
    }
    else{
        //the space is empty - do nothing
    }
}
