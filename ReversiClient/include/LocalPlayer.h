
#ifndef REVERSI_LOCALPLAYER_H
#define REVERSI_LOCALPLAYER_H

#include "Player.h"
#include "Client.h"

/**
 * this is the local player, he choose cell cell and send
 * the information to the server.
 */
class LocalPlayer : public Player {
public:
    /**
     * this is the constructor
     * @param type - 'X' or 'O'
     * @param screen - as ConsoleScreen Object
     * @param client - as a Client object
     */
    LocalPlayer(char type, ConsoleScreen *screen, Client &client);

    /**
     * the local player is asked for a point, he enter a point,
     * sent it to the server and return to the gameFlow.
     * @param gameLogic - as the gameLogic object
     * @return string - the chosen cell
     */
    string chooseCell(GameLogic &gameLogic);

private:
    Client client;

    /**
    * this method converts a point from a human representation to computer's.
    * @param user_choice - as the cell before the convert.
    * @return string - the cell after the change
    */
    string fixPointToCom(string user_choice) const;
};

#endif //REVERSI_LOCALPLAYER_H