#include <vector>
#include <string>
#include <iostream>

#include "Bishop.h"

using namespace std;

Bishop::Bishop(char team, char pieceIdentifier, char letterRank, int numberRank) : Piece(team, pieceIdentifier, letterRank, numberRank){
    string str = "";
    str.push_back(team);
    str.push_back(pieceIdentifier);
    str.push_back(letterRank);
    string toAdd = to_string(numberRank);
    str.append(toAdd);
    this->position = str;
}

Bishop::Bishop(std::string information) : Piece(information){}

vector<string> Bishop::legalMoves(vector<Piece*>& pieces, vector<string>& previousMoves, bool whiteTurn, bool& isInCheck){
    vector<string> allLegalMoves = temporaryLegalMoves(pieces, previousMoves, whiteTurn, isInCheck);
    
        vector<string> removeLegalMoves = legalMovesRestrictedByCheck(pieces, previousMoves, whiteTurn, isInCheck);
        for(int i = 0; i < allLegalMoves.size(); i++){
            for(int k = 0; k < removeLegalMoves.size(); k++){
                if((removeLegalMoves.at(k)[1] == 'B') && (allLegalMoves.at(i) == removeLegalMoves.at(k).substr(2, 2))){
                    allLegalMoves.erase(allLegalMoves.begin() + i);
                    removeLegalMoves.erase(removeLegalMoves.begin() + k);
                    i--;
                    k--;
                    break;
                }
            }
        }
    
    return allLegalMoves;
}

vector<string> Bishop::temporaryLegalMoves(vector<Piece*>& pieces, vector<string>& previousMoves, bool whiteTurn, bool& isInCheck){
    vector<string> moves;
    char teamLetter = getInformation()[0];
    int i;
    //left up-diag
    string pos = getPos();
    pos[0] -= 1;
    pos[1] += 1;
    for(i = 0; i < 8; i++){
        if(pos[0] < 'a' || pos[1] > '8'){
            break;
        }
        if(pieceOnLocation(pieces, pos)){
            if(getPieceOnLocation(pieces, pos)->getInformation()[0] != teamLetter){
                moves.push_back(pos);
            }
            break;
        }
        moves.push_back(pos);
        pos[0] -= 1;
        pos[1] += 1;
    }
    //left down-diag
    pos = getPos();
    pos[0] -= 1;
    pos[1] -= 1;
    for(i = 0; i < 8; i++){
        if(pos[0] < 'a' || pos[1] < '1'){
            break;
        }
        if(pieceOnLocation(pieces, pos)){
            if(getPieceOnLocation(pieces, pos)->getInformation()[0] != teamLetter){
                moves.push_back(pos);
            }
            break;
        }
        moves.push_back(pos);
        pos[0] -= 1;
        pos[1] -= 1;
    }
    //right down-diag
    pos = getPos();
    pos[0] += 1;
    pos[1] -= 1;
    for(i = 0; i < 8; i++){
        if(pos[0] > 'h' || pos[1] < '1'){
            break;
        }
        if(pieceOnLocation(pieces, pos)){
            if(getPieceOnLocation(pieces, pos)->getInformation()[0] != teamLetter){
                moves.push_back(pos);
            }
            break;
        }
        moves.push_back(pos);
        pos[0] += 1;
        pos[1] -= 1;
    }
    //right up-diag
    pos = getPos();
    pos[0] += 1;
    pos[1] += 1;
    for(i = 0; i < 8; i++){
        if(pos[0] > 'h' || pos[1] > '8'){
            break;
        }
        if(pieceOnLocation(pieces, pos)){
            if(getPieceOnLocation(pieces, pos)->getInformation()[0] != teamLetter){
                moves.push_back(pos);
            }
            break;
        }
        moves.push_back(pos);
        pos[0] += 1;
        pos[1] += 1;
    }
    return moves;
}