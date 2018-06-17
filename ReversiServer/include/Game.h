
#ifndef REVERSISERVER_GAME_H
#define REVERSISERVER_GAME_H

#include <string.h>
#include <iostream>

using namespace std;

enum STATUS {
    WAIT, PLAYING, ENDGAME
};

/**
 * This class saves the data about a game.
 */
class Game {
public:
    /**
     * constructor of game
     */
    Game();

    /**
     * destructor of game
     */
    ~Game();

    /**
     * this method returns the game status
     * @return STATUS - using an enum
     */
    STATUS getStatus() const;

    /**
     * this method changes the game status
     * @param status - using an enum
     */
    void setStatus(STATUS status);

    /**
     * this method gets the game name
     * @return string - the name
     */
    const string &getName() const;

    /**
     * this method sets the game name
     * @param name - the name - the name member should be change to
     */
    void setName(const string &name);

    /**
     * this method gets the first client(player) socket
     * @return int - as the first client socket
     */
    int getFirst_socket() const;

    /**
     * this method sets the first client socket member
     * @param first_socket - the socket the member should be change to
     */
    void setFirst_socket(int first_socket);

    /**
     * this method gets the second client(player) socket
     * @return int - as the second lient socket
     */
    int getSecond_socket() const;

    /**
     * this method sets the second client socket member
     * @param second_socket - the socjet the member should change to
     */
    void setSecond_socket(int second_socket);

private:
    string name;
    int first_socket_;
    int second_socket_;
    STATUS status;
};

#endif //REVERSISERVER_GAME_H