#include "playfield.hpp"

using namespace tilegames;


Playfield::Playfield(int w, int h, Tile* base){
    if(w < 1) w = 1;
    if(h < 1) h = 1;
    width = w;
    height = h;

    grid = new Tile**[height];
    for(int i = 0; i < height; ++i){
        grid[i] = new Tile*[width];
        for(int j = 0; j < width; ++j)
            grid[i][j] = (base ? new Tile(*base) : base);
    }

}

void Playfield::clear(){
    for(int h = 0; h < height; ++h)
        for(int w = 0; w < width; ++w)
            if(grid[h][w]){
                delete grid[h][w];
                grid[h][w] = NULL;
            }
}

Playfield::~Playfield(){
    clear();
    for(int h = 0; h < height; ++h)
        delete[] grid[h];
    delete[] grid;
}

bool Playfield::tryMove(int X, int Y){
    if((X | Y )< 0 || X >= width || Y >= height)
        return false;
    x = X;
    y = Y;
    return true;
}

void Playfield::moveTo(int X, int Y){
    //Biztosítás túl/alulindexelés ellen, mert nem szeretek throwolással foglalkozni
	if(X < 0) { X= 0; }
	else if(X >= width) { X = width-1;}
	if(Y < 0) { Y = 0;}
	else if(Y >= height) { Y = height-1;}
	//átállítás
	x = X;
	y = Y;

}

bool Playfield::sizeCheck(){
    if(width <= 80 && height <= 23)
        return 1;
    return 0;
}

//kiírás ostreamre
void Playfield::print(std::ostream& os){
    for(int i = 0; i < height; ++i){
        for(int j = 0; j < width; ++j){
            printTile(grid[i][j], os);
        }
        //standard konzolméret miatt
        if(width < 80)
            os << std::endl;
    }
}
