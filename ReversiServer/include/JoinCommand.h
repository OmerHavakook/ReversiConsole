
#ifndef REVERSISERVER_JOINCOMMAND_H
#define REVERSISERVER_JOINCOMMAND_H

#include "../include/Command.h"

class JoinCommand : public Command {
public:
    /**
     * the constructor of JoinCommand
     * @param run - RunServer obj
     */
    JoinCommand();

    /**
     * destructor
     */
    virtual ~JoinCommand();

    /**
    * this method goes over the list of games (receiving it from the
    * class container) and checks if there is an available game with
    * the same name the user chose.
    * If he can join the game than sends okJoin, If there are
    * already 2 player playing the game than sends gameIsPlaying,
    * and if there is not a game with this name than sends notSuchGameJoin.
    * @param args - the arguments from the client
    * @param clientSocket - number of client socket
    */
    virtual void execute(vector<string> args,int clientSocket);

private:
    string ok_join_;
    string not_such_game_join_;
    string game_is_playing_;
};

#endif //REVERSISERVER_JOINCOMMAND_H