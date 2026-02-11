#include "attack.h"
#include <vector>
using namespace std;

bool isSquareAttacked(const Board& board, int x, int y, bool isSafeForWhite) {//isSafeForWhite is true means if square is safe for white, false means if square is safe for black
    // Check if the square (x, y) is attacked by any piece of the specified color
    // This function should check for attacks from all piece types (pawns, knights, bishops, rooks, queens, kings)

    char opponentPawn = isSafeForWhite ? 'p' : 'P';
    // Check for pawn attacks
    int direction = isSafeForWhite ? -1 : 1; // White pawns attack upwards, black pawns attack downwards
    if (x + direction >= 0 && x + direction < 8) {
        if (y > 0 && board.getPiece(x + direction, y - 1) == opponentPawn) {
            return true; // Attacked by a pawn on the left diagonal
        }
        if (y < 7 && board.getPiece(x + direction, y + 1) == opponentPawn) {
            return true; // Attacked by a pawn on the right diagonal
        }
    }

    // Check for knight attacks
    vector<pair<int, int>> knightMoves = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};
    char opponentKnight = isSafeForWhite ? 'n' : 'N';
    for (auto& move : knightMoves) {
        int newX = x + move.first;
        int newY = y + move.second;
        if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
            if (board.getPiece(newX, newY) == opponentKnight) {
                return true; // Attacked by a knight
            }
        }
    }

    // Check for Bishop attack
    vector<pair<int, int>> bishopDirections = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    for (auto& dir : bishopDirections) {
        int newX = x + dir.first;
        int newY = y + dir.second;
        while (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
            char targetPiece = board.getPiece(newX, newY);
            if (targetPiece == '.') {
                newX += dir.first;
                newY += dir.second;
                continue;
            } else if ((isSafeForWhite && islower(targetPiece)) || (!isSafeForWhite && isupper(targetPiece))) {
                if (tolower(targetPiece) == 'b' || tolower(targetPiece) == 'q') {
                    return true; // Attacked by a bishop or queen
                } else {
                    break; // Blocked by another piece
                }
            } else {
                break; // Blocked by another piece
            }
        }
    }

    // Check for Rook attack
    vector<pair<int, int>> rookDirections = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (auto& dir : rookDirections) {
        int newX = x + dir.first;
        int newY = y + dir.second;
        while (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
            char targetPiece = board.getPiece(newX, newY);
            if (targetPiece == '.') {
                newX += dir.first;
                newY += dir.second;
                continue;
            } else if ((isSafeForWhite && islower(targetPiece)) || (!isSafeForWhite && isupper(targetPiece))) {
                if (tolower(targetPiece) == 'r' || tolower(targetPiece) == 'q') {
                    return true; // Attacked by a rook or queen
                } else {
                    break; // Blocked by another piece
                }
            } else {
                break; // Blocked by another piece
            }
        }
    }

    // Check for King attack
    vector<pair<int, int>> kingMoves = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    char opponentKing = isSafeForWhite ? 'k' : 'K';
    for (auto& move : kingMoves) {
        int newX = x + move.first;
        int newY = y + move.second;
        if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
            if (board.getPiece(newX, newY) == opponentKing) {
                return true; // Attacked by a king
            }
        }
    }
    return false;
}  

bool isInCheck(const Board& board, bool isWhiteKing) {
    // Find the king's position
    char king = isWhiteKing ? 'K' : 'k';
    int kingX = -1, kingY = -1;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (board.getPiece(x, y) == king) {
                kingX = x;
                kingY = y;
                break;
            }
        }
        if (kingX != -1) break;
    }
    if (kingX == -1) return false; // King not found, should not happen in a valid game

    // Check if the king's square is attacked
    return isSquareAttacked(board, kingX, kingY, isWhiteKing);
}