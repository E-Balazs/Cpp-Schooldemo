#ifndef MINESWEEPINTERFACE_HPP_INCLUDED
#define MINESWEEPINTERFACE_HPP_INCLUDED

#include "minesweeper.hpp"
#include "string5.h"

/// \brief Az aknakereső kontrollárására használatos
class MinesweeperInterface{
    Minesweeper* board;
    MinesweeperInterface(MinesweeperInterface&);
    int bombs, w,h;
    enum numBombs{
        BEasy = 12,
        BRegular = 60,
        BChallange = 160
    };
    enum mapsize{
        SEasy = 10,
        SRegular = 20,
        WChallange =34,
        HChallange = 23
    };
    int gameLoop();
    void info();
    void game();

public:
    MinesweeperInterface();
    void start();


    ~MinesweeperInterface(){if(board) delete board;}
};

#endif // MINESWEEPINTERFACE_HPP_INCLUDED
