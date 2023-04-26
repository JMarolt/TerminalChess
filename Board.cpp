#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

#include "Board.h"
#include "Pawn.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Knight.h"

using namespace std;

Board::Board(){
    init();
}

void Board::initVector(vector<Piece*>& pieces){
    for(unsigned i = 0; i < 8; i++){
        Pawn* whitePawns = new Pawn('W', 'P', 'a' + i, 2);
        pieces.push_back(whitePawns);
    }
    for(unsigned i = 0; i < 8; i++){
        Pawn* blackPawns = new Pawn('B', 'P', 'a' + i, 7);
        pieces.push_back(blackPawns);
    }
    Bishop* bBishop1 = new Bishop('B', 'B', 'c', 8);
    Bishop* bBishop2 = new Bishop('B', 'B', 'f', 8);
    Bishop* wBishop1 = new Bishop('W', 'B', 'c', 1);
    Bishop* wBishop2 = new Bishop('W', 'B', 'f', 1);
    pieces.push_back(bBishop1);
    pieces.push_back(bBishop2);
    pieces.push_back(wBishop1);
    pieces.push_back(wBishop2);
    Knight* bKnight1 = new Knight('B', 'N', 'b', 8);
    Knight* bKnight2 = new Knight('B', 'N', 'g', 8);
    Knight* wKnight1 = new Knight('W', 'N', 'b', 1);
    Knight* wKnight2 = new Knight('W', 'N', 'g', 1);
    pieces.push_back(bKnight1);
    pieces.push_back(bKnight2);
    pieces.push_back(wKnight1);
    pieces.push_back(wKnight2);
    Rook* bRook1 = new Rook('B', 'R', 'a', 8);
    Rook* bRook2 = new Rook('B', 'R', 'h', 8);
    Rook* wRook1 = new Rook('W', 'R', 'a', 1);
    Rook* wRook2 = new Rook('W', 'R', 'h', 1);
    pieces.push_back(bRook1);
    pieces.push_back(bRook2);
    pieces.push_back(wRook1);
    pieces.push_back(wRook2);
    Queen* bQueen = new Queen('B', 'Q', 'd', 8);
    Queen* wQueen = new Queen('W', 'Q', 'd', 1);
    pieces.push_back(bQueen);
    pieces.push_back(wQueen);
    King* bKing = new King('B', 'K', 'e', 8);
    King* wKing = new King('W', 'K', 'e', 1);
    pieces.push_back(bKing);
    pieces.push_back(wKing);
    sortByPosition(pieces);
}

void Board::init(){
    initVector(this->pieces);
}

void Board::run(){
    printBoardWhitePerspective();
    bool whiteTurn = true;
    bool isInCheck = false;
    string input = "";
    string teamColorTurn = "White";
    while(input != "//"){
        whiteTurn == 1 ? teamColorTurn = "White" : teamColorTurn = "Black";
        cout << "What piece would would you like to move?" << "(" << teamColorTurn << " to move)" << "\n";
        cin >> input;
        if(input == "//"){
            break;
        }
        Piece* toBeMoved = getPiece(pieces, input);
        if(toBeMoved == nullptr){
            cout << "That is not a valid piece. Please try again\n";
            break;
        }

        if(toBeMoved->legalMoves(pieces, previousMoves, whiteTurn, isInCheck).size() == 0){
            cout << "This piece has no legal moves, please choose another piece\n";

        }

        cout << "Where would you like to move that piece to?\n";
        cin >> input;

        bool legal = false;
        for(int i = 0; i < toBeMoved->legalMoves(pieces, previousMoves, whiteTurn, isInCheck).size(); i++){
            if(toBeMoved->legalMoves(pieces, previousMoves, whiteTurn, isInCheck).at(i) == input){
                legal = true;
                break;
            }
        }
        if(legal){
            string previousLocation = toBeMoved->getPos();
            toBeMoved->makeMove(pieces, input);
            string newPrev = toBeMoved->getInformation().append(previousLocation);
            previousMoves.push_back(newPrev);
        }else{
            cout << "Legal Moves: ";
            for(int i = 0; i < toBeMoved->legalMoves(pieces, previousMoves, whiteTurn, isInCheck).size(); i++){
                cout << toBeMoved->legalMoves(pieces, previousMoves, whiteTurn, isInCheck).at(i) << ", ";
            }
            break;
        }
        //update pieces legal moves here
        whiteTurn = !whiteTurn;
        printBoardWhitePerspective();

        //check for stalemate and checkmate down here

        continue;
    }
}

void Board::printBoardPieces(){
    for(unsigned i = 0; i < pieces.size(); i++){
        cout << pieces.at(i)->getInformation() << ", ";
    }
}

//Prints the board sideways as if someone is spectating
void Board::printBoardFromSpectator(){
    //8 is size of chess board
    unsigned index = 0;
    for(unsigned i = 0; i < 8; i++){
        char file = i + 'a';
        for(unsigned rank = 0; rank < 8; rank++){
            if(pieces.at(index)->getInformation()[2] == file && pieces.at(index)->getInformation()[3] == '1' + rank){
                cout << pieces.at(index)->getInformation() << " ";
                index++;
            }else{
                cout << "---- ";
            }
        }   
        cout << endl;
    }
}

//prints the board from white's perspective(white on our side, black on far side)
void Board::printBoardWhitePerspective(){
    //8 is size of chess board
    for(int rank = 7; rank >= 0; rank--){
        for(int k = 0; k < 8; k++){
            char file = 'a' + k;
            cout << pieceOnLocation(pieces, file, rank + '1') << " ";
        }   
        cout << endl;
    }
}

//selection sort(n^2) cuz at most 32 elements
void Board::sortByPosition(vector<Piece*>& pieces){
    for(int i = 0; i < pieces.size(); i++){
        string lowest = pieces.at(i)->getPos();
        int lowestIndex = i;
        for(int k = i; k < pieces.size(); k++){
            if(pieces.at(k)->getPos() < lowest){
                lowest = pieces.at(k)->getPos();
                lowestIndex = k;
            }
        }
        Piece* toBeSwitched = pieces.at(i);
        pieces.at(i) = pieces.at(lowestIndex);
        pieces.at(lowestIndex) = toBeSwitched;
    }
}

string Board::pieceOnLocation(vector<Piece*>& pieces, char file, int rank){
    for(unsigned int i = 0; i < pieces.size(); i++){
        if(pieces.at(i)->getInformation()[2] == file && pieces.at(i)->getInformation()[3] == rank){
            return pieces.at(i)->getInformation();
        }
    }
    return "----";
}

Piece* Board::getPiece(vector<Piece*>& pieces, string pieceCode){
    for(int i = 0; i < pieces.size(); i++){
        if(pieces.at(i)->getInformation() == pieceCode){
            return pieces.at(i);
        }
    }
    return nullptr;
}

//basically, its true if there are no legal moves for a player and the king is in check
//if there are no legal moves, its their turn and they aren't in check, then it is a stalemate. 

