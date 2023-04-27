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
        //returns ONLY the legal moves for a piece
        virtual vector<string> legalMoves(vector<Piece*>&, vector<string>&, bool, bool){
            vector<string> temp;
            return temp;
        }
        //returns all legal moves and illegal moves because of check
        virtual vector<string> temporaryLegalMoves(vector<Piece*>&, vector<string>&, bool, bool){
            vector<string> temp;
            return temp;
        }
        //function just for the pawn class to promote when on the back rank
        virtual void promote(vector<Piece*>&, Piece*, int){}
        //returns the piece identity and the position combined
        string getInformation(){
            return position;
        }
        //sets the piece's identity and position
        void setInformation(string info){
            this->position = info;
        }
        //returns JUST the position
        string getPos(){
            return position.substr(2, 2);
        }
        //determines if a piece is on a given location
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
        //returns a pointer to the piece object given the location
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
                    //Special case: En Passant
                    string enPassantOldPosition = pieces.at(i)->getInformation();
                    pieces.at(i)->setInformation(pieces.at(i)->getInformation().substr(0, 2) + newPosition);
                    if(isEnPassant(pieces, enPassantOldPosition, newPosition)){
                        int add = 1;
                        if(pieces.at(i)->getInformation()[0] == 'B') add = -1;
                        string pawnPositionBeingCaptured = newPosition;
                        pawnPositionBeingCaptured[1] -= add;
                        capturePiece(pieces, getPieceOnLocation(pieces, pawnPositionBeingCaptured)->getInformation(), pawnPositionBeingCaptured);
                    }
                    //Special Case: Promotion
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
                    //capture a piece if its on the square to be moved
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
        //position includes the piece, team color, and position
        string position;
        //removes the moves returned from temporaryLegalMoves that are illegal because the player is in check
        //or that move causes the player to be in check
        virtual vector<string> legalMovesRestrictedByCheck(vector<Piece*>&, bool){
            vector<string> temp;
            return temp;
        }

        //checks whether or not a pawn has the ability to promote
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