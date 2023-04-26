#ifndef PAWN_H
#define PAWN_H
#include "Piece.h"
#include <string>

class Pawn : public Piece{
    public:
        Pawn(char, char, char, int);
        std::vector<std::string> legalMoves(std::vector<Piece*>&, std::vector<std::string>&, bool, bool);
        std::vector<std::string> temporaryLegalMoves(std::vector<Piece*>&, std::vector<std::string>&, bool, bool);
        std::vector<std::string> legalMovesRestrictedByCheck(std::vector<Piece*>&, bool);
        void setHasMoved(bool moved){
            this->hasMoved = moved;
        }
        void promote(std::vector<Piece*>&, Piece*, int);
        void setTurnAmount(int turns){
            this->turnsSinceFirstMove = turns;
        }
        int getNumberOfTurns(){
            return turnsSinceFirstMove;
        }
        //en passant

    private:
        std::string position;
        std::string startingPosition;
        bool hasMoved;
        int turnsSinceFirstMove;

};
#endif