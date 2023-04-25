#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include <unordered_set>
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
        //stores all the pieces currently on the board
        vector<Piece*> pieces;
        //stores all the moves that have happened throughout the game
        //key is piece info and value is the move
        //key will be saying black pawn(BP) for example 
        unordered_set<string, string> previousMoves;
        int turn;

        void sortByPosition(vector<Piece*>&);
        string pieceOnLocation(vector<Piece*>&, char, int);
        Piece* getPiece(vector<Piece*>&, string);
        void addEnPassantLegalMoves();

};
#endif