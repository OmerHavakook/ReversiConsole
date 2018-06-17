#include "../include/Game.h"

// initialize both sockets members to -1
Game::Game() : first_socket_(-1), second_socket_(-1) {}

Game::~Game() {}

const string &Game::getName() const {
    return name;
}

void Game::setName(const string &name) {
    Game::name = name;
}

int Game::getFirst_socket() const {
    return first_socket_;
}

void Game::setFirst_socket(int first_socket) {
    Game::first_socket_ = first_socket;
}

int Game::getSecond_socket() const {
    return second_socket_;
}

void Game::setSecond_socket(int second_socket) {
    Game::second_socket_ = second_socket;
}

STATUS Game::getStatus() const {
    return status;
}

void Game::setStatus(STATUS status) {
    Game::status = status;
}