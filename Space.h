//*****************************************************************
//
//  Program:     Space class Interface File
//
//  Author:      Joey Cunningham
//  Email:       jc402615@ohio.edu
//
//  Assignment:  Project 6A
//
//  Date:        08.08.18
//
//*****************************************************************

#ifndef SPACE_H
#define SPACE_H

enum state{BLACK, WHITE, EMPTY};

class Space{
public:
    Space();
    //*****************************************************************
    //  Function:   Space
    //  Purpose:    default constructor - sets status to EMPTY
    //  Parameters: none
    //  Pre Conditions: none
    //  Post Conditions: does not return a value
    //*****************************************************************
    state get_status() const;
    //*****************************************************************
    //  Function:   get_status
    //  Purpose:    gets the current status of the space
    //  Parameters: none
    //  Pre Conditions: the object is valid
    //  Post Conditions: returns the state that the piece is in
    //*****************************************************************
    void set_status(state new_status);
    //*****************************************************************
    //  Function:   set_status
    //  Purpose:    sets status to a new state
    //  Parameters: new_status - the state to set status to
    //  Pre Conditions: the object is valid
    //  Post Conditions: does not return a value
    //*****************************************************************
    void flip();
    //*****************************************************************
    //  Function:   flip
    //  Purpose:    if the space is BLACK or WHITE, then the status is
    //              changed to the other color
    //  Parameters: none
    //  Pre Conditions: the object is valid
    //  Post Conditions: does not return a value
    //*****************************************************************
private:
    state status;
};


#endif
