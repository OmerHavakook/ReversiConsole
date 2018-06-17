
#ifndef REVERSISERVER_STARTCOMMAND_H
#define REVERSISERVER_STARTCOMMAND_H

#include "../include/Command.h"

class StartCommand : public Command {
public:
    /**
     * constructor for startCommand
     * @param run - RunServer obj
     */
    StartCommand();

    /**
     * destructor
     */
    virtual ~StartCommand();

    /**
    * this method starts a new game by creating a Game object and
    * setting its members. Than the method adds the game to the list
    * of games in the server containter class
    * If starting a game is possible than sends OkStart to the client,
    * else, sends him notOkStart.
    * @param args - the arguments from the client
    * @param int - client socket
    */
    virtual void execute(vector<string> args, int clientSocket);

private:
    string ok_start_;
    string not_ok_start_;
};

#endif //REVERSISERVER_STARTCOMMAND_H
