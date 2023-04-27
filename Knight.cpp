#include <vector>
#include <string>
#include <iostream>

#include "Knight.h"

using namespace std;

Knight::Knight(char team, char pieceIdentifier, char letterRank, int numberRank) : Piece(team, pieceIdentifier, letterRank, numberRank){
    string str = "";
    str.push_back(team);
    str.push_back(pieceIdentifier);
    str.push_back(letterRank);
    string toAdd = to_string(numberRank);
    str.append(toAdd);
    this->position = str;
}

Knight::Knight(string information) : Piece(information){}

vector<string> Knight::legalMoves(vector<Piece*>& pieces, vector<string>& previousMoves, bool whiteTurn, bool isInCheck){
    vector<string> allLegalMoves = temporaryLegalMoves(pieces, previousMoves, whiteTurn, isInCheck);
    return allLegalMoves;
}

vector<string> Knight::temporaryLegalMoves(vector<Piece*>& pieces, vector<string>& previousMoves, bool whiteTurn, bool isInCheck){
    //+2 rank + 1 file done
    //+2 rank - 1 file done
    //+1 rank + 2 file done
    //+1 rank - 2 file done
    //-1 rank + 2 file done
    //-1 rank - 2 file done
    //-2 rank + 1 file done
    //-2 rank - 1 file done
    vector<string> moves;
    char teamLetter = getInformation()[0];
    string pos = getPos();
    pos[0] += 1;
    pos[1] += 2;
    if(pos[0] <= 'h' && pos[1] <= '8'){
        if(pieceOnLocation(pieces, pos)){
            if(getPieceOnLocation(pieces, pos)->getInformation()[0] != teamLetter){
                moves.push_back(pos);
            }
        }else{
            moves.push_back(pos);
        }
    }
    pos = getPos();
    pos[0] -= 1;
    pos[1] += 2;
    if(pos[0] >= 'a' && pos[1] <= '8'){
        if(pieceOnLocation(pieces, pos)){
            if(getPieceOnLocation(pieces, pos)->getInformation()[0] != teamLetter){
                moves.push_back(pos);
            }
        }else{
            moves.push_back(pos);
        }
    }
    pos = getPos();
    pos[0] += 2;
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

    pos = getPos();
    pos[0] -= 2;
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

    pos = getPos();
    pos[0] += 2;
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

    pos = getPos();
    pos[0] -= 2;
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

    pos = getPos();
    pos[0] += 1;
    pos[1] -= 2;
    if(pos[0] <= 'h' && pos[1] >= '1'){
        if(pieceOnLocation(pieces, pos)){
            if(getPieceOnLocation(pieces, pos)->getInformation()[0] != teamLetter){
                moves.push_back(pos);
            }
        }else{
            moves.push_back(pos);
        }
    }

    pos = getPos();
    pos[0] -= 1;
    pos[1] -= 2;
    if(pos[0] >= 'a' && pos[1] >= '1'){
        if(pieceOnLocation(pieces, pos)){
            if(getPieceOnLocation(pieces, pos)->getInformation()[0] != teamLetter){
                moves.push_back(pos);
            }
        }else{
            moves.push_back(pos);
        }
    }
    return moves;
}

vector<string> Knight::legalMovesRestrictedByCheck(vector<Piece*>& pieces, bool whiteTurn){
    vector<string> moves;

    return moves;
}