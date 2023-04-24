#include <vector>
#include <string>
#include <iostream>

#include "Knight.h"

Knight::Knight(char team, char pieceIdentifier, char letterRank, int numberRank) : Piece(team, pieceIdentifier, letterRank, numberRank){}

Knight::Knight(std::string information) : Piece(information){}

std::vector<std::string> Knight::legalMoves(std::vector<Piece*>& pieces){
    std::vector<std::string> moves;

    return moves;
}