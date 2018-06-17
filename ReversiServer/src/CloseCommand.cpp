
#include "../include/CloseCommand.h"

CloseCommand::CloseCommand() {
    ok_close_ = string("6");
    not_ok_close_ = string("7");
}

CloseCommand::~CloseCommand() {}

void CloseCommand::execute(vector<string> args, int client_socket_) {
    string game_name = args[0];
    // try to remove game from the list in server container
    bool del = ServerContainer::getInstance()->removeGame(game_name);
    string msg = "";
    if (del) { // if removing was possible, send ok_close_
        msg.append(ok_close_);
    } else { // if removing wasn't possible, send not_ok_close_
        msg.append(not_ok_close_);
    }
    sendMessageToClient(msg, client_socket_);
}