
#include "../include/GameLogic.h"

#include <iostream>

GameLogic::GameLogic(int size, Player *player1, Player *player2,
                     ConsoleScreen *screen) {
    this->my_screen_ = screen;
    this->first_player_ = player1;
    this->second_player_ = player2;
    this->my_board_ = new Board(size);
    this->current_Player_ = 'X';
}

GameLogic::~GameLogic() {
    delete my_screen_;
    delete first_player_;
    delete second_player_;
    delete my_board_;
}

char GameLogic::returnsWhoWon() const {
    // save the scores and compare
    int player_X_score, player_O_score;
    player_X_score = first_player_->getScore();
    player_O_score = second_player_->getScore();
    if (player_X_score == player_O_score) { // if it's a tie
        return '=';
    }
    if (player_X_score > player_O_score) {
        return first_player_->getType();
    }
    return second_player_->getType();
}

bool GameLogic::checksIfGameOver(Board &board) {
    // if all cells are full or the are no possible moves for each side
    if (board.checkAllCellsFull() ||
        (!checksIfMovesArePossible('X', board)
         && !checksIfMovesArePossible('O', board))) {
        return true;
    }
}

bool GameLogic::checksIfMovesArePossible(char type, Board &board) {
    vector<string> vector_to_check = findPossibleCells(board, type);
    if (vector_to_check.size() == 0) { // if it's empty
        return false;
    }
    return true;
}

