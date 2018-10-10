//*****************************************************************
//
//  Program:     Othello Class Implementation File
//
//  Author:      Joey Cunningham
//  Email:       jc402615@ohio.edu
//
//  Assignment:  Project 6A
//
//  Date:        08.08.18
//
//*****************************************************************

#include <iostream>
#include <string>
#include <cctype>
#include <queue>
#include "Othello.h"
#include "Space.h"

using namespace std;

Othello::Othello(){
    restart(); //sets up a new game
}

void Othello::make_move(const string &move){
    //convert from string to array indices
    int row = int(move[0] - 'A');
    int column = int(move[1] - '1');

    //check for PASS move
    if(move == "PASS"){
        //do not place a piece, simply elevate move number to change turn
        game::make_move(move);
    }
    else{
        //place piece in move specified position based on whose turn it is
        if(main_savitch_14::game::next_mover() == HUMAN){
            board[row][column].set_status(BLACK);
        }
        else{//it's the other player/ computer's turn
            board[row][column].set_status(WHITE);
        }

        //flip pieces (if applicable) in all 8 directions
        if(check_up(move)){
            flip_up(move);
        }
        if(check_down(move)){
            flip_down(move);
        }
        if(check_right(move)){
            flip_right(move);
        }
        if(check_left(move)){
            flip_left(move);
        }
        if(check_up_left(move)){
            flip_up_left(move);
        }
        if(check_up_right(move)){
            flip_up_right(move);
        }
        if(check_down_left(move)){
            flip_down_left(move);
        }
        if(check_down_right(move)){
            flip_down_right(move);
        }

        game::make_move(move); //increments move number
    }
}

void Othello::restart(){
    //set all spaces to empty
    for(int i = 0; i < 8; ++i){ //all rows
        for(int j = 0; j < 8; ++j){ //all columns
            board[i][j].set_status(EMPTY);
        }
    }
    //set initial four pieces
    board[3][3].set_status(WHITE); //D4
    board[3][4].set_status(BLACK); //D5
    board[4][3].set_status(BLACK); //E4
    board[4][4].set_status(WHITE); //E5

    game::restart(); //resets move number to 0
}

void Othello::display_status() const{
    cout << "          1   2   3   4   5   6   7   8" << endl; //header
    cout << "        ┌───┬───┬───┬───┬───┬───┬───┬───┐" << endl << RESET;

    char letter = 'A';
    for(int i = 0; i < 8; ++i){
        cout << "      " << char(letter + i) << " │";
        for(int j = 0; j < 8; ++j){
            cout << " ";
            //fill sqare with appropriate piece
            if(board[i][j].get_status() == BLACK){
                //cout black circle
                cout << CYAN << "◉" << RESET; //iternally player1 is white, but
            }                                 //color matched the board
            else if(board[i][j].get_status() == WHITE){
                //cout white circle
                cout << YELLOW << "◉" << RESET; //iternally opponent is black, but
            }                                   //but color changed to stand out
            else{ //empty space
                cout << " ";
            }
            cout << " │";
        }
        cout << endl;
        //print midline except for final time
        if(i < 7){
            cout << "        ├───┼───┼───┼───┼───┼───┼───┼───┤" << endl;
        }
    }
    //bottom of chart
    cout << "        └───┴───┴───┴───┴───┴───┴───┴───┘" << endl << RESET;
}

bool Othello::is_legal(const string &move) const{
    //check if user tried to PASS
    if(move == "PASS"){
        queue<string> possibleMoves;
        compute_moves(possibleMoves);
        if (possibleMoves.empty()){ //if there are no moves
            return true;
        }
        else{ //if moves are available
            cout << "Psst, what about " << possibleMoves.front() << "?" << endl;
            return false;
        }
    }
    //Check that move is actually on board
    if(move[0] < 'A' || move[0] > 'H'){
        return false;
    }
    if(move[1] < '1' || move[1] > '8'){
        return false;
    }

    //check that move is not already taken
    //convert to array indices
    int row = int(move[0] - 'A');
    int column = int(move[1] - '1');
    if((board[row][column]).get_status() != EMPTY){
        return false;
    }

     //8 directional checks
     return (check_up(move) || check_down(move) || check_right(move) ||
          check_left(move) || check_up_left(move) || check_up_right(move) ||
          check_down_left(move) || check_down_right(move));
}

