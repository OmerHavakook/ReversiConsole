#ifndef EX2_DSA_H
#define EX2_DSA_H

#include <fstream>
#include <unistd.h>
#include <cstring>
#include "../include/GameFlow.h"
#include "../include/AIPlayer.h"
#include "../include/HumanPlayer.h"
#include "../include/RemotePlayer.h"
#include "../include/LocalPlayer.h"

# define OkStart 1
# define NotOkStart 2
# define OkJoin 3
# define NotSuchAGameJoin 4
# define GameIsPlaying 5
# define OkClose 6
# define NotOkClose 7
# define NotOkList 8

GameFlow::GameFlow(int size) : size(size) {}

GameFlow::~GameFlow() {
    delete game;
}

void GameFlow::run() {
    Board *board = this->game->getBoard();
    Player *player;
    // printing the board
    screen->printBoard(*board);
    string user_choice, choice_to_compare;
    // as long as the game is not over
    while (!this->game->checksIfGameOver(*this->game->getBoard())) {
        board = this->game->getBoard();
        player = (game->getPlayer('C'));
        // ask for point if it's needed
        if (!(computer) || player->getType() == 'X') {
            bool b = x_player_;
            if (player->getType() == 'O') {
                b = o_player_;
            }
            screen->printPlayerOrder(b, player->getType());
        }
        // scan a point
        user_choice = this->game->getPlayer('C')->chooseCell(*this->game);
        // if the player can make a move
        if (user_choice.compare("NO MOVE")) {
            // split the input
            vector<int> point_coordinate = screen->cutPoint(user_choice);
            int first_number = point_coordinate.front();
            int second_number = point_coordinate.back();
            // print move
            screen->printPlayerMove(player->getType(),
                                    first_number, second_number);
            // updating the board and printing it
            this->game->updateBoard(first_number, second_number,
                                    this->game->getPlayer('D')->getType(),
                                    *this->game->getBoard());
            this->screen->printEndl();
            this->screen->printBoard(*board);
        } else { // if no move is possible
            this->screen->printNoMoveOrder(player->getType());
        }
        this->game->changePlayer();
    }
    showScores();
}

void GameFlow::showScores() {
    screen->printGameOver(this->game->returnsWhoWon(), this->game->getPlayer1Score(),
                          game->getPlayer2Score());
}

void GameFlow::setUpGame() {
    this->screen = new ConsoleScreen();
    int player_check = this->screen->printOpenMenu();
    switch (player_check) {
        // for a game with a human
        case 1:
            createGameHuman();
            break;
            // for a game with the computer
        case 2 :
            createAIGame();
            break;
            // for a game with a remote player
        case 3 :
            try {
                /* pair<const char *, int> p=createClientFromFile();
                 Client client(p.first,p.second);*/
                ifstream inFile;
                inFile.open("config_client.txt");
                string ip;
                int port;
                inFile >> ip;
                inFile >> port;
                Client client(ip.c_str(), port);
                // call handleThirdCase to run this case
                handleThirdCase(client);
                break;
            } catch (const char *msg) {
                // if there was an error than print a message
                this->screen->printString("Failed to connect to server."
                                                  " Reason: ");
                this->screen->printString(msg);
                this->screen->printEndl();
                return;
            }
        default:
            break;
    }
}

pair<const char *, int> GameFlow::createClientFromFile() {
    ifstream inFile;
    inFile.open("config_client.txt");
    string ip;
    int port;
    getline(inFile, ip);
    //inFile >> ip;
    inFile >> port;
    return make_pair(ip.c_str(), port);
}

