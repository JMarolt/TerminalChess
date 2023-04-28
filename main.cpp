#include "Board.h"
#include <iostream>

//g++ main.cpp Board.cpp Pawn.cpp Knight.cpp Rook.cpp Queen.cpp Bishop.cpp King.cpp -o main
int main(){
    Board* board = new Board();
    //std::cout << "\033[0mdefault colors\n";
    board->run();
    delete board;
    return 0;
}