#ifndef KNIGHT_H
#define KNIGHT_H
#include "Piece.h"
#include <string>

using namespace std;

class Knight : public Piece{
    public:
        Knight(char, char, char, int);
        Knight(string);
        vector<string> legalMoves(vector<Piece*>&, vector<string>&, bool);
        vector<string> temporaryLegalMoves(vector<Piece*>&, vector<string>&, bool);
        void legalMovesRestrictedByCheck(vector<Piece*>&, vector<string>&, vector<string>&, bool);

    private:
        string position;
        

};
#endif