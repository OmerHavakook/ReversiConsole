#ifndef EX2_CONSOLESCREEN_H
#define EX2_CONSOLESCREEN_H

#include <vector>
#include "Board.h"

class ConsoleScreen {
public:
    /**
     * this is the constructor for the object.
     */
    ConsoleScreen();

    /**
     * destructor for the object
     */
    ~ConsoleScreen();

    /**
     * this method prints string to the console.
     * @param s - as the string to print.
     */
    void printString(string s) const;

    /**
     * this method prints empty line to the console.
     */
    void printEndl() const;

    /**
     * this method prints a board
     * @param board - reference to board
     */
    void printBoard(Board &board) const;

    /**
     * this method prints the player his possible options
     * @param moves - as the vector of options
     * @param computer - true if computer is playing, false otherwise
     * @param type - the player type
     */
    void printPossibleMoves(vector<string> &moves, bool computer, char type) const;

    /**
     * In this method the player is asked for a point
     * @return string - the user choice
     */
    string printPlayerDialog() const;

    /**
     * this method writes the last move in the game
     * @param type - 'X' for 'X' choice and 'O' for 'O' choice
     * @param num1 - row
     * @param num2 - col
     */
    void printPlayerMove(char type, int num1, int num2) const;

    /**
     * this method prints the open menu and ask the user for a
     * game type.
     * @return - the user choice
     */
    int printOpenMenu() const;

    /**
     * If game is over, print the number of points
     * @param flag "=" for tie , otherwise there is a winner
     * @param score_1 - player one score
     * @param score_2 - player two score
     */
    void printGameOver(char flag, int score_1, int score_2) const;

    /**
     * This method converts a point from computer representation to humans'
     * @param s - as the coordinate vector
     * @return string - the point
     */
    string fixPointToUser(vector<int> s) const;

    /**
     * this method converts int to string.
     * @param number - int
     * @return string
     */
    string toStringInt(int number) const;

    /**
     * this method cup point by "," and return a vector of int
     * with the point coordinate
     * @param user_input - as the chosen cell
     * @return vector of int
     */
    vector<int> cutPoint(string user_input) const;

    /**
     * this method prints the turns
     * @param type - as the current player type
     */
    void printPlayerOrder(bool b, char type) const;

    /**
     * this method prints which player has no moves.
     * @param type - player type
     */
    void printNoMoveOrder(char type) const;

    /**
     * this method calls printSubMenu and by the return value returns
     * a pairs : the first in the pair is the mission with it's args
     * and the second is the name of the game(args)
     * @return pair
     */
    pair<string, string> handleSubMenu();

private:
    /**
     * this method prints the user a sub menu (for the choice of
     * playing with a remote player)
     * @return int - the user choice
     */
    int printSubMenu();

    /**
     * this method receives data from the user about what kind
     * of game he wants to play and returns is.
     * @return string - the user game choice
     */
    string userChoiceOfGame();
};

#endif //EX2_CONSOLESCREEN_H