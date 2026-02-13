#include <iostream>
#include "board.h"

using namespace std;

Board::Board() {
    // Initialize the board with the standard chess starting position
    // Uppercase for white pieces, lowercase for black pieces, '.' for empty squares
    const char* initialBoard[8] = {
        "rnbqkbnr",
        "pppppppp",
        "........",
        "........",
        "........",
        "........",
        "PPPPPPPP",
        "RNBQKBNR"
    };
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = initialBoard[i][j];
        }
    }
}

void Board::printBoard() const {
    cout << endl;
    for (int i = 0; i < 8; i++) {
        cout<< 8-i << " ";
        for (int j = 0; j < 8; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << "  a b c d e f g h" << endl;
}

char Board::getPiece(int x, int y) const {
    return board[x][y];
}

bool Board::makeMove(const Move& move) {
    if (move.fromX < 0 || move.fromX >= 8 || move.fromY < 0 || move.fromY >= 8 || move.toX < 0 || move.toX >= 8 || move.toY < 0 || move.toY >= 8)
        return false; // Checking out of bounds
    char piece = board[move.fromX][move.fromY];
    char captureBlock = board[move.toX][move.toY];
    if (piece == '.' || (isupper(piece) && isupper(captureBlock)) || (islower(piece) && islower(captureBlock))) {
        return false; // Invalid move or no piece to move
    }
    board[move.toX][move.toY] = piece;
    board[move.fromX][move.fromY] = '.';
    if(move.promotionPiece != '.'){
        board[move.toX][move.toY] = move.promotionPiece;
    }
    return true;
}

void Board::undoMove(const Move& move, char capturedPiece) {
    char piece = board[move.toX][move.toY];
    board[move.fromX][move.fromY] = piece;
    board[move.toX][move.toY] = capturedPiece;
    if(move.promotionPiece != '.'){
        // Revert promotion
        char pawn = isupper(move.promotionPiece) ? 'P' : 'p';
        board[move.fromX][move.fromY] = pawn;
    }
}

