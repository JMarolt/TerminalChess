#ifndef BISHOP_H
#define BISHOP_H
#include "Piece.h"
#include <string>

class Bishop : public Piece{
    public:
        Bishop(char, char, char, int);
        Bishop(std::string);
        std::vector<std::string> legalMoves(std::vector<Piece*>&);

    private:
        std::string position;
        

};
#endif