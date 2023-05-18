#ifndef QUEEN_H
#define QUEEN_H
#include "Piece.h"
#include <string>

using namespace std;

class Queen : public Piece{
    public:
        Queen(char, char, char, int);
        Queen(string);
        vector<string> legalMoves(vector<Piece*>&, vector<string>&, bool);
        vector<string> temporaryLegalMoves(vector<Piece*>&, vector<string>&, bool);
        void legalMovesRestrictedByCheck(vector<Piece*>&, vector<string>&, vector<string>&, bool);

    private:
        string position;
        

};
#endif