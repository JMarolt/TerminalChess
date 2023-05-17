#ifndef KNIGHT_H
#define KNIGHT_H
#include "Piece.h"
#include <string>

using namespace std;

class Knight : public Piece{
    public:
        Knight(char, char, char, int);
        Knight(string);
        vector<string> legalMoves(vector<Piece*>&, vector<string>&, bool, bool);
        vector<string> temporaryLegalMoves(vector<Piece*>&, vector<string>&, bool, bool);
        void legalMovesRestrictedByCheck(vector<Piece*>&, vector<string>&, vector<string>&, bool, bool);

    private:
        string position;
        

};
#endif