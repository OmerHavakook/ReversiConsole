
#include <iostream>
#include <fstream>
#include "../include/Server.h"

using namespace std;

int main() {
	// creating a server from file
	int port=0;
	ifstream inFile;
    try{
		inFile.open("config_server.txt");
		inFile >> port;
    }catch (const char *msg) {
        cout << "Cannot start server. Config Problem Reason: " << msg << endl;
    }
	//ClientHandler c(0);
	Server server(port);
	// try to connect
	try {
		cout << "Enter exit to stop server\n" << endl;
		server.start();
		string str;
		cin >> str;
		if (str == "exit")
			server.stop();
	} catch (const char *msg) {
		cout << "Cannot start server. Reason: " << msg << endl;
	}
	// stop connection
	server.stop();
	return 0;
}
