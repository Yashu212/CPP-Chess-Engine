#include "eval.h"
#include "movegen.h"
#include <cctype>
using namespace std;

const int MOBILITY_WEIGHT = 2;
static const int pawnTable[8][8] = {
    { 0,  0,  0,  0,  0,  0,  0,  0},
    {50, 50, 50, 50, 50, 50, 50, 50},
    {10, 10, 20, 30, 30, 20, 10, 10},
    { 5,  5, 10, 25, 25, 10,  5,  5},
    { 0,  0,  0, 20, 20,  0,  0,  0},
    { 5, -5,-10,  0,  0,-10, -5,  5},
    { 5, 10, 10,-20,-20, 10, 10,  5},
    { 0,  0,  0,  0,  0,  0,  0,  0}
};

static const int knightTable[8][8] = {
    {-50,-40,-30,-30,-30,-30,-40,-50},
    {-40,-20,  0,  0,  0,  0,-20,-40},
    {-30,  0, 10, 15, 15, 10,  0,-30},
    {-30,  5, 15, 20, 20, 15,  5,-30},
    {-30,  0, 15, 20, 20, 15,  0,-30},
    {-30,  5, 10, 15, 15, 10,  5,-30},
    {-40,-20,  0,  5,  5,  0,-20,-40},
    {-50,-40,-30,-30,-30,-30,-40,-50}
};

static const int bishopTable[8][8] = {
    {-20,-10,-10,-10,-10,-10,-10,-20},
    {-10,  0,  0,  0,  0,  0,  0,-10},
    {-10,  0,  5, 10, 10,  5,  0,-10},
    {-10,  5,  5, 10, 10,  5,  5,-10},
    {-10,  0, 10, 10, 10, 10,  0,-10},
    {-10, 10, 10, 10, 10, 10, 10,-10},
    {-10,  5,  0,  0,  0,  0,  5,-10},
    {-20,-10,-10,-10,-10,-10,-10,-20}
};

static const int rookTable[8][8] = {
    {  0,  0,  0,  5,  5,  0,  0,  0},
    { -5,  0,  0,  0,  0,  0,  0, -5},
    { -5,  0,  0,  0,  0,  0,  0, -5},
    { -5,  0,  0,  0,  0,  0,  0, -5},
    { -5,  0,  0,  0,  0,  0,  0, -5},
    { -5,  0,  0,  0,  0,  0,  0, -5},
    {  5, 10, 10, 10, 10, 10, 10,  5},
    {  0,  0,  0,  0,  0,  0,  0,  0}
};

static const int queenTable[8][8] = {
    {-20,-10,-10, -5, -5,-10,-10,-20},
    {-10,  0,  0,  0,  0,  0,  0,-10},
    {-10,  0,  5,  5,  5,  5,  0,-10},
    { -5,  0,  5,  5,  5,  5,  0, -5},
    {  0,  0,  5,  5,  5,  5,  0, -5},
    {-10,  5,  5,  5,  5,  5,  0,-10},
    {-10,  0,  5,  0,  0,  0,  0,-10},
    {-20,-10,-10, -5, -5,-10,-10,-20}
};

static const int kingTable[8][8] = {
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-30,-40,-40,-50,-50,-40,-40,-30},
    {-20,-30,-30,-40,-40,-30,-30,-20},
    {-10,-20,-20,-20,-20,-20,-20,-10},
    { 20, 20,  0,  0,  0,  0, 20, 20},
    { 20, 30, 10,  0,  0, 10, 30, 20}
};


int pieceValue(char piece) {
    switch (tolower(piece)) {
        case 'p': return 100;
        case 'n': return 320;
        case 'b': return 330;
        case 'r': return 500;
        case 'q': return 900;
        case 'k': return 20000; 
        default: return 0;
    }
}

int positionalValue(char piece, int x, int y, bool isWhite) {
    int tableX = isWhite ? x : 7 - x;
    switch (tolower(piece)) {
        case 'p': return pawnTable[tableX][y];
        case 'n': return knightTable[tableX][y];
        case 'b': return bishopTable[tableX][y];
        case 'r': return rookTable[tableX][y];
        case 'q': return queenTable[tableX][y];
        case 'k': return kingTable[tableX][y];
        default: return 0;
    }
} 

bool isCenterSquare(const Board& board, int x, int y, bool isWhite) {
    return (x == 3 || x == 4) && (y == 3 || y == 4);
}

bool isExtendedCenterSquare(const Board& board, int x, int y, bool isWhite) {
    return (x >= 2 && x <= 5) && (y >= 2 && y <= 5);
}

int evaluateBoard(const Board& board) {
    int score = 0;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            char piece = board.getPiece(x, y);
            if (piece != '.') {
                int value = pieceValue(piece);
                int posValue = positionalValue(piece, x, y, isupper(piece));
                if(isupper(piece)) {
                    score += value + posValue; // White pieces add to score
                } else {
                    score -= value + posValue; // Black pieces subtract from score
                }
            }

            //for center control
            if (isCenterSquare(board, x, y, true)) {
                if (isupper(board.getPiece(x, y))) score += 10; // Control of center adds to score
                else if (islower(board.getPiece(x, y))) score -= 10; // Opponent control of center subtracts from score
            } else if (isExtendedCenterSquare(board, x, y, true)) {
                if (isupper(board.getPiece(x, y))) score += 5; // Control of extended center adds to score
                else if (islower(board.getPiece(x, y))) score -= 5; // Opponent control of extended center subtracts from score
            }

        }
    }
    
    //for Mobility
    Board tempBoard = board; // Create a temporary board to generate moves
    auto whiteMoves = generateLegalMoves(tempBoard, true);
    auto blackMoves = generateLegalMoves(tempBoard, false);
    score += MOBILITY_WEIGHT * (whiteMoves.size() - blackMoves.size()); // Mobility factor
    return score;
}