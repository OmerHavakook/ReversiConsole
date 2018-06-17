
#ifndef REVERSISERVER_COMMAND_H
#define REVERSISERVER_COMMAND_H


#include <vector>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include "iostream"

using namespace std;

/**
 * Interface of Command, we will create classed that implements this class
 * and use the command design pattern.
 */
class Command {
public:
    /**
     * this method execute the command using the vector of args.
     * this is a pure virtual method
     * @param args - vector of string
     */
    virtual void execute(vector<string> args, int clientSocket) = 0;

    /**
     * destructor for command
     */
    virtual ~Command() {}

    /**
     * this method sends message to the client
     * @param msg - the message to send the client
     * @param client_socket_ - the client socket
     */
    void sendMessageToClient(string msg, int client_socket_) {
        int n = send(client_socket_, msg.c_str(), msg.length(), 0);
        if (n == -1) { // error
            cout << "Error writing buffer_local" << endl;
            return;
        }
    }

};

#endif //REVERSISERVER_COMMAND_H
