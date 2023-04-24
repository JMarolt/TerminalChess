#ifndef KING_H
#define KING_H
#include "Piece.h"
#include <string>

class King : public Piece{
    public:
        King(char, char, char, int);
        std::vector<std::string> legalMoves(std::vector<Piece*>&);

    private:
        std::string position;
        

};
#endif