
#ifndef EX2_AIPLAYER_H
#define EX2_AIPLAYER_H

#include "Player.h"

/**
 * AIPlayer is the computer player class
 */
class AIPlayer : public Player {
public:
    /**
     * constructor of HumanPlayer.
     * @param type - as char ('X' or 'O')
     * @param screen  - as the game screen
     */
    AIPlayer(char type, ConsoleScreen *screen);

    /**
     * In this method we run over all of the computer's options,
     * and used the "minimax" algorithm in order to find the option
     * that will cause the human player not to make his best choices.
     * @param game - as gameLogic object
     * @return string - the chosen cell.
     */
    string chooseCell(GameLogic &game);

};

#endif //EX2_AIPLAYER_H