/*
 *  Author: lee alima
 *  ID: 313467441
 */

#include "Board.h"
#include <iostream>
#include <sstream>

using namespace std;

Board::Board(int row,int col,Screen& screen):
        row(row), col(col), game_screen_(screen) {
    int mid_row = row/2 -1;
    int mid_col = col/2 -1;
    // creating the matrix
    this->my_matrix_ = new Cell**[row];
    // creating the rows
    for (int i = 0;i<row;i++){
        this->my_matrix_[i] = new Cell*[col];
    }
    // creating the all matrix
    for (int j = 0; j < row; j++) {
        for (int z = 0; z < col; z++) {
            this->my_matrix_[j][z] = new Cell('E');
        }
    }
    // initialize the 4 inner cells.
    this->my_matrix_[mid_row][mid_col]->setType('O');
    this->my_matrix_[mid_row][mid_col+1]->setType('X');
    this->my_matrix_[mid_row+1][mid_col+1]->setType('O');
    this->my_matrix_[mid_row+1][mid_col]->setType('X');
}

Board::~Board() {
    // freeing all of the cells
    for (int j = 0; j < row; j++) {
        for (int z = 0; z<col; z++){
            delete my_matrix_[j][z];
        }
    }
    // freeing all of the rows
    for (int i = 0; i<row; i++){
        delete [] my_matrix_[i];
    }
    // freeing the all matrix
    delete [] my_matrix_;
}

int Board ::getRow() const{
    return this->row;
}

int Board::getCol() const {
    return this->col;
}

void Board::printBoard() const {
    // printing the first line of the board
    for (int z=0; z<col+1 ;z++){
        if (z==0){
            this->game_screen_.printString(" ");
        }
        else{
            this->game_screen_.printString("| " + this->toStringInt(z) + " ");
        }
    }
    this->printLine(this->col);
    // two loops, this first one symbolizes the columns and the second
    // one symbolizes the lines.
    for (int x = 0; x<col; x++){
        for (int y = 0; y<row;y++){
            if (y==0){
                this->game_screen_.printString(toStringInt(x+1));
            }
            this->game_screen_.printString("|");
            // printing the cell's type if it's not empty
            if (my_matrix_[x][y]->getType() == 'X' ||
                my_matrix_[x][y]->getType() == 'O') {
                this->game_screen_.printString(
                        " " + toStringChar(my_matrix_[x][y]->getType()) + " ");
            }
            else { // if the cell is empty
                this->game_screen_.printString("   ");
            }
        }
        this->printLine(this->col);
    }
}

bool Board::checkAllCellsFull() const {
    // going over all the matrix cells
    for (int i= 0;i<col ;i++ ){
        for (int j = 0; j < col; j++) {
            if (my_matrix_[j][i]->getType() == 'E'){
                return false;
            }
        }
    }
    // if all cells are full
    return true;
}

char Board::returnCellType(int r,int c) const{
    return my_matrix_[r][c]->getType();
}

void Board::setCellInBoard(int r, int c, char t) const {
    this->my_matrix_[r][c]->setType(t);
}

string Board::toStringInt(int number) const {
    stringstream ss;
    ss << number;
    string str = ss.str();
    return str;
}

string Board::toStringChar(char c) const {
    stringstream ss;
    string target;
    ss << c;
    ss >> target;
    return target;
}

void Board::printLine(int number) const {
    game_screen_.printString("|");
    game_screen_.printEndl();
    game_screen_.printString("--");
    for (int i = 0;i<number;i++){
    this->game_screen_.printString("----");
    }
    this->game_screen_.printEndl();
}
