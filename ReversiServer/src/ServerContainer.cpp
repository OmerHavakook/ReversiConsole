
#include "../include/ServerContainer.h"

ServerContainer *ServerContainer::instance = NULL;
pthread_mutex_t ServerContainer::lock;

ServerContainer *ServerContainer::getInstance() {
    if (instance == 0) {
        pthread_mutex_lock(&lock);
        if (instance == 0) {
            instance = new ServerContainer();
        }
        pthread_mutex_unlock(&lock);
    }
    return instance;
}

ServerContainer::ServerContainer() {
    this->vec_of_games_ = new vector<Game *>;
}

ServerContainer::~ServerContainer() {
    delete vec_of_games_;
}

void ServerContainer::addGame(Game *game) {
    pthread_mutex_lock(&lock);
    this->vec_of_games_->push_back(game);
    pthread_mutex_unlock(&lock);
}

bool ServerContainer::removeGame(string name) {
    // going over the vector of games and look for a game with the same name
    // as the name received in this method
    for (vector<Game *>::iterator it = vec_of_games_->begin();
         it != vec_of_games_->end(); ++it) {
        if (!strcmp((*it)->getName().c_str(), name.c_str())) {
            // if a game was found than erase it and return true
            pthread_mutex_lock(&lock);
            vec_of_games_->erase(it);
            pthread_mutex_unlock(&lock);
            return true;
        }
    }
    // no game with the same name was found
    return false;
}

void ServerContainer::addClientSocket(int client_socket) {
    pthread_mutex_lock(&lock);
    this->client_sockets_.push_back(client_socket);
    pthread_mutex_unlock(&lock);
}

bool ServerContainer::removeClientSocket(int client_socket) {
    // going over the vector of integers and look for a number
    // as the same as the client socket
    for (vector<int>::iterator it = client_sockets_.begin();
         it != client_sockets_.end(); ++it) {
        if (*it == client_socket) {
            pthread_mutex_lock(&lock);
            // if a number was found than erase if and return true
            client_sockets_.erase(it);
            pthread_mutex_unlock(&lock);
            return true;
        }
    }
    // there is no a number as the client_socket in the vec of int
    return false;
}

vector<Game *> *ServerContainer::getVecOfGames() {
    return vec_of_games_;
}

vector<int> ServerContainer::getClient_sockets() const {
    return client_sockets_;
}