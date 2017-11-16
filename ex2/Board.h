/*
 *  Author: lee alima
 *  ID: 313467441
 */

#ifndef EX2_BOARD_H
#define EX2_BOARD_H

#include "Cell.h"
#include "Screen.h"

class Board {
public:
    /**
     * this is the constructor for the object.
     * @param row - as the row location.
     * @param col - as the col location.
     * @param screen - as the game's screen to communicate with the users.
     */
    Board(int row, int col,Screen& screen);

    /**
     * as the deconstructor - to free all the objects that were allocated.
     */
    ~Board();
    
    /**
     * this method return the board's rows number.
     * @return int - the number of rows
     */
    int getRow() const;
    
    /**
     * this method returns the number of cols.
     * @return int - the number of columns.
     */
    int getCol() const;
    
    /**
     * this method prints the board.
     */
    void printBoard() const;
    
    /**
     * this method runs over the board's cells and checks
     * if all cells are full.
     * @return true - if the board is full and false otherwise.
     */
    bool checkAllCellsFull() const;
    
    /**
     * this method returns the cell's type given its location.
     * @param r - as the row's location.
     * @param c - as the col's location.
     * @return char - as the cell's type.
     */
    char returnCellType(int r,int c) const;
    
    /**
     * this method set the cell's type.
     * @param r - as the row's location.
     * @param c - as the col's location.
     * @param t - as the type to change to.
     */
    void setCellInBoard(int r, int c,char t) const;

private:
    int row;
    int col;
    Cell *** my_matrix_;
    Screen & game_screen_;
    /**
     * this method converts int to string.
     * @param number - int.
     * @return string.
     */
    string toStringInt(int number) const ;

    /**
     * this method converts char into string.
     * @param c - as the char.
     * @return string.
     */
    string toStringChar(char c) const;

    /**
     * this method prints a line between rows.
     * @param number - of cols
     */
    void printLine(int number) const;
};

#endif //EX2_BOARD_H