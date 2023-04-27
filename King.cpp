#include <vector>
#include <string>
#include <iostream>

#include "King.h"

using namespace std;

King::King(char team, char pieceIdentifier, char letterRank, int numberRank) : Piece(team, pieceIdentifier, letterRank, numberRank){
    hasMoved = false;
    string str = "";
    str.push_back(team);
    str.push_back(pieceIdentifier);
    str.push_back(letterRank);
    string toAdd = to_string(numberRank);
    str.append(toAdd);
    this->position = str;
    startingPosition = position;
}

vector<string> King::legalMoves(vector<Piece*>& pieces, vector<string>& previousMoves, bool whiteTurn, bool isInCheck){
    vector<string> allLegalMoves = temporaryLegalMoves(pieces, previousMoves, whiteTurn, isInCheck);
    return allLegalMoves;
}

vector<string> King::temporaryLegalMoves(vector<Piece*>& pieces, vector<string>& previousMoves, bool whiteTurn, bool isInCheck){
    vector<string> moves;
    if(startingPosition != getInformation()){
        hasMoved = true;
    }
    char teamLetter = getInformation()[0];
    string pos = getPos();
    //up-left
    pos[0] -= 1;
    pos[1] += 1;
    if(pos[0] >= 'a' && pos[1] <= '8'){
        if(pieceOnLocation(pieces, pos)){
            if(getPieceOnLocation(pieces, pos)->getInformation()[0] != teamLetter){
                moves.push_back(pos);
            }
        }else{
            moves.push_back(pos);
        }
    }
    //left
    pos = getPos();
    pos[0] -= 1;
    if(pos[0] >= 'a'){
        if(pieceOnLocation(pieces, pos)){
            if(getPieceOnLocation(pieces, pos)->getInformation()[0] != teamLetter){
                moves.push_back(pos);
            }
        }else{
            moves.push_back(pos);
        }
    }
    //left down
    pos = getPos();
    pos[0] -= 1;
    pos[1] -= 1;
    if(pos[0] >= 'a' && pos[1] >= '1'){
        if(pieceOnLocation(pieces, pos)){
            if(getPieceOnLocation(pieces, pos)->getInformation()[0] != teamLetter){
                moves.push_back(pos);
            }
        }else{
            moves.push_back(pos);
        }
    }
    //down
    pos = getPos();
    pos[1] -= 1;
    if(pos[1] >= '1'){
        if(pieceOnLocation(pieces, pos)){
            if(getPieceOnLocation(pieces, pos)->getInformation()[0] != teamLetter){
                moves.push_back(pos);
            }
        }else{
            moves.push_back(pos);
        }
    }
    //down right
    pos = getPos();
    pos[0] += 1;
    pos[1] -= 1;
    if(pos[0] <= 'h' && pos[1] >= '1'){
        if(pieceOnLocation(pieces, pos)){
            if(getPieceOnLocation(pieces, pos)->getInformation()[0] != teamLetter){
                moves.push_back(pos);
            }
        }else{
            moves.push_back(pos);
        }
    }
    //right
    pos = getPos();
    pos[0] += 1;
    if(pos[0] <= 'h'){
        if(pieceOnLocation(pieces, pos)){
            if(getPieceOnLocation(pieces, pos)->getInformation()[0] != teamLetter){
                moves.push_back(pos);
            }
        }else{
            moves.push_back(pos);
        }
    }
    //right up
    pos = getPos();
    pos[0] += 1;
    pos[1] += 1;
    if(pos[0] <= 'h' && pos[1] <= '8'){
        if(pieceOnLocation(pieces, pos)){
            if(getPieceOnLocation(pieces, pos)->getInformation()[0] != teamLetter){
                moves.push_back(pos);
            }
        }else{
            moves.push_back(pos);
        }
    }
    //up
    pos = getPos();
    pos[1] += 1;
    if(pos[1] <= '8'){
        if(pieceOnLocation(pieces, pos)){
            if(getPieceOnLocation(pieces, pos)->getInformation()[0] != teamLetter){
                moves.push_back(pos);
            }
        }else{
            moves.push_back(pos);
        }
    }
    //castle time
    if(!hasMoved){
        //king side
        pos = getPos();
        pos[0] += 1;
        if(!pieceOnLocation(pieces, pos)){
            pos[0] += 1;
            if(!pieceOnLocation(pieces, pos)){
                pos[0] += 1;
                Piece* isRook = getPieceOnLocation(pieces, pos);
                if(isRook != nullptr){
                    if(isRook->getInformation()[1] == 'R' && !(isRook->moved())){
                        pos[0] -= 1;
                        moves.push_back(pos);
                    }
                }
            }
        }
        //queen side
        pos = getPos();
        pos[0] -= 1;
        if(!pieceOnLocation(pieces, pos)){
            pos[0] -= 1;
            if(!pieceOnLocation(pieces, pos)){
                pos[0] -= 1;
                if(!pieceOnLocation(pieces, pos)){
                    pos[0] -= 1;
                    Piece* isRook = getPieceOnLocation(pieces, pos);
                    if(isRook != nullptr){
                        if(isRook->getInformation()[1] == 'R' && !(isRook->moved())){
                            pos[0] += 2;
                            moves.push_back(pos);
                        }
                    }
                }
            }
        }
    }

    return moves;
}

vector<string> King::legalMovesRestrictedByCheck(vector<Piece*>& pieces, bool whiteTurn){
    vector<string> moves;
    return moves;
}