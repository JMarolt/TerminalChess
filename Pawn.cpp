#include <vector>
#include <string>
#include <iostream>

#include "Pawn.h"
#include "Queen.h"
#include "Bishop.h"
#include "Rook.h"
#include "Knight.h"

using std::string;
using std::vector;

Pawn::Pawn(char team, char pieceIdentifier, char letterRank, int numberRank) : Piece(team, pieceIdentifier, letterRank, numberRank){
    hasMoved = false;
}

vector<string> Pawn::legalMoves(vector<Piece*>& pieces){
    vector<string> moves;
    if(position[0] == 'W'){
        bool blocked = true;
        if(position[3] < '8'){
            string oneSpace = position;
            oneSpace[3] = position[3] + 1;
            if(!pieceOnLocation(pieces, oneSpace)){
                blocked = false;
                moves.push_back(oneSpace);
            }
        }
        if(hasMoved == false){
            if(!blocked){
                string twoSpaces = position;
                if(!pieceOnLocation(pieces, twoSpaces)){
                    moves.push_back(twoSpaces);
                }
            }
        }
    }else{
        bool blocked = true;
        if(position[3] > '1'){
            string oneSpace = position;
            oneSpace[3] = position[3] + 1;
            if(!pieceOnLocation(pieces, oneSpace)){
                blocked = false;
                moves.push_back(oneSpace);
            }
        }
        if(hasMoved == false){
            if(!blocked){
                string twoSpaces = position;
                if(!pieceOnLocation(pieces, twoSpaces)){
                    moves.push_back(twoSpaces);
                }
            }
        }
    }
    return moves;
}

void Pawn::promote(vector<Piece*> pieces, Pawn* pawnToReplace, int choice){
    string pawnInfo = pawnToReplace->getInformation();
    for(unsigned i = 0; i < pieces.size(); i++){
        if(pieces.at(i) == pawnToReplace){
            pieces.erase(pieces.begin() + i);
            delete pawnToReplace;
        }
    }
    switch(choice){
        case 1:
        {
            Queen* queen = new Queen(pawnInfo);
            pieces.push_back(queen);
            break;
        }
        case 2:
        {
            Bishop* bishop = new Bishop(pawnInfo);
            pieces.push_back(bishop);
            break;
        }
        case 3:
        {
            Rook* rook = new Rook(pawnInfo);
            pieces.push_back(rook);
            break;
        }
        case 4:
        {
            Knight* knight = new Knight(pawnInfo);
            pieces.push_back(knight);
            break;
        }
    }
}