main_savitch_14::game::who Othello::winning() const{
    //walk through each space
    int whiteChips = 0;
    int blackChips = 0;
    for(int i = 0; i <= 7; ++i){
        for(int j = 0; j <= 7; ++j){
            if(board[i][j].get_status() == BLACK){
                blackChips += 1;
            }
            else if(board[i][j].get_status() == WHITE){
                whiteChips += 1;
            }
            else{
                //dont count any empty space
            }
        }
    }
    if(blackChips > whiteChips){
        return HUMAN;
    }
    else if(whiteChips > blackChips){
        return COMPUTER;
    }
    else{
        return NEUTRAL;
    }
}

int Othello::evaluate() const{
    //walk through every space on board
    int boardValue = 0; //represents how valuable the board is
    for(int i = 0; i <= 7; ++i){
        for(int j = 0; j <= 7; ++j){
            //check for special conditions of i and j
            //corners, weighted 5 times more valuable than a standard piece
            //since they are unflankable and provide key positioning for flanks
            if((i == 0 || i == 7) && (j == 0 || j == 7)){
                if(board[i][j].get_status() == BLACK){
                    boardValue -= 5; //not good for computer
                }
                else if(board[i][j].get_status() == WHITE){
                    boardValue += 5; //good for computer
                }
            }

            //edges, weighted 2 times as heavy since they can only be captured
            //from limited angles and also allow control of center board
            else if((i == 0 || i == 7) || (j == 0 || j == 7)){
                if(board[i][j].get_status() == BLACK){
                    boardValue -= 2; //not good for computer
                }
                else if(board[i][j].get_status() == WHITE){
                    boardValue += 2; //good for computer
                }
            }

            //regular positions, weighted regularly
            else{
                if(board[i][j].get_status() == BLACK){
                    boardValue--; //not good for computer
                }
                else if(board[i][j].get_status() == WHITE){
                    boardValue++; //good for computer
                }
            }

        }
    } //end of nested for loops
    return boardValue;
}



void Othello::compute_moves(std::queue<std::string>& moves) const{
    string moveName;
    for(int i = 0; i <= 7; ++i){ //loop to cycle through the 8 rows
        moveName = "A0";
        moveName[0] += i; //changes move row letter each time
        for(int j = 0; j <= 7; ++j){//loop through column numbers
            moveName[1] += 1; //change the column number each time
            if(is_legal(moveName)){
                moves.push(moveName); //fill the queue with all legal moves
            }
        }
    }
}

main_savitch_14::game* Othello::clone( ) const{
    return new Othello(*this);
}

bool Othello::is_game_over( ){
    queue<string> moveList;
    compute_moves(moveList);
    if(moveList.empty()){ //current player has no moves - check other player
        game::change_move_number(-1); //change to opposite player's turn
        compute_moves(moveList);
        game::change_move_number(1); //change back to correct player's turn
        if(moveList.empty()){//the other player has no moves either
            return true;
        }
        else{ //the other player does have moves
            return false;
        }
    }
    else{ //the current player still has moves at least
        false;
    }
}

