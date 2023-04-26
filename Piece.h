#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Piece{

    public:
        Piece(char team, char pieceIdentifier, char letterRank, int numberRank){
            string str = "";
            str.push_back(team);
            str.push_back(pieceIdentifier);
            str.push_back(letterRank);
            string toAdd = to_string(numberRank);
            str.append(toAdd);
            this->position = str;
        }
        Piece(string information){
            this->position = information;
        }
        //all LEGAL moves
        virtual vector<string> legalMoves(vector<Piece*>&, vector<string>&, bool, bool){
            vector<string> temp;
            return temp;
        }
        //legal moves before check restrictions of a specific piece
        virtual vector<string> temporaryLegalMoves(vector<Piece*>&, vector<string>&, bool, bool){
            vector<string> temp;
            return temp;
        }
        virtual void promote(vector<Piece*>&, Piece*, int){}
        string getInformation(){
            return position;
        }
        void setInformation(string info){
            this->position = info;
        }
        string getPos(){
            return position.substr(2, 2);
        }
        bool pieceOnLocation(vector<Piece*>& pieces, string& location) const{
            for(unsigned i = 0; i < pieces.size(); i++){
                if(pieces.at(i)->getPos() == location){
                    if(pieces.at(i) == this){
                        continue;
                    }
                    return true;
                }
            }
            return false;
        }
        Piece* getPieceOnLocation(vector<Piece*>& pieces, string& location) const{
            for(unsigned i = 0; i < pieces.size(); i++){
                if(pieces.at(i)->getPos() == location){
                    if(pieces.at(i) != this){
                        return pieces.at(i);
                    }
                }
            }
            return nullptr;
        }
        //needs to be a function that restricts or basically forces moves because of check
        void makeMove(vector<Piece*>& pieces, string newPosition){
            for(unsigned i = 0; i < pieces.size(); i++){
                if(pieces.at(i) == this){
                    string enPassantOldPosition = pieces.at(i)->getInformation();
                    pieces.at(i)->setInformation(pieces.at(i)->getInformation().substr(0, 2) + newPosition);
                    if(isEnPassant(pieces, enPassantOldPosition, newPosition)){
                        int add = 1;
                        if(pieces.at(i)->getInformation()[0] == 'B') add = -1;
                        string pawnPositionBeingCaptured = newPosition;
                        pawnPositionBeingCaptured[1] -= add;
                        capturePiece(pieces, getPieceOnLocation(pieces, pawnPositionBeingCaptured)->getInformation(), pawnPositionBeingCaptured);
                    }
                    if(canPiecePromote(pieces.at(i)->getInformation())){
                        string choice = "";
                        int num = 1;
                        cout << "Your pawn can be promoted! What piece would you like?(Bishop, Knight, Queen, Rook)(By not choosing one of these choices, you will be automatically promoted to a queen)\n";
                        cin >> choice;
                        if(choice == "Queen") num = 1;
                        if(choice == "Bishop") num = 2;
                        if(choice == "Rook") num = 3;
                        if(choice == "Knight") num = 4;
                        pieces.at(i)->promote(pieces, pieces.at(i), num);
                    }
                    if(pieceOnLocation(pieces, newPosition)){
                        capturePiece(pieces, getPieceOnLocation(pieces, newPosition)->getInformation(), newPosition);
                    }
                }
            }
        }

        //pieceInfo refers to information about piece TO BE CAPTURED and position refers to position of piece
        //REMOVE the position argument, it is useless
        void capturePiece(vector<Piece*>& pieces, string pieceInfo, string position){
            int indexToRemove = 0;
            for(int i = 0; i < pieces.size(); i++){
                if(pieces.at(i)->getPos() == position && pieces.at(i)->getInformation() == pieceInfo){
                    indexToRemove = i;
                    break;
                }
            }
            Piece* pieceToBeRemoved = pieces.at(indexToRemove);
            pieces.erase(pieces.begin() + indexToRemove);
            cout << "Piece Captured: " << pieceToBeRemoved->getInformation() << endl;
            delete pieceToBeRemoved;
        }

    private:
        string position;
        virtual vector<string> legalMovesRestrictedByCheck(vector<Piece*>&, bool){
            vector<string> temp;
            return temp;
        }

        bool canPiecePromote(string pieceInfo){
            if(pieceInfo[1] != 'P'){
                return false;
            }
            if(pieceInfo[0] == 'W'){
                if(pieceInfo[3] == '8'){
                    return true;
                }
            }else{
                if(pieceInfo[3] == '1'){
                    return true;
                } 
            }
            return false;
        }

        //we can check if our piece is a pawn and if its going diagonal onto a square with no piece, it must
        //be capturing another pawn that just advanced 2 squares
        bool isEnPassant(vector<Piece*>& pieces, string pieceInfo, string newPosition){
            if(pieceInfo[1] != 'P'){
                return false;
            }
            if(pieceInfo[2] != newPosition[0]){
                if(!pieceOnLocation(pieces, newPosition)){
                    return true;
                }
            }
            return false;
        }

};
#endif