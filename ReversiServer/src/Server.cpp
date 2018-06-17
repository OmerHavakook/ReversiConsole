
#include "../include/Server.h"
#include <cstdlib>
#include <netinet/in.h>
#include <unistd.h>


using namespace std;

/**
 * This method creates a new ClientHandler with the clientSocket number
 * and handle its commands in a thread.
 * It also adds the thread to the list of threads.
 * @param obj - Server object in cast from void*
 * @return null for error in sending the message
 */
static void *mainThread(void *obj);


Server::Server(int _port) : port(_port), server_socket_(0){
    this->pool = new ThreadPool(THREADS_NUM);
}

Server::~Server() {
    delete pool;
}

void Server::start() {
    // Create a socket point
    server_socket_ = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket_ == -1) {
        throw "Error opening socket";
    }
    // Assign a local address to the socket
    struct sockaddr_in serverAddress;
    bzero((void *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);
    if (bind(server_socket_, (struct sockaddr *) &serverAddress,
             sizeof(serverAddress)) == -1) {
        throw "Error on binding";
    }
    listen(server_socket_, 0);
    int exit_thread_result = pthread_create(&p_exit, NULL, mainThread,
                                            (void *) this);
    if (exit_thread_result) {
        cout << "Exit thread creation failed, exiting" << endl;
        return;
    }
}


void Server::stop() {
    // close connection and exit program
    // save all of the client sockets to be able to make them
    // know the server is going to shut down.
    vector<int> sockets = ServerContainer::getInstance()->getClient_sockets();
    string msg = "-1";
    // inform all client
    for (int i = 0; i < sockets.size(); i++) {
        if (sockets[i] != 0) {
            int n = send(sockets[i], msg.c_str(), msg.length(), 0);
            if (n == -1) { // error
                cout << "Error writing buffer_local" << endl;
                exit(0);
            }
        }
    }
    cout << "All done. All communications are closed!" << endl;
    // close server and exit
    close(server_socket_);
    pool->terminate();
    exit(0);
}

int Server::getServer_socket_()  {
    return server_socket_;
}

ThreadPool *Server::getPool() const {
    return pool;
}

void *mainThread(void *args) {
    Server *serverObj = (Server *) args;
    cout << "Waiting for clients connections..." << endl;
    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);
    // as long as the server should be activated
    while (true) {
        // accept client requests to connect the server
        int client_socket_ = accept(serverObj->getServer_socket_(), (struct sockaddr *) &client_address,
                                    &client_address_len);
        if (client_socket_ == -1) {
            throw "Error on accept";
        }
        cout << "Client connected" << endl;
        // add the client socket to the list of clients socket in ServerContainer
        // add socket to the serverContainer obj
        ServerContainer::getInstance()->addClientSocket(client_socket_);
        // save the thread pool
        ThreadPool *p = serverObj->getPool();
        // create a new task
        Task *t = new Task(ClientHandler::handleCommand, (void *) (long)client_socket_ );
        // add task to the queue
        p->addTask(t);
    }
}