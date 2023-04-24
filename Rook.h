#ifndef ROOK_H
#define ROOK_H
#include "Piece.h"
#include <string>

class Rook : public Piece{
    public:
        Rook(char, char, char, int);
        Rook(std::string);
        std::vector<std::string> legalMoves(std::vector<Piece*>&);

    private:
        std::string position;
        

};
#endif