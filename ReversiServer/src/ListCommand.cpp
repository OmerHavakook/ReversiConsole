
#include "../include/ListCommand.h"
#include "../include/Game.h"
#include "../include/ServerContainer.h"

ListCommand::ListCommand() {
    not_ok_list_ = string("8");
}

ListCommand::~ListCommand() {}

void ListCommand::execute(vector<string> args,int client_socket_) {
    string list = "";
    vector<Game *> *list_of_games = ServerContainer::getInstance()->getVecOfGames();
    // go over the list of games
    for (vector<Game *>::iterator it = list_of_games->begin();
         it != list_of_games->end(); ++it) {
        // it the game status is waiting, than append its name to the string
        if ((*it)->getStatus() == WAIT) {
            list.append((*it)->getName());
            list.append("\n");
        }
    } // if the string is empty (there are no games waiting)
    if (list == "") { // send not_ok_list_
        list.append(not_ok_list_);
        sendMessageToClient(list,client_socket_);
        return;
    }
    // send the the list to the user
    string msg = "";
    msg.append("The available games:\n");
    msg.append(list);
    sendMessageToClient(msg,client_socket_);
}