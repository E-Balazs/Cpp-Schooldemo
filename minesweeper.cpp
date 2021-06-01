#include "minesweeper.hpp"

#define JPORTA

#include <ctime>
#include <random>
#include <cstdlib>

using namespace tilegames;



Minesweeper::Minesweeper(const int width, const int height, int bombs):Playfield(width, height),bombcount(bombs){
	///GUARD BEGIN

	if(bombcount > width*height){
		bombcount = width*height;
	}
	else if(bombcount <= 0){
		bombcount = ((width*height)/9)+1;  //~12%, talán nem túl nehéz default
	}

	///GUARD END
	moves = 0;
	moveTo(0,0);
	//random seed

	#ifndef JPORTA
	std::srand(std::time(0));
	#endif // JPORTA
	#ifdef JPORTA
	std::srand(3);
	#endif // JPORTA

    //0-ra inicializálás
	int** tilevals = new int*[height];
	for(int i = 0;i < height; ++i){
		tilevals[i] = new int[width];
		for(int j = 0; j < width; ++j){
			tilevals[i][j] = 0;
		}
	}

	//bombák felrakása



	int currbombs = 0;
	while(currbombs < bombcount){
		int bx = std::rand()%width;
		int by = std::rand()%height;//igen, teljesen random. Ha minden kockára bombát raksz, eltart egy ideig.
		moveTo(bx, by);
		if(!getTile()){
			setTile(new Tile('X',bomb));
			initval(bx,by,tilevals);        //int tömb, amiben a közeli bombákat mérjük
			++currbombs;
		}
	}

	for(int Y = 0; Y < height; ++Y){
		for(int X = 0; X < width; ++X){
            moveTo(X,Y);
			if(!getTile()){                          //ha még nincs bomba

				setTile(new Tile('0'+tilevals[Y][X]));  //az előre körbenézett bombák alapján lerakjuk a terepet
			}
            #ifdef DEBUG
            std::cout << getTile()->GFX();
            #endif // DEBUG
		}
		#ifdef DEBUG
		std::cout << std::endl;
		#endif // DEBUG
		delete[] tilevals[Y];                               //töröljük a már felesleges számlálót
	}
	delete[] tilevals;
	moveTo(0,0);
}


void Minesweeper::initval(int X, int Y, int **tilevals){
	for(int dy = Y-1; dy < Y+2; ++dy){
		for(int dx = X-1; dx < X+2; ++dx){                  //8 irányba körbenéz
			if(((dy | dx) < 0) || dy >= getH() || dx >= getW())   //pályán belül maradás
				{continue;}
			++tilevals[dy][dx];                             //éppeni kocka - ami bomba - körül növeljük az értékeket
		}
	}
}


bool Minesweeper::showmore(int X, int Y){
	if(!(tryMove(X,Y))) // táblán kívül vagyunk?
		{return 0;}
	int& tileflags = getTile()->Flags();            //mutatót odatettük
    if(tileflags & visible || tileflags & flagged)  //már felfedett/megjelölt kocka?
		{return 0;}
	tileflags |= visible;
	++moves;
	if(getTile()->GFX() != '0'){               //ha nem 0
		if(getTile()->Flags() & bomb)  //ha bomba
            {return 1;}                 //akkor RIP
		return 0;
    }
	for(int dy = Y-1; dy < Y+2; ++dy){      //körül nézzük
		for(int dx = X-1; dx < X+2; ++dx){  //8 irányba
			showmore(dx,dy);
		}
	}
	return 0; //nem volt bomba és körbe felderítettünk, úgyhogy OK
}


bool Minesweeper::flag(){
	if(getTile()->Flags() & visible)   //ha már felfedett kocka
		{return false;}                 //off
	++moves;
	getTile()->Flags() ^= flagged;     //átbillentjük a zászló bitet
	if(getTile()->Flags() & bomb){         //ha bomba
		if (getTile()->Flags() & flagged)  //bejelöltük
			{--bombcount;}                  //akkorjó
		else                                //amúgy
			{++bombcount;}                  //visszaszedjük
	}

	return bombcount < 1;
}


void Minesweeper::printTile(Tile* toprint, std::ostream& os){
    if(toprint->Flags() & flagged){
        os << '!';
    }
    else if(toprint->Flags() & visible){
        char tilegfx = toprint->GFX();
        switch (tilegfx){
        case '0':
            os << ' ';
            break;
        default:
            os << tilegfx;
            break;
        }

    }
    else{os << '#';
    }
}

void Minesweeper::print(std::ostream& os){
    for(int i = 0; i < getH(); ++i){
        for(int j = 0; j < getW(); ++j){
            if(i == getY() && j == getX())
                os << "@";
            else
                printTile(getTile(j,i), os);
        }
        //standard konzolméret miatt
        if(getH() < 80)
            os << std::endl;
    }
}
