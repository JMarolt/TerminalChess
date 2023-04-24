#ifndef QUEEN_H
#define QUEEN_H
#include "Piece.h"
#include <string>

class Queen : public Piece{
    public:
        Queen(char, char, char, int);
        Queen(std::string);
        std::vector<std::string> legalMoves(std::vector<Piece*>&);

    private:
        std::string position;
        

};
#endif