/*
 *  Author: lee alima
 *  ID: 313467441
 */

#ifndef EX2_CELL_H
#define EX2_CELL_H

#include <string>

using namespace std;

class Cell {
public:
    /**
    * this is the constructor of the cell object.
    * @param initializeType - as the type (char) of the cell.
    */
    Cell(char initializeType);

    /**
    * this method return the cell's type.
    * @return char - as the type of the cell.
    */
    char getType() const;

    /**
    * this method set the type of the cell.
    * @param typeToChange - as a char(type) to change to.
    */
    void setType(char typeToChange);

private:
    char type;
};


#endif //EX2_CELL_H