#ifndef MINESWEEPER
#define MINESWEEPER

#include "playfield.hpp"
#include <iostream>

namespace tilegames{

//REDO
    /// \brief Aknakereső tábáblát, állapotát tárolja.
	class Minesweeper : public Playfield{
		enum Flagtypes{
			visible=1,
			bomb=2,
			flagged = 4
		};
		//körökre osztottság révén nem időt, hanem jelöléseket számol
 		int bombcount, moves;



		//adott bomba körül növeli értékeket
		void initval(int X, int Y, int **tilevals);
		//rekurzív felderítés, ha kijelölsz valamit
		bool showmore(int X, int Y);
		//kiírja az adott mezőt. azér külön func, mert sok kritértium
        void printTile(Tile* toprint, std::ostream& os = std::cout);
	public:
        ///Update
        //konstruktor, mert kell
		Minesweeper(int width, int height, int bombs = 0);

		//pillanatnyi koordináta zászlózása, ha lehet. ha 1, winner
		bool flag();


		bool show(){
		    int X = getX(), Y = getY();
		    bool out = showmore(X,Y);
		    moveTo(X,Y);
		    return out;
        }
        char obstructed(){
            if(getTile()->Flags() & visible)
                return getTile()->GFX();
            if(getTile()->Flags() & flagged)
                return '!';
            return '#';
        }
        void print(std::ostream& os = std::cout);
        int remBombs() const {return bombcount;}
        int turns() const {return moves;}
        bool sizeCheck();
	};
}

#endif

