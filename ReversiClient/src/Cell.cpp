
#include "../include/Cell.h"

Cell::Cell(char initializeType) : type(initializeType) {
}

char Cell::getType() const {
    return this->type;
}

void Cell::setType(char typeToChange) {
    this->type = typeToChange;
}