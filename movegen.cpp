#include "movegen.h"
#include "attack.h"
using namespace std;

vector<Move> generatePawnMoves(const Board& board, bool isWhiteTurn) {
    // ignore en passant for now.
    vector<Move> moves;
    char pawn = isWhiteTurn ? 'P' : 'p';
    int direction = isWhiteTurn ? -1 : 1; // White moves up, black moves down
    int startRow = isWhiteTurn ? 6 : 1; // Starting row for pawns
    int promotionRow = isWhiteTurn ? 0 : 7; // Row for promotion

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (board.getPiece(x, y) == pawn) {
                //forward moves
                if (x + direction >= 0 && x + direction < 8 && board.getPiece(x + direction, y) == '.') {
                    // Single move forward
                    if(x + direction == promotionRow){
                        char promotionOption[] = {'Q', 'R', 'B', 'N'};
                        for (char piece : promotionOption) {
                            char promotionPiece = isWhiteTurn ? piece : tolower(piece);
                            moves.push_back({x, y, x + direction, y, promotionPiece});
                        }
                    }
                    else
                        moves.push_back({x, y, x + direction, y});

                    // Double move forward from starting position
                    if (x == startRow && board.getPiece(x + 2 * direction, y) == '.') {
                        moves.push_back({x, y, x + 2 * direction, y});
                    }
                    
                }
                //Digaonal captures moves
                if(x + direction >= 0 && x + direction < 8){ 
                    //Left Diagonal move.
                    if(y > 0){
                        char targetPiece = board.getPiece(x + direction, y - 1);
                        if(targetPiece != '.' && ((isWhiteTurn && islower(targetPiece)) || (!isWhiteTurn && isupper(targetPiece))) ){
                            if(x+direction == promotionRow){
                                char promotionOption[] = {'Q', 'R', 'B', 'N'};
                                for (char piece : promotionOption) {
                                    char promotionPiece = isWhiteTurn ? piece : tolower(piece);
                                    moves.push_back({x, y, x + direction, y - 1, promotionPiece});
                                }
                            }
                            else
                                moves.push_back({x, y, x + direction, y - 1});
                        }
                    }
                    //Right Diagonal move.
                    if(y < 7){
                        char targetPiece = board.getPiece(x + direction, y + 1);
                        if(targetPiece != '.' && ((isWhiteTurn && islower(targetPiece)) || (!isWhiteTurn && isupper(targetPiece))) ){
                            if(x+direction == promotionRow){
                                char promotionOption[] = {'Q', 'R', 'B', 'N'};
                                for (char piece : promotionOption) {
                                    char promotionPiece = isWhiteTurn ? piece : tolower(piece);
                                    moves.push_back({x, y, x + direction, y + 1, promotionPiece});
                                }
                            }
                            else
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

vector<Move> generateBishopMoves(const Board& board, bool isWhiteTurn) {
    vector<Move> moves;
    char bishop = isWhiteTurn ? 'B' : 'b';
    vector<pair<int, int>> directions = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (board.getPiece(x, y) == bishop) {
                for (auto& dir : directions) {
                    int newX = x + dir.first;
                    int newY = y + dir.second;
                    while (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
                        char targetPiece = board.getPiece(newX, newY);
                        if (targetPiece == '.') {
                            moves.push_back({x, y, newX, newY});
                        } else if ((isWhiteTurn && islower(targetPiece)) || (!isWhiteTurn && isupper(targetPiece))) {
                            moves.push_back({x, y, newX, newY});
                            break;
                        } else {
                            break;
                        }
                        newX += dir.first;
                        newY += dir.second;
                    }
                }
            }
        }
    }
    return moves;
}

vector<Move> generateRookMoves(const Board& board, bool isWhiteTurn) {
    vector<Move> moves;
    char rook = isWhiteTurn ? 'R' : 'r';
    vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (board.getPiece(x, y) == rook) {
                for (auto& dir : directions) {
                    int newX = x + dir.first;
                    int newY = y + dir.second;
                    while (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
                        char targetPiece = board.getPiece(newX, newY);
                        if (targetPiece == '.') {
                            moves.push_back({x, y, newX, newY});
                        } else if ((isWhiteTurn && islower(targetPiece)) || (!isWhiteTurn && isupper(targetPiece))) {
                            moves.push_back({x, y, newX, newY});
                            break;
                        } else {
                            break;
                        }
                        newX += dir.first;
                        newY += dir.second;
                    }
                }
            }
        }
    }
    return moves;
}

vector<Move> generateQueenMoves(const Board& board, bool isWhiteTurn) {
    vector<Move> moves;
    char queen = isWhiteTurn ? 'Q' : 'q';
    vector<pair<int, int>> directions = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (board.getPiece(x, y) == queen) {
                for (auto& dir : directions) {
                    int newX = x + dir.first;
                    int newY = y + dir.second;
                    while (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
                        char targetPiece = board.getPiece(newX, newY);
                        if (targetPiece == '.') {
                            moves.push_back({x, y, newX, newY});
                        } else if ((isWhiteTurn && islower(targetPiece)) || (!isWhiteTurn && isupper(targetPiece))) {
                            moves.push_back({x, y, newX, newY});
                            break;
                        } else {
                            break;
                        }
                        newX += dir.first;
                        newY += dir.second;
                    }
                }
            }
        }
    }
    return moves;
}

