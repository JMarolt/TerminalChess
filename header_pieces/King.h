#ifndef KING_H
#define KING_H
#include "Piece.h"
#include <string>

using namespace std;

class King : public Piece{
    public:
        King(char, char, char, int);
        vector<string> legalMoves(vector<Piece*>&, vector<string>&, bool);
        vector<string> temporaryLegalMoves(vector<Piece*>&, vector<string>&, bool);
        void legalMovesRestrictedByCheck(vector<Piece*>&, vector<string>&, vector<string>&, bool);

    private:
        string position;
        string startingPosition;
        bool hasMoved;
        

};
#endif