bool Othello::check_up(const string &move) const{
    //convert string to indices
    int row = int(move[0] - 'A');
    int column = int(move[1] - '1');

    //if piece is on top or 2nd row, then there is no room to flank above
    if(row == 0 || row == 1){
        return false;
    }

    //determine whose turn it is
    if(main_savitch_14::game::next_mover() == HUMAN){ //black's turn
        //check that piece above is white
        if(board[row - 1][column].get_status() != WHITE){
            return false;
        }
        else{
            //while on the board, continue looking up for another black piece
            row -= 2;
            while(row >= 0 && row <= 7 && column >= 0 && column <= 7){
                if(board[row][column].get_status() == BLACK){//is flankable
                    return true;
                }
                if(board[row][column].get_status() == EMPTY){ //no more pieces to flank
                    return false;
                }
                row -= 1; //keep checking upwards
            }
            //fell off board - no more spaces to check for
            return false;
        }
    }
    else{ //white's turn
        //check that piece above is black
        if(board[row - 1][column].get_status() != BLACK){
            return false;
        }
        else{
            //while on board, continue looking up for another white piece
            row -= 2;
            while(row >= 0 && row <= 7 && column >= 0 && column <= 7){
                if(board[row][column].get_status() == WHITE){//is flankable
                    return true;
                }
                if(board[row][column].get_status() == EMPTY){ //no more pieces to flank
                    return false;
                }
                row -= 1; //keep checking upwards
            }
            //fell off board - no more spaces to check for
            return false;
        }
    }
}

bool Othello::check_down(const string &move) const{
    //convert string to indices
    int row = int(move[0] - 'A');
    int column = int(move[1] - '1');

    //if piece is on bottom or 7th row, then there is no room to flank above
    if(row == 6 || row == 7){
        return false;
    }

    //determine whose turn it is
    if(main_savitch_14::game::next_mover() == HUMAN){ //black's turn
        //check that piece below is white
        if(board[row + 1][column].get_status() != WHITE){
            return false;
        }
        else{
            //while on the board, continue looking down for another black piece
            row += 2;
            while(row >= 0 && row <= 7 && column >= 0 && column <= 7){
                if(board[row][column].get_status() == BLACK){//is flankable
                    return true;
                }
                if(board[row][column].get_status() == EMPTY){ //no more pieces to flank
                    return false;
                }
                row += 1; //keep checking downwards
            }
            //fell off board - no more spaces to check for
            return false;
        }
    }
    else{ //white's turn
        //check that piece below is black
        if(board[row + 1][column].get_status() != BLACK){
            return false;
        }
        else{
            //while on board, continue looking down for another white piece
            row += 2;
            while(row >= 0 && row <= 7 && column >= 0 && column <= 7){
                if(board[row][column].get_status() == WHITE){//is flankable
                    return true;
                }
                if(board[row][column].get_status() == EMPTY){ //no more pieces to flank
                    return false;
                }
                row += 1; //keep checking upwards
            }
            //fell off board - no more spaces to check for
            return false;
        }
    }
}

bool Othello::check_right(const string &move) const{
    //convert string to indices
    int row = int(move[0] - 'A');
    int column = int(move[1] - '1');

    //if piece is on right or 7th column, then there is no room to flank above
    if(column == 6 || column == 7){
        return false;
    }

    //determine whose turn it is
    if(main_savitch_14::game::next_mover() == HUMAN){ //black's turn
        //check that piece to the right is white
        if(board[row][column + 1].get_status() != WHITE){
            return false;
        }
        else{
            //while on the board, continue looking to the right for another black piece
            column += 2;
            while(row >= 0 && row <= 7 && column >= 0 && column <= 7){
                if(board[row][column].get_status() == BLACK){//is flankable
                    return true;
                }
                if(board[row][column].get_status() == EMPTY){ //no more pieces to flank
                    return false;
                }
                column += 1; //keep checking to the right
            }
            //fell off board - no more spaces to check for
            return false;
        }
    }
    else{ //white's turn
        //check that piece to the right is black
        if(board[row][column + 1].get_status() != BLACK){
            return false;
        }
        else{
            //while on board, continue looking to the right for another white piece
            column += 2;
            while(row >= 0 && row <= 7 && column >= 0 && column <= 7){
                if(board[row][column].get_status() == WHITE){//is flankable
                    return true;
                }
                if(board[row][column].get_status() == EMPTY){ //no more pieces to flank
                    return false;
                }
                column += 1; //keep checking to the right
            }
            //fell off board - no more spaces to check for
            return false;
        }
    }
}

