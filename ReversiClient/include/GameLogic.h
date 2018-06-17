
#ifndef EX2_GAMELOGIC_H
#define EX2_GAMELOGIC_H

#include <vector>

#include "Board.h"
#include "Player.h"
#include "ConsoleScreen.h"

class Player;

class GameLogic {
public:
    /**
     * this is the constructor of the game's board size.
     * @param size - as the matrix size
     * @param player1 - one player
     * @param player2 - second player
     * @param screen - a screen to show the game to the user
     */
    GameLogic(int size, Player *player1, Player *player2, ConsoleScreen *screen);

    /**
     * this is the destructor of the game.
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
     * @param board - to check if moves are possible
     * @return true - if there are possibe moves and false otherwise.
     */
    bool checksIfMovesArePossible(char type, Board &board);

    /**
     * this method checks if the game if over.
     * @param board - to check if game is over on it
     * @return true if the game is over and false if not.
     */
    bool checksIfGameOver(Board &board);

    /**
     * this method calculates the possible moves of player
     * and returns a vector of the possible moves.
     * @param board - a board to fins possible moves on it
     * @param type - as the current player type.
     * @return vector of string - of the possible moves.
     */
    vector<string> findPossibleCells(Board &board, char type);

    /**
     * this method update the board based on the player's movement.
     * @param row - as the row location.
     * @param col - as the col location.
     * @param type - as the user type.
     * @param board - to update
     */
    Board *updateBoard(int row, int col, char type, Board &board);

    /**
     * this method returns the board's game
     * @return Board* - as the game's board object
     */
    Board *getBoard();

    /**
     * this method  the scores.
     * @param board - to update the players's scores based on the board.
     */
    void updateScore(Board &board);

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
     * this method checks if the player can make the movement he chose.
     * @param user_input - as string of the point.
     * @param type - as the player's type.
     * @param board - to check a movement on it
     * @return true - if the movement is possible, false otherwise.
     */
    bool checkPlayerMove(string user_input, char type, Board &board);

    /**
     * this method changes the current player member
     */
    void changePlayer();

    /**
     * this method returns one of the players base on a char.
     * @param type - as the player type
     * @return Player
     */
    Player *getPlayer(char type);

    /**
     * this method return the difference between the player's score
     * @param b - the board to calculate the difference between the scores
     * @return the difference
     */
    int getScoresDifference(Board &b);

    /**
     * this method changes a number
     * @param number - the number to change
     * @param flag - 1 or -1
     * @param default_number - the number i want to change
     * @param add_number - the number I want to add default_number
     */
    void changeNumber(int &number, int flag, int default_number, int add_number);

    /**
    * this method receive 2 numbers and change them
    * by going over the board
    * @param x_score - as the x score
    * @param o_score - as the o score
    * @param board - as the board
    */
    void calculateScores(int &x_score, int &o_score, Board &board);

private:
    Player *first_player_;
    Player *second_player_;
    Board *my_board_;
    ConsoleScreen *my_screen_;
    char current_Player_;

    /**
     * this method make a move in the game
     * @param r - as the row location
     * @param c - as the col location
     * @param t - as the player's type
     * @param row_change - as the change in row
     * @param col_change - as the change in col
     * @param board - board to make a move on it
     */
    void makeAMove(int r, int c, char t, int row_change,
                   int col_change, Board &board);

    /**
    * this method finds possible cell
     * @param r - as the row location
     * @param c - as the col location
     * @param t - as the player's type
     * @param row_change - as the change in row
     * @param col_change - as the change in col
     * @param board - to fint empty cell on it
     * @return "(" - if no cell is possible and the cell's location otherwise
     */
    string findEmptyCellGeneral(int r, int c, char t, int row_change,
                                int col_change, Board &board);

    /**
     * this method cuts duplication in a vector
     * @param vector_before - as the vector with the duplication
     * @return new vector
     */
    vector<string> cutDuplicate(vector<string> vector_before) const;

};

#endif //EX2_GAMELOGIC_H