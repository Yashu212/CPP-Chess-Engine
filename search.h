#ifndef SEARCH_H
#define SEARCH_H   

#include "board.h"
#include "move.h"

Move findBestMove(Board& board, bool isWhiteTurn, int depth);

#endif