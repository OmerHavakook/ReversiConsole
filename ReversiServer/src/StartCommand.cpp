
#include "../include/StartCommand.h"
#include "../include/Game.h"
#include "../include/ServerContainer.h"

StartCommand::StartCommand(){
    ok_start_ = string("1");
    not_ok_start_ = string("2");
}

StartCommand::~StartCommand() {}

void StartCommand::execute(vector<string> args,int client_socket_) {

    vector<Game *> *list_of_games = ServerContainer::getInstance()->getVecOfGames();
    string game_name = args[0];
    string msg = "";
    // go over the list og games
    for (vector<Game *>::iterator it = list_of_games->begin();
         it != list_of_games->end(); ++it) {
        // if there is already a game with this name than sends not_ok_start_
        if (!strcmp((*it)->getName().c_str(), game_name.c_str())) {
            msg.append(not_ok_start_);
            sendMessageToClient(msg,client_socket_);
            return;
        }
    }
    // create a new game and sets its name, status and first client socket.
    Game *newGame = new Game();
    newGame->setName(game_name);
    newGame->setFirst_socket(client_socket_);
    newGame->setStatus(WAIT);
    // add game to the server_container_
    ServerContainer::getInstance()->addGame(newGame);
    // send ok_start_
    msg.append(ok_start_);
    sendMessageToClient(msg,client_socket_);
}