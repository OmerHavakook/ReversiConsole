
#ifndef REVERSISERVER_CLOSECOMMAND_H
#define REVERSISERVER_CLOSECOMMAND_H

#include "../include/Command.h"
#include "../include/ServerContainer.h"

class CloseCommand : public Command {
public:
    /**
     * If the client send the server close XXX than this class execute method
     * is called.
     * @param run - as a RunServer object
     */
    CloseCommand();

    /*
     * destructor
     */
    virtual ~CloseCommand();

    /**
     * This method tries to remove a game in the server container.
     * If it succeeded than it sends okClose , else notOkClose to the client.
     * @param args - the arguments from the client
     * @param clientSocket - number of client socket
     */
    virtual void execute(vector<string> args,int clientSocket);

private:
    string ok_close_;
    string not_ok_close_;
};

#endif //REVERSISERVER_CLOSECOMMAND_H