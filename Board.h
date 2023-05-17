#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include "Piece.h"

using namespace std;

class Board{

    public:
        Board();
        void init();
        void initVector(vector<Piece*>&);
        void run();
        void printBoardPieces();
        void printBoardWhitePerspective();
        void printBoardFromSpectator();
    private:
        //stores all the pieces currently on the board
        vector<Piece*> pieces;
        //stores all the moves that have happened throughout the game
        //key is piece info and value is the move(i.e. where it previously was since our key will hold our current pos)
        vector<string> previousMoves;
        
        void sortByPosition(vector<Piece*>&);
        string pieceOnLocation(vector<Piece*>&, char, int);
        Piece* getPiece(vector<Piece*>&, string);
        bool isCheckmate(bool);
        bool isStalemate(bool);

};
#endif