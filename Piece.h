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
        virtual vector<string> legalMoves(vector<Piece*>&) = 0;
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
                if(pieces.at(i)->getInformation() == location){
                    return true;
                }
            }
            return false;
        }
        //needs to be a function that restricts or basically forces moves because of check
        void makeMove(vector<Piece*>& pieces, string newPosition){
            for(unsigned i = 0; i < pieces.size(); i++){
                if(pieces.at(i) == this){
                    pieces.at(i)->setInformation(pieces.at(i)->getInformation().substr(0, 2) + newPosition);
                }
                //check piece color
                if(pieces.at(i)->getPos() == newPosition.substr(2, 2) && pieces.at(i)->getInformation()[0] != newPosition[0]){
                    capturePiece(pieces, i);
                }
            }
        }

        void capturePiece(vector<Piece*>& pieces, unsigned positionToBeRemoved){
            Piece* pieceToBeRemoved = pieces.at(positionToBeRemoved);
            pieces.erase(pieces.begin() + positionToBeRemoved);
            cout << "Piece Captured: " << pieceToBeRemoved->getInformation() << endl;
            delete pieceToBeRemoved;
        }
        //virtual void draw() = 0;

    private:
        string position;

};
#endif