bool Othello::check_left(const string &move) const{
    //convert string to indices
    int row = int(move[0] - 'A');
    int column = int(move[1] - '1');

    //if piece is on left or 2th column, then there is no room to flank above
    if(column == 0 || column == 1){
        return false;
    }

    //determine whose turn it is
    if(main_savitch_14::game::next_mover() == HUMAN){ //black's turn
        //check that piece to the left is white
        if(board[row][column - 1].get_status() != WHITE){
            return false;
        }
        else{
            //while on the board, continue looking to the left for another black piece
            column -= 2;
            while(row >= 0 && row <= 7 && column >= 0 && column <= 7){
                if(board[row][column].get_status() == BLACK){//is flankable
                    return true;
                }
                if(board[row][column].get_status() == EMPTY){ //no more pieces to flank
                    return false;
                }
                column -= 1; //keep checking to the right
            }
            //fell off board - no more spaces to check for
            return false;
        }
    }
    else{ //white's turn
        //check that piece to the left is black
        if(board[row][column - 1].get_status() != BLACK){
            return false;
        }
        else{
            //while on board, continue looking to the left for another white piece
            column -= 2;
            while(row >= 0 && row <= 7 && column >= 0 && column <= 7){
                if(board[row][column].get_status() == WHITE){//is flankable
                    return true;
                }
                if(board[row][column].get_status() == EMPTY){ //no more pieces to flank
                    return false;
                }
                column -= 1; //keep checking to the right
            }
            //fell off board - no more spaces to check for
            return false;
        }
    }
}

bool Othello::check_up_left(const string &move) const{
    //convert string to indices
    int row = int(move[0] - 'A');
    int column = int(move[1] - '1');

    //if piece is on top or 2nd row, or on the left or 2nd column
    //then there is no room to flank up-left diagonally
    if(row == 0 || row == 1 || column == 0 || column == 1){
        return false;
    }

    //determine whose turn it is
    if(main_savitch_14::game::next_mover() == HUMAN){ //black's turn
        //check that piece up-left diagonally is white
        if(board[row - 1][column - 1].get_status() != WHITE){
            return false;
        }
        else{
            //while on the board, continue looking up-left diagonally for another black piece
            row -= 2;
            column -= 2;
            while(row >= 0 && row <= 7 && column >= 0 && column <= 7){
                if(board[row][column].get_status() == BLACK){//is flankable
                    return true;
                }
                if(board[row][column].get_status() == EMPTY){ //no more pieces to flank
                    return false;
                }
                row -= 1; //keep checking up-left diagonally
                column -= 1;
            }
            //fell off board - no more spaces to check for
            return false;
        }
    }
    else{ //white's turn
        //check that piece up-left diagonally is black
        if(board[row - 1][column - 1].get_status() != BLACK){
            return false;
        }
        else{
            //while on board, continue looking upleft diagonally for another white piece
            row -= 2;
            column -= 2;
            while(row >= 0 && row <= 7 && column >= 0 && column <= 7){
                if(board[row][column].get_status() == WHITE){//is flankable
                    return true;
                }
                if(board[row][column].get_status() == EMPTY){ //no more pieces to flank
                    return false;
                }
                row -= 1; //keep checking up-left diagonally
                column -= 1;
            }
            //fell off board - no more spaces to check for
            return false;
        }
    }
}

