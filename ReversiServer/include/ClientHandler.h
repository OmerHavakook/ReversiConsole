#ifndef REVERSISERVER_CLIENTHANDLER_H
#define REVERSISERVER_CLIENTHANDLER_H

#include <iostream>
#include "vector"
#include "CommandManager.h"
#include "ServerContainer.h"

#define MaxSize 20

using namespace std;

class ClientHandler {
public:
    /**
     * constructor for ClientHandler
     * @param client_Socket - the number of the client socket
     * @param serverContainer - a pointer to the server container
     */
    ClientHandler();

    /**
     * destructor
     */
    ~ClientHandler();

    /**
     * static method that handle the client's commands ( is being called
     * in threads to handle many clients at the same time)
     * @param obj - as void * but will cast to ClientHandler object
     * in the method to be able to use this class methods and members.
     * @return void * - false for an error
     */
    static void *handleCommand(void *obj);

    /**
    * this method is static and is being called from handleCommand and
    * by the data received from the client - the method splits it by
    * space and return a pair
    * @param msg - the message from client
    * @return pair with the data splitted
    */
    static pair<string, vector<string> > extractCommand(string msg);

private:
    int client_Socket_;
    ServerContainer *server_container_;
};

#endif //REVERSISERVER_CLIENTHANDLER_H