#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>
#include "header_pieces\Piece.h"

using namespace std;

class Board{

    public:
        Board();
        void run();
        void runTests();
    private:
        //stores all the pieces currently on the board
        vector<Piece*> pieces;
        //stores all the moves that have happened throughout the game
        //key is piece info and value is the move(i.e. where it previously was since our key will hold our current pos)
        vector<string> previousMoves;
        
        void init();
        void initVector(vector<Piece*>&);
        void sortByPosition(vector<Piece*>&);
        string pieceOnLocation(vector<Piece*>&, char, int);
        Piece* getPiece(vector<Piece*>&, string);
        bool isCheckmate(bool);
        bool isStalemate(bool);

        void printBoardPieces();
        void printBoardWhitePerspective();
        void printBoardFromSpectator();

        //test stuff
        void numberOfPositionsAfterMove(int);
        long long recursivePositionCount(int, vector<Piece*>&, vector<string>&, bool);
};
#endif