
#ifndef REVERSI_REMOTEPLAYER_H
#define REVERSI_REMOTEPLAYER_H


#include "Player.h"
#include "Client.h"
#include "stdlib.h"

/**
 * this is the remote player, he can't choose cell for himself,
 * but choose by the information from the server.
 */
class RemotePlayer : public Player {
public:

    /**
     * this is the constructor for RemotePlayer
     * @param type - as char type
     * @param screen - as the game screen
     * @param client - as Client object - to communicate.
     */
    RemotePlayer(char type, ConsoleScreen *screen, Client &client);

    /**
     * the remote player receive information from the server and
     * returns it.
     * @param gameLogic - as gameLogic object.
     * @return string - as cell.
     */
    string chooseCell(GameLogic &gameLogic);

protected:
    Client client;
};

#endif //REVERSI_REMOTEPLAYER_H