vector<string> GameLogic::findPossibleCells(Board &board, char type) {
    vector<string> vector_of_cells;
    char other_type = 'O';
    if (type == 'O') {
        other_type = 'X';
    }
    // going over the all matrix
    for (int i = 0; i < board.getSize(); i++) {
        for (int j = 0; j < board.getSize(); j++) {
            // if the cell is on the current player type
            if (board.returnCellType(i, j) == type) {
                // looking for the other type near it
                for (int a = -1; a < 2; a++) {
                    for (int b = -1; b < 2; b++) {
                        if ((i + a >= 0) && (i + a < board.getSize())
                            && (j + b >= 0)
                            && (j + b < board.getSize())) {
                            // found other type cell
                            if (board.returnCellType(i + a, j + b)
                                == other_type) {
                                string empty_word = "(";
                                string point = findEmptyCellGeneral(
                                        i + a, j + b, other_type, a, b, board);
                                //if the points exists add it to the vector
                                if ((point.compare(empty_word) != 0)) {
                                    vector_of_cells.push_back(point);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return this->cutDuplicate(vector_of_cells);
}

string GameLogic::findEmptyCellGeneral(int r, int c, char t, int row_change,
                                       int col_change, Board &board) {
    int index_row = r;
    int index_col = c;
    for (int i = 1; i < board.getSize(); i++) {
        changeNumber(index_row, row_change, r, i);
        changeNumber(index_col, col_change, c, i);
        // check if in limits
        if (index_row >= 0 && index_row < board.getSize()
            && index_col >= 0 && index_col < board.getSize()) {
            // if an empty cell was found
            if (board.returnCellType(index_row, index_col) == 'E') {
                return "(" + this->getBoard()->toStringInt(index_row) +
                       "," + this->getBoard()->toStringInt(index_col) + ")";
            } // if the cell is on the same player's type
            if (board.returnCellType(index_row, index_col) == t) {
                continue;
            } // if the cell is on the other player's type
            if (board.returnCellType(index_row, index_col) != t) {
                break;
            }
        }
    }
    return "(";
}

void GameLogic::makeAMove(int r, int c, char t, int row_change,
                          int col_change, Board &board) {
    int index_row = r;
    int index_col = c;
    char other_type = 'X';
    if (t == 'X') {
        other_type = 'O';
    }
    for (int i = 0; i < board.getSize(); i++) {
        // change the index variables, add or reduce i from r\c
        changeNumber(index_row, row_change, r, i);
        changeNumber(index_col, col_change, c, i);
        if (index_row >= 0 && index_row < board.getSize()
            && index_col >= 0 && index_col < board.getSize()) {
            if (board.returnCellType(index_row, index_col)
                == other_type) {
                int row_new = index_row;
                int col_new = index_col;
                row_new += row_change;
                col_new += col_change;
                if (row_new >= 0 && row_new < board.getSize()
                    && col_new >= 0 && col_new < board.getSize()) {
                    // if an empty cell was found
                    if (board.returnCellType(row_new, col_new)
                        == 'E') {
                        return;
                    }
                } // if the cell is out of the matrix
                if (row_new < 0 || row_new >= board.getSize()
                    || col_new < 0 || col_new >= board.getSize()) {
                    return;
                } // if access is possible ,check its type
                if (board.returnCellType(row_new, col_new) == t) {
                    for (int j = 0; j <= i + 1; j++) {
                        int row_loop = r;
                        int col_loop = c;
                        changeNumber(row_loop, row_change, row_loop, j);
                        changeNumber(col_loop, col_change, col_loop, j);
                        board.setCellInBoard(row_loop, col_loop, t);
                        this->updateScore(board);
                    }
                    return;
                }
            }
        }
    }
}

void GameLogic::changeNumber(int &number, int flag,
                             int default_number, int add_number) {
    if (flag == 1) {
        number = default_number + add_number;
    }
    if (flag == -1) {
        number = default_number - add_number;
    }
}

Board *GameLogic::updateBoard(int x, int y, char type, Board &board) {
    char other_type = 'O';
    if (type == 'O') {
        other_type = 'X';
    } // set the cell in the matrix
    board.setCellInBoard(x, y, other_type);
    for (int a = -1; a < 2; a++) {
        for (int b = -1; b < 2; b++) {
            if ((x + a >= 0) && (x + a < board.getSize())
                && (y + b >= 0) && (y + b < board.getSize())) {
                // make a move
                if (board.returnCellType(x + a, y + b) == type) {
                    makeAMove(x + a, y + b, other_type, a, b, board);
                }
            }
        }
    }
    return &board;
}

bool GameLogic::checkPlayerMove(string user_input, char type, Board &board) {
    vector<string> allPoints = this->findPossibleCells(board, type);
    vector<string>::iterator it;
    // go over all of the possible moves and compare
    // the user choice to them
    for (it = allPoints.begin(); it != allPoints.end(); ++it) {
        if ((*it).compare(user_input) == 0) {
            // if the player choice is llegal
            return true;
        }
    }
    return false;
}

Board *GameLogic::getBoard() {
    return my_board_;
}

void GameLogic::updateScore(Board &board) {
    // going over the all matrix and counting the number
    // of appearances to each player
    int player_X = 0;
    int player_O = 0;
    calculateScores(player_X, player_O, board);
    this->first_player_->setScore(player_X);
    this->second_player_->setScore(player_O);
}

int GameLogic::getScoresDifference(Board &b) {
    // going over the all matrix and counting the number
    // of appearances to each player
    int player_X = 0;
    int player_O = 0;
    calculateScores(player_X, player_O, b);
    return player_X - player_O;
}

void GameLogic::calculateScores(int &x_score, int &o_score, Board &board) {
    for (int i = 0; i < board.getSize(); i++) {
        for (int j = 0; j < board.getSize(); j++) {
            if (board.returnCellType(i, j) == 'X') {
                x_score++;
            }
            if (board.returnCellType(i, j) == 'O') {
                o_score++;
            }
        }
    }
}

int GameLogic::getPlayer2Score() const {
    return this->second_player_->getScore();
}

int GameLogic::getPlayer1Score() const {
    return this->first_player_->getScore();
}

vector<string> GameLogic::cutDuplicate(vector<string> vector_before) const {
    vector<string> vector_without_dup;
    vector<string>::iterator iterat;
    // go over all of the vector_before vector
    for (iterat = vector_before.begin(); iterat != vector_before.end();
         ++iterat) {
        bool flag = false;
        vector<string>::iterator it2;
        for (it2 = vector_without_dup.begin();
             it2 != vector_without_dup.end(); ++it2) {
            string s1 = *iterat;
            string s2 = *it2;
            if ((s1.compare(s2) == 0)) {
                // if the point already appeared
                flag = true;
            }
        }
        if (!flag) { // if the point didn't appear already
            vector_without_dup.push_back(*iterat);
        }
    }
    return vector_without_dup;
}

void GameLogic::changePlayer() {
    if (this->current_Player_ == 'O') {
        this->current_Player_ = 'X';
    } else {
        this->current_Player_ = 'O';
    }
}

Player *GameLogic::getPlayer(char type) {
    // check the type and return the right player
    if (type == 'X') {
        return this->first_player_;
    }
    if (type == 'O') {
        return this->second_player_;
    } // 'C' for computer type
    if (type == 'C') {
        if (current_Player_ == 'X') {
            return this->first_player_;
        }
        return this->second_player_;
    } // 'D' for the other player (not computer) type
    if (type == 'D') {
        if (current_Player_ == 'X') {
            return this->second_player_;
        }
        return this->first_player_;
    }
}