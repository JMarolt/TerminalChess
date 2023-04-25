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
        //all moves within the board, cant move onto a square with its own piece, restricts movement if king is in check
        virtual vector<string> legalMoves(vector<Piece*>&){
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
                    pieces.at(i)->setInformation(pieces.at(i)->getInformation().substr(0, 2) + newPosition);
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

};
#endif