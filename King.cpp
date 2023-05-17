#include <vector>
#include <string>
#include <iostream>

#include "King.h"

using namespace std;

King::King(char team, char pieceIdentifier, char letterRank, int numberRank) : Piece(team, pieceIdentifier, letterRank, numberRank){
    this->hasMoved = false;
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
    legalMovesRestrictedByCheck(pieces, previousMoves, allLegalMoves, whiteTurn, isInCheck);
    return allLegalMoves;
}

vector<string> King::temporaryLegalMoves(vector<Piece*>& pieces, vector<string>& previousMoves, bool whiteTurn, bool isInCheck){
    if(hasMoved == false){
        for(int i = 0; i < pieces.size(); i++){
            if(pieces.at(i) == this && pieces.at(i)->hasMoved == true){
                this->hasMoved = true;
            }
        }
    }
    vector<string> moves;
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
                    if(isRook->getInformation()[1] == 'R' && !(isRook->hasMoved)){
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
                        if(isRook->getInformation()[1] == 'R' && !(isRook->hasMoved)){
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

void King::legalMovesRestrictedByCheck(vector<Piece*>& pieces, vector<string>& previousMoves, vector<string>& tempLegalMoves, bool whiteTurn, bool isInCheck){
    //basically, in here we just have to move the piece to each of its temp legal moves and if the king remains in check, then we can remove it
    //we will call erase in tempLegalMoves
    string thisKingPos;
    for(int i = 0; i < pieces.size(); i++){
        if(whiteTurn){
            if(pieces.at(i)->getInformation()[0] == 'B'){
                continue;
            }
        }else{
            if(pieces.at(i)->getInformation()[0] == 'W'){
                continue;
            }
        }
        if(pieces.at(i)->getInformation()[1] == 'K'){
            thisKingPos = pieces.at(i)->getPos();
            break;
        }
    }

    for(int i = 0; i < tempLegalMoves.size(); i++){
        string originalPos = getPos();
        //here we temporarily remove a piece that the king moves to
        Piece* tempCaptured = nullptr;
        for(int k = 0; k < pieces.size(); k++){
            if(whiteTurn){
                if(pieces.at(k)->getInformation()[0] == 'W'){
                    continue;
                }
            }else{
                if(pieces.at(k)->getInformation()[0] == 'B'){
                    continue;
                }
            }
            if(pieces.at(k)->getPos() == tempLegalMoves.at(i)){
                tempCaptured = pieces.at(k);
                pieces.erase(pieces.begin() + k);
                k--;
            }
        }
        this->setInformation(getInformation().substr(0, 2) + tempLegalMoves.at(i));
        thisKingPos = this->getPos();
        bool noMove = false;
        //go through pieces of the other team and check if it checks the king
        for(int j = 0; j < pieces.size(); j++){
            //if it is white's turn, then we need to check if the black pieces can now check
            if(whiteTurn){
                if(pieces.at(j)->getInformation()[0] == 'W'){
                    continue;
                }
            }else{
                if(pieces.at(j)->getInformation()[0] == 'B'){
                    continue;
                }
            }
            //check if legal moves of the other team are now/still on the king
            vector<string> legal_Moves = pieces.at(j)->temporaryLegalMoves(pieces, previousMoves, whiteTurn, isInCheck);
            for(int k = 0; k < legal_Moves.size(); k++){
                if(legal_Moves.at(k) == thisKingPos){
                    tempLegalMoves.erase(tempLegalMoves.begin() + i);
                    i--;
                    noMove = true;
                    break;
                }
            }
            if(noMove){
                break;
            }
        }
        this->setInformation(getInformation().substr(0, 2) + originalPos);
        thisKingPos = originalPos;
        if(tempCaptured != nullptr){
            pieces.push_back(tempCaptured);
        }
    }
}