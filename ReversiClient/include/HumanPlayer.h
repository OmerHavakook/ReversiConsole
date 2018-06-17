
#ifndef EX2_HUMANPLAYER_H
#define EX2_HUMANPLAYER_H

#include "Player.h"

class HumanPlayer : public Player {
public:
    /**
     * constructor of HumanPlayer.
     * @param type - as char ('X' or 'O')
     * @param screen  - as the game screen
     */
    HumanPlayer(char type, ConsoleScreen *screen);

    /**
     * the human player is asked for a point, he enter a point,
     * and return to the gameFlow.
     * @param gameLogic - as the gameLogic object
     * @return string - the chosen cell
     */
    string chooseCell(GameLogic &gameLogic);

private:
    /**
     * this method converts a point from a human representation to computer's.
     * @param user_choice - as the cell before the convert.
     * @return string - the cell after the change
     */
    string fixPointToCom(string user_choice) const;
};

#endif //EX2_HUMANPLAYER_H