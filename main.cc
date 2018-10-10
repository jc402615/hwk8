//*****************************************************************
//
//  Program:     Application to run Othello Game
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
#include "Othello.h"
#include "game.h"

using namespace std;

int main(){
    //phase 3 opening
    cout << "Welcome to Othello! You will be playing as blue." << endl;
    cout << "\nControls:" << endl;
    cout << "Enter move with letter followed by number e.g. -> C7" << endl;
    cout << "If no moves are available, enter PASS" << endl << endl;

    Othello myGame;
    main_savitch_14::game::who winner = myGame.play();
    if(winner == main_savitch_14::game::HUMAN){
        cout << endl << endl << "Congratulations, Player1, you are the winner!"
             << endl << endl;
    }
    else if(winner == main_savitch_14::game::COMPUTER){
        cout << endl << endl << "Sorry, looks like the computer wins."
             << endl << endl;
    }
    else{
        cout << endl << endl << "It's a draw!" << endl << endl;
    }

    return 0;
}
