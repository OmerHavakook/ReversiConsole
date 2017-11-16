/*
 *  Author: lee alima
 *  ID: 313467441
 */

#ifndef EX2_GAMEFLOW_H
#define EX2_GAMEFLOW_H


#include "GameLogic.h"

/**
 * this class runs the all game.
 */

class GameFlow {
public:
    /**
     * this is the constructor of the class.
     * @param size - as the board size.
     */
    GameFlow(int size1);

    /**
     * this is the deconstructor of the game.
     */
    ~GameFlow();

    /**
     * this method runs the game.
     */
    void play();

private:
    int size;
    GameLogic* game;
    Screen* screen;

    /**
     * this method split the user input to 2 strings;
     * @param user_input - as the user input.
     * @return vector of string.
     */
    vector<string> cutPoint(string user_input) const;

    /**
     * this method converts char to string.
     * @param c - as char to convert.
     * @return string.
     */
    string toStringC(char c) const;

    /**
     * this method converts int to string.
     * @param number - as int.
     * @return string.
     */
    string toStringI(int number) const ;

    /**
     * this method converts points with the computer vals
     * to the matrix val - like (0,0) to (1,1)
     * @param s - as the point
     * @return new string
     */
    string fixPointToUser(vector <string> s) const;

    /**
     * this method converts points with the matrix vals
     * to the computer vals - like (1,1) to (0,0)
     * @param user_choice
     * @return
     */
    string fixPointToCom(string user_choice) const;
};

#endif //EX2_GAMEFLOW_H