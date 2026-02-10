#ifndef BOARD_H
#define BOARD_H

#include "move.h"
class Board {
public:
    Board();
    bool makeMove(const Move& move);
    void undoMove(const Move& move, char capturedPiece);
    void printBoard() const;
    char getPiece(int x, int y) const;
private:
    char board[8][8];
};

#endif