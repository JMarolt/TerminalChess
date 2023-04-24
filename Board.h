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
        void draw();
        void printBoardPieces();
        void printBoardWhitePerspective();
        void printBoardFromSpectator();
    private:
        vector<Piece*> pieces;
        int turn;

        void sortByPosition(vector<Piece*>&);
        string pieceOnLocation(vector<Piece*>&, char, int);
        Piece* getPiece(vector<Piece*>&, string);

};
#endif