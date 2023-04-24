#include <vector>
#include <string>
#include <iostream>

#include "Bishop.h"

Bishop::Bishop(char team, char pieceIdentifier, char letterRank, int numberRank) : Piece(team, pieceIdentifier, letterRank, numberRank){}

Bishop::Bishop(std::string information) : Piece(information){}

std::vector<std::string> Bishop::legalMoves(std::vector<Piece*>& pieces){
    std::vector<std::string> moves;
    return moves;
}