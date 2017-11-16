/*
 *  Author: lee alima
 *  ID: 313467441
 */


#ifndef EX2_SCREEN_H
#define EX2_SCREEN_H

#include <string>

using namespace std;

/**
 * this is an abstract class - in this way the game can
 * be shown in different ways (like: console and gui).
 */
class Screen {
public:
    /**
     * this method prints a string.
     * @param s - as the string.
     */
    virtual void printString(string s) const = 0;

    /**
     * this method prints an empty line.
     */
    virtual void printEndl() const  = 0;
};


#endif //EX2_SCREEN_H
