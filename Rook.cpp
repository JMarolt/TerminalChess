#include <vector>
#include <string>
#include <iostream>

#include "Rook.h"

Rook::Rook(char team, char pieceIdentifier, char letterRank, int numberRank) : Piece(team, pieceIdentifier, letterRank, numberRank){}

Rook::Rook(std::string information) : Piece(information){}

std::vector<std::string> Rook::legalMoves(std::vector<Piece*>& pieces){
    std::vector<std::string> moves;
    return moves;
}