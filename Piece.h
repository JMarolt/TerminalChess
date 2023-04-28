#ifndef PIECE_H
#define PIECE_H

#include <string>
#include <vector>
#include <iostream>
#include <queue>

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
        //returns if the piece has moved or not
        bool moved(){
            return hasMoved;
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
                    string oldPosition = pieces.at(i)->getInformation().substr(2, 2);
                    string enPassantOldPosition = pieces.at(i)->getInformation();
                    pieces.at(i)->setInformation(pieces.at(i)->getInformation().substr(0, 2) + newPosition);
                    //Special case: En Passant
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
                    //Special case: Castle
                    if(pieces.at(i)->getInformation()[1] == 'K'){
                        //queen side
                        if(pieces.at(i)->getInformation()[2] == oldPosition[0] - 2){
                            oldPosition[0] -= 4;
                            Piece* temp = getPieceOnLocation(pieces, oldPosition);
                            string newRookPosition = oldPosition;
                            newRookPosition[0] += 3;
                            temp->setInformation(temp->getInformation().substr(0, 2) + newRookPosition);
                        //king side
                        }else if(pieces.at(i)->getInformation()[2] == oldPosition[0] + 2){
                            oldPosition[0] += 3;
                            Piece* temp = getPieceOnLocation(pieces, oldPosition);
                            string newRookPosition = oldPosition;
                            newRookPosition[0] -= 2;
                            temp->setInformation(temp->getInformation().substr(0, 2) + newRookPosition);
                        }
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

    protected:
        //checks if the piece has moved(for pawn, rook, and king only)
        bool hasMoved;

        //two things to check:
        //1) if the player is in check, they must play a move to get them out of it
        //2) if the player is not in check, they cannot play a move that will put their king in check
        vector<string> legalMovesRestrictedByCheck(vector<Piece*>& pieces, vector<string>& previousMoves, bool whiteTurn, bool isInCheck){
            //if the player is in check, restrict movement
            vector<string> movesToRemove;
            string kingPosition;
            string originalKingPos;
            string kingValue = "WK";
            if(!whiteTurn){
                kingValue = "BK";
            }
            for(int i = 0; i < pieces.size(); i++){
                if(pieces.at(i)->getInformation().substr(0, 2) == kingValue){
                    kingPosition = pieces.at(i)->getPos();
                }
            }
            originalKingPos = kingPosition;
            //I DONT ACTUALLY CAPTURE PIECE SO IT COUNTS AS AN ILLEGAL MOVE.
            //I MIGHT HAVE TO MAKE A WHOLE SEPERATE PIECES LIST AND DO THE CALCULATIONS ON THAT
            if(isInCheck){
                for(int i = 0; i < pieces.size(); i++){ //go through all the pieces on the board
                    if(whiteTurn){
                        if(pieces.at(i)->getInformation()[0] == 'B') continue;
                    }else{
                        if(pieces.at(i)->getInformation()[0] == 'W') continue;
                    }
                    vector<string> legalMoves = pieces.at(i)->temporaryLegalMoves(pieces, previousMoves, whiteTurn, isInCheck);
                    //now we have to go through each of these moves and see whether if that move would stop check
                    string originalInfo = pieces.at(i)->getInformation();

                    for(int k = 0; k < legalMoves.size(); k++){ //go through all the legal moves of one piece
                        //so we change the piece to the legal move. and then in another loop, we see if check remains

                        // kingPosition = originalKingPos;
                        // if(pieces.at(i)->getInformation()[1] == 'K'){
                        //     kingPosition = legalMoves.at(k);
                        // }

                        pieces.at(i)->setInformation(originalInfo.substr(0, 2) + legalMoves.at(k));
                        //This for loop directly below simply checks if the piece can be captured
                        queue<int> piecesCapturedCheck; //this queue holds pieces that can be captured that are checking the king
                        for(int m = 0; m < pieces.size(); m++){
                            if(pieces.at(m)->getInformation().substr(2, 2) == legalMoves.at(k)){
                                if(pieces.at(m)->getInformation()[0] != kingValue[0]){
                                    piecesCapturedCheck.push(m);
                                }
                            }
                        }
                        //special positions needs to be checked where we assume a certain piece is removed
                        for(int j = 0; j < pieces.size(); j++){ //go through all the pieces of the non-checked player
                            if(whiteTurn){
                                if(pieces.at(j)->getInformation()[0] == 'W') continue;
                            }else{
                                if(pieces.at(j)->getInformation()[0] == 'B') continue;
                            }
                            if(j == piecesCapturedCheck.front()){//skip piece because it was captured
                                piecesCapturedCheck.pop();
                                continue;
                            }
                            vector<string> moves_legal = pieces.at(j)->temporaryLegalMoves(pieces, previousMoves, whiteTurn, isInCheck);
                            for(int h = 0; h < moves_legal.size(); h++){
                                if(moves_legal.at(h) == kingPosition){
                                    movesToRemove.push_back(legalMoves.at(k));
                                }
                            }
                        }
                    }
                    pieces.at(i)->setInformation(originalInfo);
                }
            }else{

            }
            return movesToRemove;
        }
};
#endif