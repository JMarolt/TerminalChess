#include <vector>
#include <string>
#include <iostream>

#include "Queen.h"

Queen::Queen(char team, char pieceIdentifier, char letterRank, int numberRank) : Piece(team, pieceIdentifier, letterRank, numberRank){}

Queen::Queen(std::string information) : Piece(information){}

std::vector<std::string> Queen::legalMoves(std::vector<Piece*>& pieces){
    std::vector<std::string> moves;
    return moves;
}