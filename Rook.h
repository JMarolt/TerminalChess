#ifndef ROOK_H
#define ROOK_H
#include "Piece.h"
#include <string>

using namespace std;

class Rook : public Piece{
    public:
        Rook(char, char, char, int);
        Rook(string);
        vector<string> legalMoves(vector<Piece*>&, vector<string>&, bool, bool);
        vector<string> temporaryLegalMoves(vector<Piece*>&, vector<string>&, bool, bool);
        vector<string> legalMovesRestrictedByCheck(vector<Piece*>&, bool);

    private:
        string position;
        bool hasMoved;

};
#endif