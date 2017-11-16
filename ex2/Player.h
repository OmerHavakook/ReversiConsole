/*
 *  Author: lee alima
 *  ID: 313467441
 */

#ifndef EX2_PLAYER_H
#define EX2_PLAYER_H

#include <string>
#include "Screen.h"

using namespace std;

/**
 * this is an abstract class - in the way, different
 * kinds of players can be created.
 */
class Player {
public:
    /**
     * this method return the player type.
     * @return char - as the player's type.
     */
    virtual char getType() const = 0;

    /**
     * this method return the player score.
     * @return int - as the player's score.
     */
    virtual int getScore() const = 0;

    /**
     * this method asks the user for a cell and returns it.
     * @return string - as the cell's location.
     */
    virtual string chooseCell() const = 0;

    /**
     * this method sets the player's score
     * @param number - as the score number
     */
    virtual void setScore(int number) = 0;



protected:
    char type;
    int score;
    Screen* player_screen_;
};


#endif //EX2_PLAYER_H