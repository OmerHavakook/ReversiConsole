
#include "../include/JoinCommand.h"
#include "../include/Game.h"
#include "../include/ServerContainer.h"
#include "../include/GameRoom.h"

JoinCommand::JoinCommand(){
    ok_join_ = string("3");
    not_such_game_join_ = string("4");
    game_is_playing_ = string("5");
}

JoinCommand::~JoinCommand() {}

void JoinCommand::execute(vector<string> args, int client_socket_) {
    Game *cur_game = NULL;
    string game_name = args[0];
    string msg = "";
    vector<Game *> *list_of_games = ServerContainer::getInstance()->getVecOfGames();
    // go over the list of games
    for (vector<Game *>::iterator it = list_of_games->begin();
         it != list_of_games->end(); ++it) {
        // if there is a waiting game with this name
        if (!strcmp((*it)->getName().c_str(), game_name.c_str())
            && (*it)->getStatus() == WAIT) {
            // set second socket and send ok_join_
            (*it)->setSecond_socket(client_socket_);
            cur_game = *it;
            msg.append(ok_join_);
            sendMessageToClient(msg,client_socket_);
            // create a new GameRoom
            GameRoom *gr = new GameRoom(cur_game);
            cur_game->setStatus(PLAYING);
            pthread_t newThread;
            // run the game in a thread
            int rc = pthread_create(&newThread, NULL, gr->runGame, (void *) gr);
            if (rc) { // can't create a thread
                cout << "Error: unable to create thread, " << rc << endl;
                pthread_exit(&newThread);
            }
            return;
            // if there is a game with this name but it's being playing
        } else if (!strcmp((*it)->getName().c_str(), game_name.c_str()) &&
                   (*it)->getStatus() == PLAYING) {
            // send game_is_playing_
            msg.append(game_is_playing_);
            sendMessageToClient(msg,client_socket_);
            return;
        }
    } // if there is not a game with such name, than send not_such_game_join_
    msg.append(not_such_game_join_);
    sendMessageToClient(msg,client_socket_);
    return;
}