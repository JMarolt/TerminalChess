#ifndef BISHOP_H
#define BISHOP_H
#include "Piece.h"
#include <string>
#include <vector>

using namespace std;

class Bishop : public Piece{
    public:
        Bishop(char, char, char, int);
        Bishop(string);
        vector<string> legalMoves(vector<Piece*>&, vector<string>&, bool);
        vector<string> temporaryLegalMoves(vector<Piece*>&, vector<string>&, bool);
        void legalMovesRestrictedByCheck(vector<Piece*>&, vector<string>&, vector<string>&, bool);

    private:
        string position;
        

};
#endif