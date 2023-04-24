#include <vector>
#include <string>
#include <iostream>

#include "King.h"

King::King(char team, char pieceIdentifier, char letterRank, int numberRank) : Piece(team, pieceIdentifier, letterRank, numberRank){}

std::vector<std::string> King::legalMoves(std::vector<Piece*>& pieces){
    std::vector<std::string> moves;
    return moves;
}