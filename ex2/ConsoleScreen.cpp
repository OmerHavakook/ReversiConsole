/*
 *  Author: lee alima
 *  ID: 313467441
 */

#include <iostream>
#include "ConsoleScreen.h"

ConsoleScreen::ConsoleScreen() { //empty constructor
}


void ConsoleScreen::printEndl() const {
    cout << endl;
}

void ConsoleScreen::printString(string s) const {
    cout << s;
}

ConsoleScreen::~ConsoleScreen() {
}
