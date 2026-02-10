#ifndef MOVEGEN_H
#define MOVEGEN_H

#include <vector>
#include "board.h"
#include "move.h"

using namespace std;

vector<Move> generatePawnMoves(const Board& board, bool isWhiteTurn);
vector<Move> generateKnightMoves(const Board& board, bool isWhiteTurn);
vector<Move> generateBishopMoves(const Board& board, bool isWhiteTurn);
vector<Move> generateRookMoves(const Board& board, bool isWhiteTurn);
vector<Move> generateQueenMoves(const Board& board, bool isWhiteTurn);
vector<Move> generateKingMoves(const Board& board, bool isWhiteTurn);

#endif