bool Othello::check_up_right(const string &move) const{
    //convert string to indices
    int row = int(move[0] - 'A');
    int column = int(move[1] - '1');

    //if piece is on top or 2nd row, or on the right or 7th column
    //then there is no room to flank up-right diagonally
    if(row == 0 || row == 1 || column == 6 || column == 7){
        return false;
    }

    //determine whose turn it is
    if(main_savitch_14::game::next_mover() == HUMAN){ //black's turn
        //check that piece up-right diagonally is white
        if(board[row - 1][column + 1].get_status() != WHITE){
            return false;
        }
        else{
            //while on the board, continue looking up-right diagonally for another black piece
            row -= 2;
            column += 2;
            while(row >= 0 && row <= 7 && column >= 0 && column <= 7){
                if(board[row][column].get_status() == BLACK){//is flankable
                    return true;
                }
                if(board[row][column].get_status() == EMPTY){ //no more pieces to flank
                    return false;
                }
                row -= 1; //keep checking up-right diagonally
                column += 1;
            }
            //fell off board - no more spaces to check for
            return false;
        }
    }
    else{ //white's turn
        //check that piece up-right diagonally is black
        if(board[row - 1][column + 1].get_status() != BLACK){
            return false;
        }
        else{
            //while on board, continue looking up-right diagonally for another white piece
            row -= 2;
            column += 2;
            while(row >= 0 && row <= 7 && column >= 0 && column <= 7){
                if(board[row][column].get_status() == WHITE){//is flankable
                    return true;
                }
                if(board[row][column].get_status() == EMPTY){ //no more pieces to flank
                    return false;
                }
                row -= 1; //keep checking up-right diagonally
                column += 1;
            }
            //fell off board - no more spaces to check for
            return false;
        }
    }
}

bool Othello::check_down_left(const string &move) const{
    //convert string to indices
    int row = int(move[0] - 'A');
    int column = int(move[1] - '1');

    //if piece is on bottom or 7th row, or on the left or 2nd column
    //then there is no room to flank down-left diagonally
    if(row == 6 || row == 7 || column == 0 || column == 1){
        return false;
    }

    //determine whose turn it is
    if(main_savitch_14::game::next_mover() == HUMAN){ //black's turn
        //check that piece down-left diagonally is white
        if(board[row + 1][column - 1].get_status() != WHITE){
            return false;
        }
        else{
            //while on the board, continue looking down-left diagonally for another black piece
            row += 2;
            column -= 2;
            while(row >= 0 && row <= 7 && column >= 0 && column <= 7){
                if(board[row][column].get_status() == BLACK){//is flankable
                    return true;
                }
                if(board[row][column].get_status() == EMPTY){ //no more pieces to flank
                    return false;
                }
                row += 1; //keep checking down-left diagonally
                column -= 1;
            }
            //fell off board - no more spaces to check for
            return false;
        }
    }
    else{ //white's turn
        //check that piece down-left diagonally is black
        if(board[row + 1][column - 1].get_status() != BLACK){
            return false;
        }
        else{
            //while on board, continue looking down-left diagonally for another white piece
            row += 2;
            column -= 2;
            while(row >= 0 && row <= 7 && column >= 0 && column <= 7){
                if(board[row][column].get_status() == WHITE){//is flankable
                    return true;
                }
                if(board[row][column].get_status() == EMPTY){ //no more pieces to flank
                    return false;
                }
                row += 1; //keep checking down-left diagonally
                column -= 1;
            }
            //fell off board - no more spaces to check for
            return false;
        }
    }
}

