
#ifndef REVERSISERVER_LISTCOMMAND_H
#define REVERSISERVER_LISTCOMMAND_H

#include "Command.h"

class ListCommand : public Command {
public:
    /**
     * constructor of ListCommand
     * @param run - RunServer obj
     */
    ListCommand();

    /**
     * destructor
     */
    virtual ~ListCommand();

    /**
     * this method goes over the list of games (receiving it from the
     * class container) and creates a message of it.
     * Than, the method sends the message to the user.
     * If the list is empty than sends notOkList.
     * @param args - the arguments from the client
     * @param clientSocket - number of client socket
    */
    virtual void execute(vector<string> args, int clientSocket);

private:
    string not_ok_list_;
};

#endif //REVERSISERVER_LISTCOMMAND_H