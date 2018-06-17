
#include <cstring>
#include "../include/RemotePlayer.h"

RemotePlayer::RemotePlayer(char type, ConsoleScreen *screen, Client &client) :
        Player(type, screen), client(client) {
}

string RemotePlayer::chooseCell(GameLogic &gameLogic) {
    // receiveMove information from the client.
    char *move = client.receiveMove();
    string string_form = (string) move;
    delete move;
    // if there are no possible moves
    if (!string_form.compare("NO MOVE")) {
        return string_form;
    }
    // if the another player disconnected
    if (!gameLogic.checkPlayerMove(string_form, type, *gameLogic.getBoard())) {
        player_screen_->printString("Server is had a problem");
        player_screen_->printEndl();
        player_screen_->printString("The game is over..... goodbye!!!");
        player_screen_->printEndl();
        exit(0);
    }
    return string_form;
}