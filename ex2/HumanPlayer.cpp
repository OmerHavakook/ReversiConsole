/*
 *  Author: lee alima
 *  ID: 313467441
 */

#include <iostream>
#include "HumanPlayer.h"

using namespace std;

HumanPlayer::HumanPlayer(char type,Screen* screen):
        score(2), type(type), player_screen_(screen){
}

char HumanPlayer::getType() const {
    return this->type;
}

int HumanPlayer::getScore() const {
    return this->score;
}

string HumanPlayer::chooseCell() const {
    string user_cell;
    // ask for cell
    this->player_screen_->printString("please choose a cell");
    this->player_screen_->printEndl();
    // scan what the user typed
    cin >> user_cell;
    return user_cell;
}

void HumanPlayer::setScore(int number) {
    this->score = number;
}
