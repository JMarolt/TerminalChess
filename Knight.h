#ifndef KNIGHT_H
#define KNIGHT_H
#include "Piece.h"
#include <string>

class Knight : public Piece{
    public:
        Knight(char, char, char, int);
        Knight(std::string);
        std::vector<std::string> legalMoves(std::vector<Piece*>&);

    private:
        std::string position;
        

};
#endif