bool Othello::check_down_right(const string &move) const{
    //convert string to indices
    int row = int(move[0] - 'A');
    int column = int(move[1] - '1');

    //if piece is on bottom or 7th row, or on the right or 7th column
    //then there is no room to flank down-right diagonally
    if(row == 6 || row == 7 || column == 6 || column == 7){
        return false;
    }

    //determine whose turn it is
    if(main_savitch_14::game::next_mover() == HUMAN){ //black's turn
        //check that piece down-right diagonally is white
        if(board[row + 1][column + 1].get_status() != WHITE){
            return false;
        }
        else{
            //while on the board, continue looking down-right diagonally for another black piece
            row += 2;
            column += 2;
            while(row >= 0 && row <= 7 && column >= 0 && column <= 7){
                if(board[row][column].get_status() == BLACK){//is flankable
                    return true;
                }
                if(board[row][column].get_status() == EMPTY){ //no more pieces to flank
                    return false;
                }
                row += 1; //keep checking down-right diagonally
                column += 1;
            }
            //fell off board - no more spaces to check for
            return false;
        }
    }
    else{ //white's turn
        //check that piece down-right diagonally is black
        if(board[row + 1][column + 1].get_status() != BLACK){
            return false;
        }
        else{
            //while on board, continue looking down-right diagonally for another white piece
            row += 2;
            column += 2;
            while(row >= 0 && row <= 7 && column >= 0 && column <= 7){
                if(board[row][column].get_status() == WHITE){//is flankable
                    return true;
                }
                if(board[row][column].get_status() == EMPTY){ //no more pieces to flank
                    return false;
                }
                row += 1; //keep checking down-right diagonally
                column += 1;
            }
            //fell off board - no more spaces to check for
            return false;
        }
    }
}

void Othello::flip_up(const string &move){
    //convert string to indices
    int row = int(move[0] - 'A');
    int column = int(move[1] - '1');

    //determine whose turn it is
    if(main_savitch_14::game::next_mover() == HUMAN){ //black's turn
        //piece above needs flipped
        board[row - 1][column].flip();

        //keep flipping up until a black piece is encountered
        row -= 2;
        while(board[row][column].get_status() != BLACK){
            board[row][column].flip();
            row -= 1;
        }
    }
    else{ //white's turn
        //piece above needs flipped
        board[row - 1][column].flip();

        //keep flipping up until a white piece is encountered
        row -= 2;
        while(board[row][column].get_status() != WHITE){
            board[row][column].flip();
            row -= 1;
        }
    }
}
void Othello::flip_down(const string &move){
    //convert string to indices
    int row = int(move[0] - 'A');
    int column = int(move[1] - '1');

    //determine whose turn it is
    if(main_savitch_14::game::next_mover() == HUMAN){ //black's turn
        //piece below needs flipped
        board[row + 1][column].flip();

        //keep flipping up until a black piece is encountered
        row += 2;
        while(board[row][column].get_status() != BLACK){
            board[row][column].flip();
            row += 1;
        }
    }
    else{ //white's turn
        //piece below needs flipped
        board[row + 1][column].flip();

        //keep flipping up until a white piece is encountered
        row += 2;
        while(board[row][column].get_status() != WHITE){
            board[row][column].flip();
            row += 1;
        }
    }
}

void Othello::flip_left(const string &move){
    //convert string to indices
    int row = int(move[0] - 'A');
    int column = int(move[1] - '1');

    //determine whose turn it is
    if(main_savitch_14::game::next_mover() == HUMAN){ //black's turn
        //piece to the left needs flipped
        board[row][column - 1].flip();

        //keep flipping up until a black piece is encountered
        column -= 2;
        while(board[row][column].get_status() != BLACK){
            board[row][column].flip();
            column -= 1;
        }
    }
    else{ //white's turn
        //piece to the left needs flipped
        board[row][column - 1].flip();

        //keep flipping up until a white piece is encountered
        column -= 2;
        while(board[row][column].get_status() != WHITE){
            board[row][column].flip();
            column -= 1;
        }
    }
}

void Othello::flip_right(const string &move){
    //convert string to indices
    int row = int(move[0] - 'A');
    int column = int(move[1] - '1');

    //determine whose turn it is
    if(main_savitch_14::game::next_mover() == HUMAN){ //black's turn
        //piece to the right needs flipped
        board[row][column + 1].flip();

        //keep flipping up until a black piece is encountered
        column += 2;
        while(board[row][column].get_status() != BLACK){
            board[row][column].flip();
            column += 1;
        }
    }
    else{ //white's turn
        //piece to the right needs flipped
        board[row][column + 1].flip();

        //keep flipping up until a white piece is encountered
        column += 2;
        while(board[row][column].get_status() != WHITE){
            board[row][column].flip();
            column += 1;
        }
    }
}

