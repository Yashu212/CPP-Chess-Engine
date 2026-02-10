// only pawn moves for now.
// ignore en passant, promotion for now.
#include "movegen.h"

using namespace std;

vector<Move> generatePawnMoves(const Board& board, bool isWhiteTurn) {
    vector<Move> moves;
    char pawn = isWhiteTurn ? 'P' : 'p';
    int direction = isWhiteTurn ? -1 : 1; // White moves up, black moves down

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (board.getPiece(x, y) == pawn) {
                //forward moves
                if (x + direction >= 0 && x + direction < 8 && board.getPiece(x + direction, y) == '.') {
                    // Single move forward
                    moves.push_back({x, y, x + direction, y});

                    // Double move forward from starting position
                    if ((isWhiteTurn && x == 6) || (!isWhiteTurn && x == 1)){
                        if (board.getPiece(x + 2 * direction, y) == '.') {
                            moves.push_back({x, y, x + 2 * direction, y});
                        }
                    }
                    
                }
                //Digaonal captures moves
                if(x + direction >= 0 && x + direction < 8){ 
                    //Left Diagonal move.
                    if(y > 0){
                        char targetPiece = board.getPiece(x + direction, y - 1);
                        if(targetPiece != '.' && ((isWhiteTurn && islower(targetPiece)) || (!isWhiteTurn && isupper(targetPiece))) ){
                            moves.push_back({x, y, x + direction, y - 1});
                        }
                    }
                    //Right Diagonal move.
                    if(y < 7){
                        char targetPiece = board.getPiece(x + direction, y + 1);
                        if(targetPiece != '.' && ((isWhiteTurn && islower(targetPiece)) || (!isWhiteTurn && isupper(targetPiece))) ){
                            moves.push_back({x, y, x + direction, y + 1});
                        }
                    }
                }
            }
        }
    }
    return moves;
}

vector<Move> generateKnightMoves(const Board& board, bool isWhiteTurn) {
    vector<Move> moves;
    char knight = isWhiteTurn ? 'N' : 'n';
    vector<pair<int, int>> possibleKnightMoves = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (board.getPiece(x, y) == knight) {
                for (auto& move : possibleKnightMoves) {
                    int newX = x + move.first;
                    int newY = y + move.second;
                    if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
                        char targetPiece = board.getPiece(newX, newY);
                        if (targetPiece == '.' || ((isWhiteTurn && islower(targetPiece)) || (!isWhiteTurn && isupper(targetPiece)))) {
                            moves.push_back({x, y, newX, newY});
                        }
                    }
                }
            }
        }
    }
    return moves;
}