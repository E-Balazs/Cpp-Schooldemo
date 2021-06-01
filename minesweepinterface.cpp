#include "minesweepinterface.hpp"
#include <iostream>
#include <fstream>

using namespace tilegames;

MinesweeperInterface::MinesweeperInterface(){
    board = NULL;
}

void MinesweeperInterface::start(){
    std::cout << "A K N A K E R E S O" << std::endl << std::endl << std::endl;
    std::cout << "Hagyomanyos jatekszabalyok: a palyan aknak vannak elhelyezve. " << std::endl;
    std::cout << "A palyan a pillanatnyi poziciot az @ karater jelzi" << std::endl;
    std::cout << "Mozogni a palyan a [b]alra [j]obbra, [f]el [l]e karakterekkel" << std::endl;
    std::cout << "vagy numpaddal, akar atlosan is lehet." << std::endl << std::endl;
    std::cout << "Mezot felfedni a [+] vagy [5] karakterrel, aknanak jelolni a [!] vagy [*] karakterrel lehet." << std::endl << std::endl;
    std::cout << "Informaciot a pillanatnyi allasrol az [i] karakterrel lehet elerni" << std::endl;
    std::cout << "Kilepni a [0] karakterrel lehet. A jatekellast nem lehet elmenteni" << std::endl;

    String line;
    while(true){
        std::cout << "Valassz nehezsegi fokozatot a szogletes zarojelek kozti szam beirasaval!" << std::endl << std::endl;
        std::cout << "[1] kezdo" << std::endl << "[2] kozepes" << std::endl << "[3] nehez" << std::endl;
        std::cout << "[0] kilep" <<  std::endl << std::endl;
        std::cin >> line;
        if(line.size() < 1){
            std::cout << "Kerlek valassz a leheosegek kozul!" << std::endl;
            continue;
        }
        switch(line[0]){
        case '0':
            return;
        case '1':
            w = SEasy;
            h = SEasy;
            bombs = BEasy;
            break;
        case '2':
            w = SRegular;
            h = SRegular;
            bombs = BRegular;
            break;
        case '3':
            w = WChallange;
            h = HChallange;
            bombs = BChallange;
            break;
        default:
            std::cout << "Kerlek valassz a leheosegek kozul!" << std::endl;
            continue;
        }
        game();
    }
}

void MinesweeperInterface::game(){
    board = new Minesweeper(w,h,bombs);
    board->print();
    int result = gameLoop();
    while(result == 0){
        for(int i = 0; i < 25; ++i)
            std::cout << std::endl;
        board->print();
        result = gameLoop();
    }
    switch(result){
    case 1:
        std::cout << "Sikerult! B)" << std::endl;
        break;
    case -1:
        std::cout << "B U M M! X(" << std::endl;
        break;
    case 2:
        std::cout << "Jatek megszakitva." << std::endl;
        break;
    default:
        throw "HIBA!!!!!";
    }
    info();
    delete board;
    board = NULL;
    for(int i = 0; i < 25; ++i)
        std::cout << std::endl;

}

int MinesweeperInterface::gameLoop(){
    String line;
    std::cin >> line;
    if(line.size() < 1){
        std::cout << "Nincs muvelet!";
    }
    else{
        int currX = board->getX(), currY = board->getY();
        switch(line[0]){
        case '1':
            board->moveTo(currX-1,currY+1);
            break;
        case '2':
        case 'l':
        case 'L':
            board->moveTo(currX,currY+1);
            break;
        case '3':
            board->moveTo(currX+1,currY+1);
            break;
        case '4':
        case 'b':
        case 'B':
            board->moveTo(currX-1,currY);
            break;
        case '6':
        case 'j':
        case 'J':
            board->moveTo(currX+1,currY);
            break;
        case '7':
            board->moveTo(currX-1,currY-1);
            break;
        case '8':
        case 'f':
        case 'F':
            board->moveTo(currX,currY-1);
            break;
        case '9':
            board->moveTo(currX+1,currY-1);
            break;
        case '+':
        case '5':
            return board->show() * (-1);
        case '*':
        case '!':
            return board->flag();
        case 'i':
        case 'I':
            info();
            break;
        case '0':
            std::cout << "Irj be meg egy 0-t a kilepes megerositesehez" << std::endl;
            std::cin >> line;
            if(line.size() > 0  && line[0] == '0')
                return 2;
            break;
        default:
            std::cout << "Nincs ilyen muvelet!" << std::endl;
            std::cout << "ENTER a folytatashoz..." << std::endl;
            std::cin.get();
            break;
        }
    }

    return 0;
}

void MinesweeperInterface::info(){
    std::cout << "Palya:" << w << 'x' << h <<std::endl;
    std::cout << "Hatralevo bombak: " << board->remBombs() << std::endl;
    std::cout << "Eddigi lepesek: " << board->turns() << std::endl;
    std::cout << "Pillanatnyi pozicion: " << board->obstructed() << std::endl;
    std::cout << "ENTER a folytatashoz..." << std::endl;

    std::cin.get();
}
