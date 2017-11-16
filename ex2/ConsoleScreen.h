/*
 *  Author: lee alima
 *  ID: 313467441
 */

#ifndef EX2_CONSOLESCREEN_H
#define EX2_CONSOLESCREEN_H

#include "Screen.h"

class ConsoleScreen : public Screen {
public:
    /**
     * this is the constructor for the object.
     */
    ConsoleScreen();

    /**
     * deconstructor for the object
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
};

#endif //EX2_CONSOLESCREEN_H