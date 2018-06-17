
#include <unistd.h>
#include <sys/socket.h>
#include "../include/ClientHandler.h"

void *handleCommand(void *obj);


ClientHandler::ClientHandler() {
}

ClientHandler::~ClientHandler() {
}

void *ClientHandler::handleCommand(void *socket) {
    long clientSocket = (long)socket;
    // create a buffer at max size to save the message from the client in it
    char buffer_local[MaxSize];
    string message = "";
    pair<string, vector<string> > cmd;
    cout << "wait for command :  " << clientSocket << endl;
    // call recv and read the client message and save it at buffer local
    int n = recv(clientSocket, buffer_local, MaxSize - 1, 0);
    if (n == -1) {
        cout << "Error reading buffer_local" << endl;
        return (void *) false;
    }
    if (n == 0) {
        cout << "Client disconnected" << endl;
        ServerContainer::getInstance()->removeClientSocket(clientSocket);
        return (void *) false;
    }
    // append buffer_local to message
    message.append(buffer_local);
    // call extractCommant
    cmd = ClientHandler::extractCommand(message);
    // execute command
    CommandManager::getInstance()->executeCommand(cmd.first, cmd.second,clientSocket);
}

pair<string, vector<string> > ClientHandler::extractCommand(string msg) {
    vector<string> args;
    // split the message by a space
    string cmd = "";
    size_t prev = 0, pos = 0;
    pos = msg.find(" ", prev);
    if (pos == string::npos)
        // make pair and return it
        return make_pair(msg, args);
    // save command
    string command = msg.substr(prev, pos - prev);
    if (!command.empty()) // append the command to message
        cmd.append(command);
    string game_name = msg.substr(pos + 1, msg.size() );
    args.push_back(game_name);
    // return the pair
    return make_pair(cmd, args);
}