void GameFlow::handleThirdCase(Client client) {
    while (true) {
        // connect to the server
        client.connectToServer();
        // call handle sub menu to ask the user for a mission
        pair<string, string> result = screen->handleSubMenu();
        // save the user option(start/join/list)
        string user_sub_option = result.first;
        // save the name of the game (for start/join)
        string game_name = result.second;
        // add null to make it string
        user_sub_option.append("\0");
        // send the server the option
        client.sendMessage(user_sub_option.c_str());
        // receiveMove signal from the client (a number as represented in the
        // switch case.
        string msg_from_server = client.reciveMessage();
        // if the user asked to print list and it's not empty
        if (!strcmp(msg_from_server.c_str(), "-1")) {
            this->screen->printString("The server is closed."
                                              " We are sorry, goodbye...:)");
            exit(-1);
        } else {
            // save the signal from the server as an int
            int option = atoi(msg_from_server.c_str());
            switch (option) {
                // if a game can be created
                case OkStart:
                    startGameCommand(client, game_name);
                    continue;
                    // if a game can't be created because the name
                    // has been already taken
                case NotOkStart:
                    screen->printString("this name has been already token");
                    screen->printEndl();
                    continue;
                    // if the user can join the game
                case OkJoin:
                    joinGameCommand(client, game_name);
                    continue;
                    // if the user can't join the game because ther is not
                    // a game with such a name
                case NotSuchAGameJoin:
                    screen->printString("there is not such a game");
                    screen->printEndl();
                    continue;
                    // if the user asked for a game that is being played
                case GameIsPlaying:
                    screen->printString("this game is being played by 2 players");
                    screen->printEndl();
                    continue;
                    // if the user asked to close a game and it's possible
                case OkClose:
                    return;
                    // if the user asked to close a game and there isn't
                    // a game with this name
                case NotOkClose:
                    screen->printString("there is not such a game");
                    screen->printEndl();
                    continue;
                    // if the user asked to print the list of the games but
                    // it's empty
                case NotOkList:
                    screen->printString("The list is empty");
                    screen->printEndl();
                    continue;
                default:
                    screen->printString(msg_from_server);
                    continue;
            }
        }
    }
}

void GameFlow::startGameCommand(Client client, string name) {
    string message = "";
    // print a message to the user to make him know he should wait
    screen->printString("Waiting for another player to join");
    screen->printEndl();
    // get the player order (1/2) and print it
    // the read inside getOrder make the player to wain
    // for another player to join his game
    int number = getOrder(client);
    string wait = "Your number is:" + screen->toStringInt(number);
    screen->printString(wait);
    screen->printEndl();
    // create local and remote players
    Player *player1 = new LocalPlayer('X', screen, client);
    Player *player2 = new RemotePlayer('O', screen, client);
    this->x_player_ = true;
    this->o_player_ = false;
    // create a game and run it
    this->game = new GameLogic(size, player1, player2, screen);
    run();
    client.sendMove(const_cast<char *>("END"));
}

void GameFlow::joinGameCommand(Client client, string name) {
    string message = "";
    // get the player order (1/2) and print it
    int number = getOrder(client);
    string wait = "Your number is:" + screen->toStringInt(number);
    screen->printString(wait);
    screen->printEndl();
    // create remote and local players
    Player *player1 = new RemotePlayer('X', screen, client);
    Player *player2 = new LocalPlayer('O', screen, client);
    this->x_player_ = false;
    this->o_player_ = true;
    // create a game and run it
    this->game = new GameLogic(size, player1, player2, screen);
    run();
    client.sendMove(const_cast<char *>("END"));
}

void GameFlow::createGameHuman() {
    // set the two players as HumanPlayer's
    Player *player1 = new HumanPlayer('X', screen);
    Player *player2 = new HumanPlayer('O', screen);
    this->computer = false;
    this->x_player_ = true;
    this->o_player_ = true;
    // create a game and run it
    this->game = new GameLogic(size, player1, player2, screen);
    run();
}

void GameFlow::createAIGame() {
    // set the first player as HumanPlayer and the second as AIPlayer
    Player *player1 = new HumanPlayer('X', screen);
    Player *player2 = new AIPlayer('O', screen);
    this->computer = true;
    this->x_player_ = true;
    this->o_player_ = true;
    // create the game and run it
    this->game = new GameLogic(size, player1, player2, screen);
    run();
}

int GameFlow::getOrder(Client client) {
    int num_of_player;
    int client_socket = client.getClientSocket();
    // read the number of player from the socket
    int n = read(client_socket, &num_of_player, sizeof(num_of_player));
    if (n == -1) {
        throw "Error of reading from socket";
    }
    if (num_of_player != 1 && num_of_player != 2) {
        this->screen->printString("There is a problem with the server!"
                                          " The program will shut down");
        this->screen->printEndl();
        exit(-1);
    }
    // return the number
    return num_of_player;
}

#endif //EX2_DSA_H