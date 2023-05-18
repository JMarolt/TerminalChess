#include "Board.h"
#include <iostream>

//g++ main.cpp Board.cpp src_pieces/Pawn.cpp src_pieces/Knight.cpp src_pieces/Rook.cpp src_pieces/Queen.cpp src_pieces/Bishop.cpp src_pieces/King.cpp -o main
int main(){
    Board* board = new Board();
    //board->runTests();
    board->run();
    delete board;
    return 0;
}