#ifndef ATTACK_H
#define ATTACK_H

#include "board.h"
bool isSquareAttacked(const Board& board, int x, int y, bool byWhite);
bool isInCheck(const Board& board, bool isWhiteKing);

#endif