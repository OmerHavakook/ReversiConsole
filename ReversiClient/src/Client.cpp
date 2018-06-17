#include "../include/Client.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

Client::Client(const char *serverIP, int serverPort) :
        server_IP_(serverIP), server_port_(serverPort),
        client_socket_(0) {
}

Client::~Client() {}

int Client::connectToServer() {
    client_socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket_ == -1) {
        throw "Error opening socket";
    }
    struct in_addr address;
    if (!inet_aton(server_IP_, &address)) {
        throw "Can't parse IP address";
    }
    struct hostent *server;
    server = gethostbyaddr((const void *) &address, sizeof
            address, AF_INET);
    if (server == NULL) {
        throw "Host is unreachable";
    }
    // Create a structure for the server address
    struct sockaddr_in serverAddress;
    bzero((char *) &address, sizeof(address));
    serverAddress.sin_family = AF_INET;
    memcpy((char *) &serverAddress.sin_addr.s_addr,
           (char *) server->h_addr, server->h_length);
    serverAddress.sin_port = htons(server_port_);
    if (connect(client_socket_, (struct sockaddr
    *) &serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error connecting to server";
    }
}

char *Client::receiveMove() const {
    char *user_choice = new char[point_size];
    // read from socket the movement
    int n = read(client_socket_, user_choice, point_size);
    // error in reading
    if (n == -1) {
        throw "Error of reading from socket";
    } // return the point
    return user_choice;
}

int Client::getClientSocket() const {
    return this->client_socket_;
}

void Client::sendMessage(const char *msg) const {
    string copy;
    // add the message to copy
    copy.append(msg);
    // add null at the end of the string (as should by string format)
    copy.append("\0");
    int n = send(client_socket_, copy.c_str(), copy.size() + 1, 0);
    // for an error in sending
    if (n == -1) {
        throw "Error of writing to socket";
    }
}

string Client::reciveMessage() const {
    // initialize buffer to scan the input from the server
    char buffer[max_size] = {0};
    string res = "";
    // receiveMove message from the server
    int n = recv(client_socket_, buffer, max_size - 1, 0);
    // if receiving data happened than save it
    if (n > 0) {
        res.append(buffer);
    } else {
        return "null";
    }

    return res;
}

void Client::sendMove(char *user_choice) const {
    // write the user choice
    int n = write(client_socket_, user_choice, sizeof(user_choice));
    if (n == -1) {
        throw "Error of writing to socket";
    }
}