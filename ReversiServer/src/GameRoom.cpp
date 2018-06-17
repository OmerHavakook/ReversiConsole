
#include <unistd.h>
#include "../include/GameRoom.h"

GameRoom::GameRoom(Game *game) : game(game) {}

GameRoom::~GameRoom() {
    delete game;
}
bool GameRoom::handleMove(int sender, int receiver) {
    char buffer_local[maxMove];
    cout << "wait for receiving move " << sender << endl;
    // read the move
    int n = read(sender, buffer_local, maxMove);
    if (n == -1) {
        cout << "Error reading buffer_local" << endl;
        return false;
    }
    if (n == 0) {
        cout << "Client disconnected" << endl;
        return false;
    }
    // print the move
    cout << "Got move: " << buffer_local << endl;
    // if the move is "END" (end of the game)
    if (strcmp(buffer_local, "END") == 0) {
        // than print a message, change game status and remove the game
        cout << "end of game " << game->getName() << endl;
        game->setStatus(ENDGAME);
        ServerContainer::getInstance()->removeGame(game->getName());
        return false;
    }
    // if it's not the end of the game than write it
    n = write(receiver, buffer_local, maxMove);
    if (n == -1) {
        cout << "Error writing buffer_local" << endl;
        return false;
    }
    if (n == 0) {
        cout << "Client disconnected" << endl;
        return false;
    }
    // print a message
    cout << "Sent Move:" << buffer_local << endl;
    return true;
}

void *GameRoom::runGame(void *obj) {
    // cast obj to GameRoom
    GameRoom *ptr = (GameRoom *) obj;
    int num_of_client = 1;
    // write the client his number(1)
    write(ptr->game->getFirst_socket(), &num_of_client, sizeof(num_of_client));
    num_of_client = 2;
    // write the client his number(2)
    write(ptr->game->getSecond_socket(), &num_of_client, sizeof(num_of_client));
    bool ok = true;
    int i = 0;
    while (ok) {
        // handle the moves and switch turns
        if (i % 2 == 0) {
            ok = ptr->handleMove(ptr->game->getFirst_socket(),
                                 ptr->game->getSecond_socket());
        } else {
            ok = ptr->handleMove(ptr->game->getSecond_socket(),
                                 ptr->game->getFirst_socket());
        }
        i++;
    }
    delete (GameRoom *)obj;
}