#ifndef REVERSISERVER_GAMEROOM_H
#define REVERSISERVER_GAMEROOM_H

#include "Game.h"
#include "ServerContainer.h"
#include <pthread.h>
#include <vector>

#define maxMove 9

class GameRoom {
public:
    /**
     * constructor
     * @param game - pointer to a game
     */
    GameRoom(Game *game);

    /**
     * destructor
     */
    virtual ~GameRoom();

    /**
    * this method handle the client by trying to read from the socket
    * and ended the game if needed
    * @param sender - number of sender
    * @param receiver - number of receiver
    * @return false if there was a problem of disconnection) and true
    * if the game can continue
    */
    bool handleMove(int sender, int receiver);


    /**
     * this method runs the game
     * @param obj - void * that will be case into a gameRoom object
     * @return void *
     */
    static void *runGame(void *obj);

private:
    Game *game;
};

#endif //REVERSISERVER_GAMEROOM_H