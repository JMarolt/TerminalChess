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
    string str = "";
    str.push_back(team);
    str.push_back(pieceIdentifier);
    str.push_back(letterRank);
    string toAdd = to_string(numberRank);
    str.append(toAdd);
    this->position = str;
    startingPosition = position;
}

vector<string> Pawn::temporaryLegalMoves(vector<Piece*>& pieces, vector<string>& previousMoves, bool whiteTurn, bool isInCheck){
    char teamLetter = getInformation()[0];
    if(startingPosition != getInformation()){
        hasMoved = true;
    }
    vector<string> moves;
    int value = 1;
    if(getInformation()[0] == 'B') value = -1;
    bool blocked = true;
    if(getInformation()[3] < '8' && getInformation()[3] > '1'){
        string oneSpace = getPos();
        oneSpace[1] += value;
        if(!pieceOnLocation(pieces, oneSpace)){
            blocked = false;
            moves.push_back(oneSpace);
        }
    }
    if(hasMoved == false){
        if(!blocked){
            string twoSpaces = getPos();
            twoSpaces[1] += (value * 2);
            if(!pieceOnLocation(pieces, twoSpaces)){
                moves.push_back(twoSpaces);
            }
        }
    }
    //now check if it can move up diagonally to capture a piece(will check en passant later)
    string rightDiag = getPos();
    string leftDiag = getPos();
    rightDiag[0] = rightDiag[0] + value;
    leftDiag[0] = leftDiag[0] - value;
    rightDiag[1] += value;
    leftDiag[1] += value;
    if(getPieceOnLocation(pieces, rightDiag) != nullptr && getPieceOnLocation(pieces, rightDiag)->getInformation()[0] != teamLetter){
        moves.push_back(rightDiag);
    }
    if(getPieceOnLocation(pieces, leftDiag) != nullptr && getPieceOnLocation(pieces, leftDiag)->getInformation()[0] != teamLetter){
        moves.push_back(leftDiag);
    }

    //EN PASSANT TIME... yuck
    if((getInformation()[0] == 'W' && getInformation()[3] == '5') || (getInformation()[0] == 'B' && getInformation()[3] == '4')){
        string toRight = getPos();
        string toLeft = getPos();
        toRight[0] += value;
        toLeft[0] -= value;
        Piece* rightPiece = getPieceOnLocation(pieces, toRight);
        if(rightPiece != nullptr){
            if(rightPiece->getInformation()[0] != teamLetter && rightPiece->getInformation()[1] == 'P'){
                if(previousMoves.at(previousMoves.size() - 1).substr(0, 4) == rightPiece->getInformation()){
                    string oldRight = toRight;
                    oldRight[1] += (2 * value);
                    if(previousMoves.at(previousMoves.size() - 1).substr(4, 2) == oldRight){
                        oldRight[1] -= value;
                        moves.push_back(oldRight);
                    }
                }
            }
        }
        Piece* leftPiece = getPieceOnLocation(pieces, toLeft);
        if(leftPiece != nullptr){
            if(leftPiece->getInformation()[0] != teamLetter && leftPiece->getInformation()[1] == 'P'){
                if(previousMoves.at(previousMoves.size() - 1).substr(0, 4) == leftPiece->getInformation()){
                    string oldLeft = toLeft;
                    oldLeft[1] += (2 * value);
                    if(previousMoves.at(previousMoves.size() - 1).substr(4, 2) == oldLeft){
                        oldLeft[1] -= value;
                        moves.push_back(oldLeft);
                    }
                }
            }
        }
    }
    return moves;
}

vector<string> Pawn::legalMoves(vector<Piece*>& pieces, vector<string>& previousMoves, bool whiteTurn, bool isInCheck){
    vector<string> tempLegalMoves = temporaryLegalMoves(pieces, previousMoves, whiteTurn, isInCheck);
    return tempLegalMoves;
}

vector<string> Pawn::legalMovesRestrictedByCheck(vector<Piece*>& pieces, bool whiteTurn){
    vector<string> temp;
    return temp;
}

void Pawn::promote(vector<Piece*>& pieces, Piece* pawnToReplace, int choice){
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
            pawnInfo[1] = 'Q';
            Queen* queen = new Queen(pawnInfo);
            pieces.push_back(queen);
            break;
        }
        case 2:
        {
            pawnInfo[1] = 'B';
            Bishop* bishop = new Bishop(pawnInfo);
            pieces.push_back(bishop);
            break;
        }
        case 3:
        {
            pawnInfo[1] = 'R';
            Rook* rook = new Rook(pawnInfo);
            pieces.push_back(rook);
            break;
        }
        case 4:
        {
            pawnInfo[1] = 'N';
            Knight* knight = new Knight(pawnInfo);
            pieces.push_back(knight);
            break;
        }
    }
}

