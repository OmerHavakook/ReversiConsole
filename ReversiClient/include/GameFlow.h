
#ifndef EX2_GAMEFLOW_H
#define EX2_GAMEFLOW_H

#include "GameLogic.h"
#include "ConsoleScreen.h"
#include "Client.h"

/**
 * this class runs the all game.
 */

class GameFlow {
public:
    /**
     * this is the constructor of the class.
     * @param size - as the board size.
     */
    GameFlow(int size);

    /**
     * this is the destructor of the game.
     */
    ~GameFlow();

    /**
     * this method runs the game.
     */
    void run();

    /**
    * this method is called from the constructor
    * and by the user choice initialize the members.
    */
    void setUpGame();

private:
    int size;
    GameLogic *game;
    ConsoleScreen *screen;
    bool computer;
    bool x_player_;
    bool o_player_;

    /**
     * this method prints the scores to the user
     */
    void showScores();

    /**
     * this method read a file and save it's port and socket
     * @return pair
     */
    pair<const char *, int> createClientFromFile();

    /**
     * this method handle the user choice for a
     * @param client
     */
    void handleThirdCase(Client client);

    /**
     * If starting a game is possible (known by the data received from
     * the server), than startGameCommand is called.
     * In this method I created a game with remote and local players and run it.
     * @param client - client object
     * @param name - as the name of the game
     */
    void startGameCommand(Client client, string name);

    /**
     * If joining a game is possible (known by the data received from
     * the server), than joinGameCommand is called.
     * In this method I created a game with remote and local players and run it.
     * @param client - client object
     * @param name - as the name of the game
     */
    void joinGameCommand(Client client, string name);

    /**
     * If the user chose to play with another human player (chose 1
     * in the main menu) than createGameHuman is called.
     * In this method I created a game with 2 human players
     * and run it.
     */
    void createGameHuman();

    /**
     * If the user chose to play with the computer ( chose 2 in the
     * main menu) than createAIGame is called.
     * In this method I created a game with human and AIPlayer players
     * and run it.
     */
    void createAIGame();

    /**
     * this method read from the server the order of the players.
     * @param client - Client object
     * @return int - the number of the player
     */
    int getOrder(Client client);
};

#endif //EX2_GAMEFLOW_H