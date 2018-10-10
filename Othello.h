//*****************************************************************
//
//  Program:     Othello Class Interface File
//
//  Author:      Joey Cunningham
//  Email:       jc402615@ohio.edu
//
//  Assignment:  Project 6A
//
//  Date:        08.08.18
//
//*****************************************************************

#ifndef OTHELLO_H
#define OTHELLO_H

#include <string>
#include "Space.h"
#include "game.h"
#include "colors.h"

class Othello : public main_savitch_14::game {
public:
    Othello();
    //*****************************************************************
    //  Function:   Othello
    //  Purpose:    default constuctor
    //  Parameters: none
    //  Pre Conditions: none
    //  Post Conditions: does not return a value
    //*****************************************************************
    void make_move(const std::string &move);
    //*****************************************************************
    //  Function:   make_move
    //  Purpose:    simulates a players move in the game
    //  Parameters: move - the location of the chip to be played
    //  Pre Conditions: the move is legal
    //  Post Conditions: does not return a value
    //*****************************************************************
    void restart();
    //*****************************************************************
    //  Function:   restart
    //  Purpose:    sets up a Game of Othello to be played
    //  Parameters: none
    //  Pre Conditions: the object is valid
    //  Post Conditions: does not return a value
    //*****************************************************************
    void display_status() const;
    //*****************************************************************
    //  Function:   display_status
    //  Purpose:    prints out the board's current state to the screen
    //  Parameters: none
    //  Pre Conditions: the object is valid
    //  Post Conditions: does not return a value
    //*****************************************************************
    bool is_legal(const std::string &move) const;
    //*****************************************************************
    //  Function:   is_legal
    //  Purpose:   determines whether a specified move is valid at a certain
    //             stage in the game
    //  Parameters: move - the move to check validity for
    //  Pre Conditions: the object is valid
    //  Post Conditions: returns true if the move is legal, false if not
    //*****************************************************************
    bool is_game_over();
    //*****************************************************************
    //  Function:   is_game_over
    //  Purpose:    determines whether the game has ended
    //  Parameters: none
    //  Pre Conditions: the boject is valid
    //  Post Conditions: returns true if the game has ended, false otherwise
    //*****************************************************************
    main_savitch_14::game::who winning() const;
    //*****************************************************************
    //  Function:   winning
    //  Purpose:    determines who has won a game
    //  Parameters: none
    //  Pre Conditions: the game is over
    //  Post Conditions: returns the winner of game or if it was a draw
    //*****************************************************************
    int evaluate() const;
    //*****************************************************************
    //  Function:   evaluate
    //  Purpose:    determines how valuable a specific instance of the
    //              board is to the given turn's player
    //  Parameters:none
    //  Pre Conditions:the object is valid
    //  Post Conditions: returns a higher value for valuable computer positions
    //                   and lower values for valuable player positions
    //*****************************************************************
    void compute_moves(std::queue<std::string>& moves) const;
    //*****************************************************************
    //  Function:   compute_moves
    //  Purpose:    finds all available moves available for the current player
    //  Parameters: moves - the queue to store all the possible moves in
    //  Pre Conditions: the queue and object are valid
    //  Post Conditions:does not return a value
    //*****************************************************************
    main_savitch_14::game* clone( ) const;
    //*****************************************************************
    //  Function:   clone
    //  Purpose:    creates a hypothetical game that is a copy of the
    //              current game to use in strategical analysis for the comp
    //  Parameters: none
    //  Pre Conditions: the object is valid
    //  Post Conditions: returns a pointer to a cloned version of the game 
    //*****************************************************************
    bool check_up(const string &move) const;
    //*****************************************************************
    //  Function:   check_up
    //  Purpose:    determines whether or not a given move would result
    //              in the opponent's piece(s) being flanked upwards
    //  Parameters: move - the position on the board to check up from
    //  Pre Conditions: the move has been identified as being on the board
    //                  and the move has not already been taken
    //  Post Conditions: returns true if pieces will be flanked, false otherwise
    //*****************************************************************
    bool check_down(const string &move) const;
    //*****************************************************************
    //  Function:   check_down
    //  Purpose:    determines whether or not a given move would result
    //              in the opponent's piece(s) being flanked downwards
    //  Parameters: move - the position on the board to check down from
    //  Pre Conditions: the move has been identified as being on the board
    //                  and the move has not already been taken
    //  Post Conditions: returns true if pieces will be flanked, false otherwise
    //*****************************************************************
    bool check_right(const string &move) const;
    //*****************************************************************
    //  Function:   check_right
    //  Purpose:    determines whether or not a given move would result
    //              in the opponent's piece(s) being flanked to the right
    //  Parameters: move - the position on the board to check right from
    //  Pre Conditions: the move has been identified as being on the board
    //                  and the move has not already been taken
    //  Post Conditions: returns true if pieces will be flanked, false otherwise
    //*****************************************************************
    bool check_left(const string &move) const;
    //*****************************************************************
    //  Function:   check_left
    //  Purpose:    determines whether or not a given move would result
    //              in the opponent's piece(s) being flanked to the left
    //  Parameters: move - the position on the board to check left from
    //  Pre Conditions: the move has been identified as being on the board
    //                  and the move has not already been taken
    //  Post Conditions: returns true if pieces will be flanked, false otherwise
    //*****************************************************************
    bool check_up_left(const string &move) const;
    //*****************************************************************
    //  Function:   check_up_left
    //  Purpose:    determines whether or not a given move would result
    //              in the opponent's piece(s) being flanked up and left
    //              diagonally
    //  Parameters: move - the position on the board to check up and left from
    //  Pre Conditions: the move has been identified as being on the board
    //                  and the move has not already been taken
    //  Post Conditions: returns true if pieces will be flanked, false otherwise
    //*****************************************************************
    bool check_up_right(const string &move) const;
    //*****************************************************************
    //  Function:   check_up_right
    //  Purpose:    determines whether or not a given move would result
    //              in the opponent's piece(s) being flanked up and right
    //              diagonally
    //  Parameters: move - the position on the board to check up and right from
    //  Pre Conditions: the move has been identified as being on the board
    //                  and the move has not already been taken
    //  Post Conditions: returns true if pieces will be flanked, false otherwise
    //*****************************************************************
    bool check_down_left(const string &move) const;
    //*****************************************************************
    //  Function:   check_down_left
    //  Purpose:    determines whether or not a given move would result
    //              in the opponent's piece(s) being flanked down and left
    //              diagonally
    //  Parameters: move - the position on the board to check down and left from
    //  Pre Conditions: the move has been identified as being on the board
    //                  and the move has not already been taken
    //  Post Conditions: returns true if pieces will be flanked, false otherwise
    //*****************************************************************
    bool check_down_right(const string &move) const;
    //*****************************************************************
    //  Function:   check_down_right
    //  Purpose:    determines whether or not a given move would result
    //              in the opponent's piece(s) being flanked down and right
    //              diagonally
    //  Parameters: move - the position on the board to check down and right from
    //  Pre Conditions: the move has been identified as being on the board
    //                  and the move has not already been taken
    //  Post Conditions: returns true if pieces will be flanked, false otherwise
    //*****************************************************************
    void flip_up(const string &move);
    //*****************************************************************
    //  Function:   flip_up
    //  Purpose:    flips opponents chips when they are flanked from below
    //  Parameters: move - the position to begin flipping from
    //  Pre Conditions: check_up returns true
    //  Post Conditions: does not return a value
    //*****************************************************************
    void flip_down(const string &move);
    //*****************************************************************
    //  Function:   flip_down
    //  Purpose:    flips opponents chips when they are flanked from above
    //  Parameters: move - the position to begin flipping from
    //  Pre Conditions: check_down returns true
    //  Post Conditions: does not return a value
    //*****************************************************************
    void flip_left(const string &move);
    //*****************************************************************
    //  Function:   flip_left
    //  Purpose:    flips opponents chips when they are flanked from the right
    //  Parameters: move - the position to begin flipping from
    //  Pre Conditions: check_left returns true
    //  Post Conditions: does not return a value
    //*****************************************************************
    void flip_right(const string &move);
    //*****************************************************************
    //  Function:   flip_right
    //  Purpose:    flips opponents chips when they are flanked from the left
    //  Parameters: move - the position to begin flipping from
    //  Pre Conditions: check_right returns true
    //  Post Conditions: does not return a value
    //*****************************************************************
    void flip_up_left(const string &move);
    //*****************************************************************
    //  Function:   flip_up_left
    //  Purpose:    flips opponents chips when they are flanked from the
    //              bottom right
    //  Parameters: move - the position to begin flipping from
    //  Pre Conditions: check_up_left returns true
    //  Post Conditions: does not return a value
    //*****************************************************************
    void flip_up_right(const string &move);
    //*****************************************************************
    //  Function:   flip_up_right
    //  Purpose:    flips opponents chips when they are flanked from the
    //              bottom left
    //  Parameters: move - the position to begin flipping from
    //  Pre Conditions: check_up_right returns true
    //  Post Conditions: does not return a value
    //*****************************************************************
    void flip_down_left(const string &move);
    //*****************************************************************
    //  Function:   flip_down_left
    //  Purpose:    flips opponents chips when they are flanked from the
    //              upper right
    //  Parameters: move - the position to begin flipping from
    //  Pre Conditions: check_down_left returns true
    //  Post Conditions: does not return a value
    //*****************************************************************
    void flip_down_right(const string &move);
    //*****************************************************************
    //  Function:   flip_down_right
    //  Purpose:    flips opponents chips when they are flanked from the
    //              upper left
    //  Parameters: move - the position to begin flipping from
    //  Pre Conditions: check_down_right returns true
    //  Post Conditions: does not return a value
    //*****************************************************************
    void set_board(int index1, int index2, char s);
    //*****************************************************************
    //  Function:   set_board
    //  Purpose:    debugging - set board in specific situations
    //  Parameters: index1 - the row index (0-7)
    //              index2 - the column index (0-7)
    //              char - the state to set the space to {b,w,e}
    //  Pre Conditions: none
    //  Post Conditions: does not return a value
    //*****************************************************************
private:

    Space board[8][8];
};



#endif
