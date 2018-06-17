
#ifndef REVERSI_CLIENT_H
#define REVERSI_CLIENT_H

#include <string>
#include <iostream>

using namespace std;

#define max_size 100
#define point_size 9

class Client {
public:
    /**
     * this is the constructor of Client
     * @param serverIP - as the server IP
     * @param serverPort - as the server port
     */
    Client(const char *serverIP, int serverPort);

    ~Client();

    /**
     * this method connects to the server and returns the number of the player
     * @return int - as the number of the player
     */
    int connectToServer();

    /**
     * this method sends message to the server using the number of
     * the client socket.
     * @param msg - the message the user wants to send the server
     */
    void sendMessage(const char *msg) const;

    /**
     * this method sends the server a point(move) using the client socket
     * @param user_choice - the move the user chose
     */
    void sendMove(char *user_choice) const;

    /**
    * this method receives message from the server using the client socket
    * @return string - the message
    */
    string reciveMessage() const;

    /**
     * this method receives a point from the server and returns it
     * @return char* - the point (client movement)
     */
    char *receiveMove() const;

    /**
     * this method returns the client socket
     * @return int - client socket
     */
    int getClientSocket() const;

private:
    const char *server_IP_;
    int server_port_;
    int client_socket_;

};

#endif //REVERSI_CLIENT_H