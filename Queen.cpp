#include <vector>
#include <string>
#include <iostream>

#include "Queen.h"

using namespace std;

Queen::Queen(char team, char pieceIdentifier, char letterRank, int numberRank) : Piece(team, pieceIdentifier, letterRank, numberRank){}

Queen::Queen(string information) : Piece(information){}

vector<string> Queen::legalMoves(vector<Piece*>& pieces, vector<string>& previousMoves, bool whiteTurn, bool isInCheck){
    vector<string> allLegalMoves = temporaryLegalMoves(pieces, previousMoves, whiteTurn, isInCheck);
    return allLegalMoves;
}

vector<string> Queen::temporaryLegalMoves(vector<Piece*>& pieces, vector<string>& previousMoves, bool whiteTurn, bool isInCheck){
    vector<string> moves;
    char teamLetter = getInformation()[0];
    int i;
    //left
    string pos = getPos();
    pos[0] -= 1;
    for(i = 0; i < 8; i++){
        if(pos[0] < 'a'){
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
    }
    //right
    pos = getPos();
    pos[0] += 1;
    for(i = 0; i < 8; i++){
        if(pos[0] > 'h'){
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
    }
    //down
    pos = getPos();
    pos[1] -= 1;
    for(i = 0; i < 8; i++){
        if(pos[1] < '1'){
            break;
        }
        if(pieceOnLocation(pieces, pos)){
            if(getPieceOnLocation(pieces, pos)->getInformation()[0] != teamLetter){
                moves.push_back(pos);
            }
            break;
        }
        moves.push_back(pos);
        pos[1] -= 1;
    }
    //up
    pos = getPos();
    pos[1] += 1;
    for(i = 0; i < 8; i++){
        if(pos[1] > '8'){
            break;
        }
        if(pieceOnLocation(pieces, pos)){
            if(getPieceOnLocation(pieces, pos)->getInformation()[0] != teamLetter){
                moves.push_back(pos);
            }
            break;
        }
        moves.push_back(pos);
        pos[1] += 1;
    }
    //bishop moves below

    //left up-diag
    pos = getPos();
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

vector<string> Queen::legalMovesRestrictedByCheck(vector<Piece*>& pieces, bool whiteTurn){
    vector<string> moves;
    return moves;
}