//
// Created by lee on 05/11/17.
//

#ifndef EX2_DSA_H
#define EX2_DSA_H


/*
 *  Author: lee alima
 *  ID: 313467441
 */
#include <iostream>
#include <cstdlib>
#include <sstream>
#include "GameFlow.h"

GameFlow::GameFlow(int size):size(size){
    // creating a new game
    this->game = new GameLogic(size);
    this->screen = game->getScreen();
}

GameFlow::~GameFlow() {
    delete game;
}

void GameFlow::play() {
    // printing the board
    this->game->getBoard()->printBoard();
    char current_player = 'X';
    char other_player = 'O';
    string user_choice;
    string choice_to_compare;
    // as long as the game is not over
    while (!this->game->checksIfGameOver()){
        this->screen->printString(this->toStringC(current_player)
                                  + ": It's your move!");
        this->screen->printEndl();
        // if the player can make a move
        if (this->game->checksIfMovesArePossible(current_player)) {
            // print the player's options
            this->screen->printString("Your possible moves are: ");
            // creating a vector of the options
            vector<string> options =
                    this->game->findPossibleCells(current_player);
            vector<string>::iterator it;
            // going over the options and printing them
            for (it = options.begin(); it != options.end(); ++it) {
                vector <string> string_change = this->cutPoint(*it);
                this->screen->printString(this->fixPointToUser(string_change));
                if (it != options.end() - 1) {
                    this->screen->printString(",");
                }
            }
            this->screen->printEndl();
            // ask the user for a point
            this->screen->printString("Please, enter your move row,col:");
            cin >> user_choice;
            choice_to_compare = this->fixPointToCom(user_choice) ;
            // checking the player's move, if it's illegal then asks again
            while (!this->game->checkPlayerMove(choice_to_compare,
                                                current_player)) {
                cin >> user_choice;
                choice_to_compare = this->fixPointToCom(user_choice) ;
            }
            // split the input
            vector <string> s = this->cutPoint(user_choice);
            string front_number = s.front();
            string back_number = s.back();
            // converts the string into two numbers
            int first_number = atoi( front_number.c_str());
            int second_number = atoi(back_number.c_str()) ;
            // updating the board and printing it
            this->game->updateBoard(first_number-1,second_number-1,other_player);
            this->game->getBoard()->printBoard();
        }
        else { // if no move is possible
            this->screen->printString("No moves are possible for you");
            this->screen->printEndl();
        }
        if (current_player == 'X'){
            current_player = 'O';
            other_player = 'X';
        }
        else {
            current_player = 'X';
            other_player = 'O';
        }

    }
    // when game is over , if it's a tie
    if (this->game->returnsWhoWon() == '='){
        this->screen->printString(
                "It's a tie!, each player got " +
                this->toStringI(this->game->getPlayer1Score())
                + " points.");
        this->screen->printEndl();
        return;
    }
    // if it's not a tie, print a message of the winner and the player's points
    this->screen->printString("Game Is Over, the winner is: " +
                              toStringC(this->game->returnsWhoWon()));
    this->screen->printEndl();
    this->screen->printString("X: You got " + this->toStringI
            (this->game->getPlayer1Score()) + " points");
    this->screen->printEndl();
    this->screen->printString("O: You got " + this->toStringI
            (this->game->getPlayer2Score()) + " points");
}

vector<string> GameFlow::cutPoint(string user_input) const {
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do {
        // split by ,
        pos = user_input.find(",", prev);
        if (pos == string::npos) pos = user_input.length();
        string token = user_input.substr(prev, pos - prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + 1;
    } while (pos < user_input.length() && prev < user_input.length());
    // return the point value
    return tokens;
}

string GameFlow::toStringI(int number) const {
    stringstream ss;
    ss << number;
    string str = ss.str();
    return str;
}

string GameFlow::toStringC(char c) const {
    stringstream ss;
    string target;
    ss << c;
    ss >> target;
    return target;
}

string GameFlow::fixPointToUser(vector <string> s) const {
    // saving the "numbers"
    char front_number1 = s.front()[1];
    char back_number1 = s.back()[0];
    // converts the string into two numbers
    int first_number = front_number1 - '0';
    int first_number_up = first_number + 1;
    int second_number = back_number1 - '0' ;
    int second_number_up = second_number +1;
    return "(" + this->toStringI(first_number_up)
    + "," + this->toStringI(second_number_up) + ")";
}

string GameFlow::fixPointToCom(string user_choice) const {
    // split the point by ","
    vector <string> s = this->cutPoint(user_choice);
    string front_number = s.front();
    string back_number = s.back();
    // converts the string into two numbers (-1 to fit array show)
    int first_number = atoi( front_number.c_str()) -1 ;
    int second_number = atoi(back_number.c_str()) - 1;
    return "(" +  this->toStringI(first_number)+ ","
           + this->toStringI(second_number) + ")";
}

#endif //EX2_DSA_H