/*
 *  Author: lee alima
 *  ID: 313467441
 */

#include "Cell.h"
using namespace std;

Cell::Cell(char initializeType) :type(initializeType){
}

char Cell::getType() const {
    return  this->type;
}

void Cell::setType(char typeToChange)  {
    this->type = typeToChange;
}