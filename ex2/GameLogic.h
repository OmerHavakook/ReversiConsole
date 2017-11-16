/*
 *  Author: lee alima
 *  ID: 313467441
 */

#ifndef EX2_GAMELOGIC_H
#define EX2_GAMELOGIC_H

#include <vector>
#include "Player.h"
#include "Board.h"
#include "HumanPlayer.h"
#include "Screen.h"

class GameLogic {
public:
    /**
     * this is the constructor of the game's board size.
     * @param size - as a number.
     */
    GameLogic(int size);

    /**
     * this is the deconstructor of the game.
     */
    ~GameLogic();

    /**
     * this method checks the scores of the two players and
     * returns the type of the winner.
     * @return char - the type of the winner.
     */
    char returnsWhoWon() const;

    /**
     * this method checks if the player has possible moves.
     * @param type - as the current player's type.
     * @return true - if there are possibe moves and false otherwise.
     */
    bool checksIfMovesArePossible(char type) const;

    /**
     * this method checks if the game if over.
     * @return true if the game is over and false if not.
     */
    bool checksIfGameOver() const;

    /**
     * this method calculates the possible moves of player
     * and returns a vector of the possible moves.
     * @param type - as the current player type.
     * @return vector of string - of the possible moves.
     */
    vector <string> findPossibleCells(char type) const;

    /**
     * this method update the board based on the player's movement.
     * @param row - as the row location.
     * @param col - as the col location.
     * @param type - as the user type.
     */
    void updateBoard( int row, int col, char type) const;

    /**
     * this methos returns the board's game
     * @return
     */
    Board* getBoard();

    /**
     * this method updates the scores.
     * @param type - as the player type.
     */
    void updateScore() const;

    /**
     * this method returns the number of score of player 1.
     * @return int - as the score.
     */
    int getPlayer1Score() const;

    /**
     * this method returns the number of score of player 2.
     * @return int - as the score.
     */
    int getPlayer2Score() const;

    /**
     * this method returns the game's screen object.
     * @return Screen* - as the game's screen.
     */
    Screen* getScreen();

    /**
     * this method chrcks if the player can make the movement he chose.
     * @param s - as string of the point.
     * @param type - as the player's type.
     * @return true - if the movement is possible, false otherwise.
     */
    bool checkPlayerMove(string s,char type) const;

private:
    Player* first_player_;
    Player* second_player_;
    Board* my_board_;
    Screen* my_screen_;

    /**
     * this method make a move in the game
     * @param r - as the row location
     * @param c - as the col location
     * @param t - as the player's type
     * @param rchange - as the change in row
     * @param cchange - as the change in col
     */
    void makeAMove(int r, int c, char t, int rchange, int cchange) const;

    /**
    * this method finds possible cell
     * @param r - as the row location
     * @param c - as the col location
     * @param t - as the player's type
     * @param rchange - as the change in row
     * @param cchange - as the change in col
     * @return "(" - if no cell is possible and the cell's location otherwise
     */
    string findEmptyCellGeneral(int r, int c, char t,
                                int rchange, int cchange) const;

    /**
     * this method converts int to string.
     * @param number - as int type.
     * @return string
     */
    string toString(int number) const;

    /**
     * this method cuts duplication in a vector
     * @param befor_vec - as the vector with the duplication
     * @return new vector
     */
    vector<string> cutDuplicate(vector<string> befor_vec) const;

};

#endif //EX2_GAMELOGIC_H