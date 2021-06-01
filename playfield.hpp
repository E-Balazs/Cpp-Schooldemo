#ifndef PLAYFIELD
#define PLAYFIELD

#include "tile.hpp"
#include <iostream>
using namespace tilegames;

class Playfield{
    Tile ***grid;
    int width, height, x, y;
protected:
    Tile* getTile(){return grid[y][x];}
    Tile* getTile(int X, int Y){return grid[Y][X];}
    Tile* setTile(Tile* tl = NULL){
        Tile* ret = grid[y][x];
        grid[y][x] = tl;
        return ret;
    }
    Tile* setTile(Tile* tl, int X, int Y){
        Tile* ret = grid[Y][X];
        grid[X][Y] = tl;
        return ret;
    }
    // egyes mezőket hogy írja ki az adott játék
    virtual void printTile(Tile* toprint, std::ostream& os) = 0;
    //ha a játéktéren belül van, odamozdul és true, különben false
    bool tryMove(int X, int Y);
    void clear();
public:
    Playfield(int w = 1, int h = 1, Tile* base = NULL);
    bool sizeCheck();
    virtual void print(std::ostream& os = std::cout);
    //mivel publikus, *felhasználó*biztos mozgatás
    virtual void moveTo(int X, int Y);
    int getX() const {return x;}
    int getY() const {return y;}
    const int getW() const {return width;}
    const int getH() const {return height;}
    virtual ~Playfield();
};



#endif // PLAYFIELD