void Othello::flip_up_left(const string &move){
    //convert string to indices
    int row = int(move[0] - 'A');
    int column = int(move[1] - '1');

    //determine whose turn it is
    if(main_savitch_14::game::next_mover() == HUMAN){ //black's turn
        //piece up-left diagonally needs flipped
        board[row - 1][column - 1].flip();

        //keep flipping up until a black piece is encountered
        row -= 2;
        column -= 2;
        while(board[row][column].get_status() != BLACK){
            board[row][column].flip();
            row -= 1;
            column -= 1;
        }
    }
    else{ //white's turn
        //piece up-left diagonally needs flipped
        board[row - 1][column - 1].flip();

        //keep flipping up until a white piece is encountered
        row -= 2;
        column -= 2;
        while(board[row][column].get_status() != WHITE){
            board[row][column].flip();
            row -= 1;
            column -= 1;
        }
    }
}

void Othello::flip_up_right(const string &move){
    //convert string to indices
    int row = int(move[0] - 'A');
    int column = int(move[1] - '1');

    //determine whose turn it is
    if(main_savitch_14::game::next_mover() == HUMAN){ //black's turn
        //piece up-right diagonally needs flipped
        board[row - 1][column + 1].flip();

        //keep flipping up until a black piece is encountered
        row -= 2;
        column += 2;
        while(board[row][column].get_status() != BLACK){
            board[row][column].flip();
            row -= 1;
            column += 1;
        }
    }
    else{ //white's turn
        //piece up-right diagonally needs flipped
        board[row - 1][column + 1].flip();

        //keep flipping up until a white piece is encountered
        row -= 2;
        column  += 2;
        while(board[row][column].get_status() != WHITE){
            board[row][column].flip();
            row -= 1;
            column += 1;
        }
    }
}

void Othello::flip_down_left(const string &move){
    //convert string to indices
    int row = int(move[0] - 'A');
    int column = int(move[1] - '1');

    //determine whose turn it is
    if(main_savitch_14::game::next_mover() == HUMAN){ //black's turn
        //piece down-left diagonally needs flipped
        board[row + 1][column - 1].flip();

        //keep flipping up until a black piece is encountered
        row += 2;
        column -= 2;
        while(board[row][column].get_status() != BLACK){
            board[row][column].flip();
            row += 1;
            column -= 1;
        }
    }
    else{ //white's turn
        //piece down-left diagonally needs flipped
        board[row + 1][column - 1].flip();

        //keep flipping up until a white piece is encountered
        row += 2;
        column -= 2;
        while(board[row][column].get_status() != WHITE){
            board[row][column].flip();
            row += 1;
            column -= 1;
        }
    }
}

void Othello::flip_down_right(const string &move){
    //convert string to indices
    int row = int(move[0] - 'A');
    int column = int(move[1] - '1');

    //determine whose turn it is
    if(main_savitch_14::game::next_mover() == HUMAN){ //black's turn
        //piece down-right diagonally needs flipped
        board[row + 1][column + 1].flip();

        //keep flipping up until a black piece is encountered
        row += 2;
        column += 2;
        while(board[row][column].get_status() != BLACK){
            board[row][column].flip();
            row += 1;
            column += 1;
        }
    }
    else{ //white's turn
        //piece down-right diagonally needs flipped
        board[row + 1][column + 1].flip();

        //keep flipping up until a white piece is encountered
        row += 2;
        column += 2;
        while(board[row][column].get_status() != WHITE){
            board[row][column].flip();
            row += 1;
            column += 1;
        }
    }
}

void Othello::set_board(int index1, int index2, char s){
    if(s == 'b'){
        board[index1][index2].set_status(BLACK);
    }
    else if(s == 'w'){
        board[index1][index2].set_status(WHITE);
    }
    else if(s == 'e'){
        board[index1][index2].set_status(EMPTY);
    }
}
