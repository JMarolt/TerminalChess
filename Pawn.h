#ifndef PAWN_H
#define PAWN_H
#include "Piece.h"
#include <string>

using namespace std;

class Pawn : public Piece{
    public:
        Pawn(char, char, char, int);
        vector<string> legalMoves(vector<Piece*>&, vector<string>&, bool, bool);
        vector<string> temporaryLegalMoves(vector<Piece*>&, vector<string>&, bool, bool);
        void promote(vector<Piece*>&, Piece*, int);
        void setTurnAmount(int turns){
            this->turnsSinceFirstMove = turns;
        }
        int getNumberOfTurns(){
            return turnsSinceFirstMove;
        }
        //en passant

    private:
        string position;
        string startingPosition;
        int turnsSinceFirstMove;

};
#endif