vector<Move> generateKingMoves(const Board& board, bool isWhiteTurn) {
    vector<Move> moves;
    char king = isWhiteTurn ? 'K' : 'k';
    vector<pair<int, int>> possibleKingMoves = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (board.getPiece(x, y) == king) {
                for (auto& move : possibleKingMoves) {
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

vector<Move> generateAllMoves(const Board& board, bool isWhiteTurn) {
    vector<Move> allMoves;
    auto pawnMoves = generatePawnMoves(board, isWhiteTurn);
    auto knightMoves = generateKnightMoves(board, isWhiteTurn);
    auto bishopMoves = generateBishopMoves(board, isWhiteTurn);
    auto rookMoves = generateRookMoves(board, isWhiteTurn);
    auto queenMoves = generateQueenMoves(board, isWhiteTurn);
    auto kingMoves = generateKingMoves(board, isWhiteTurn);

    allMoves.insert(allMoves.end(), pawnMoves.begin(), pawnMoves.end());
    allMoves.insert(allMoves.end(), knightMoves.begin(), knightMoves.end());
    allMoves.insert(allMoves.end(), bishopMoves.begin(), bishopMoves.end());
    allMoves.insert(allMoves.end(), rookMoves.begin(), rookMoves.end());
    allMoves.insert(allMoves.end(), queenMoves.begin(), queenMoves.end());
    allMoves.insert(allMoves.end(), kingMoves.begin(), kingMoves.end());

    return allMoves;
}

vector<Move> generateLegalMoves(Board& board, bool isWhiteTurn) {
    vector<Move> legalMoves;
    auto allMoves = generateAllMoves(board, isWhiteTurn);
    for (auto& move : allMoves) {
        char capturedPiece = board.getPiece(move.toX, move.toY);
        if (board.makeMove(move)) {
            if (!isInCheck(board, isWhiteTurn)) {
                legalMoves.push_back(move);
            }
            board.undoMove(move, capturedPiece);
        }
    }
    return legalMoves;
}

long long perft(Board& board, bool isWhiteTurn, int depth) {
    if (depth == 0) {
        return 1; // Reached a leaf node
    }

    long long nodes = 0;
    auto legalMoves = generateLegalMoves(board, isWhiteTurn);
    for (auto& move : legalMoves) {
        char capturedPiece = board.getPiece(move.toX, move.toY);
        if (board.makeMove(move)) {
            nodes += perft(board, !isWhiteTurn, depth - 1);
            board.undoMove(move, capturedPiece);
        }
    }
    return nodes;
}