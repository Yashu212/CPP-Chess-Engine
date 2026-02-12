#include "search.h"
#include "eval.h"
#include "movegen.h"
#include "attack.h"
#include <iostream>

using namespace std;

int pieceVal(char piece) {
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


int quiescenceSearch(Board& board, bool isWhiteTurn, int alpha, int beta) {
    int standPat = evaluateBoard(board);
    if (isWhiteTurn) {
        if (standPat >= beta) {
            return beta;
        }
        if (standPat > alpha) {
            alpha = standPat;
        }
    } else {
        if (standPat <= alpha) {
            return alpha;
        }
        if (standPat < beta) {
            beta = standPat;
        }
    }

    auto legalMoves = generateLegalMoves(board, isWhiteTurn);
    for (auto& move : legalMoves) {
        char capturedPiece = board.getPiece(move.toX, move.toY);
        if (capturedPiece == '.') continue; // Only consider captures in quiescence search

        board.makeMove(move);
        int score = quiescenceSearch(board, !isWhiteTurn, alpha, beta);
        board.undoMove(move, capturedPiece);

        if (isWhiteTurn) {
            if (score >= beta) {
                return beta;
            }
            if (score > alpha) {
                alpha = score;
            }
        } else {
            if (score <= alpha) {
                return alpha;
            }
            if (score < beta) {
                beta = score;
            }
        }
    }
    return isWhiteTurn ? alpha : beta;
}

int alphaBeta(Board& board, bool isWhiteTurn, int depth, int alpha, int beta) {
    if (depth == 0) {
        return quiescenceSearch(board, isWhiteTurn, alpha, beta);
    }

    auto legalMoves = generateLegalMoves(board, isWhiteTurn);
    sort(legalMoves.begin(), legalMoves.end(),[&](const Move& a, const Move& b) {

        char capA = board.getPiece(a.toX, a.toY);
        char capB = board.getPiece(b.toX, b.toY);

        int scoreA = 0;
        int scoreB = 0;

        if (capA != '.')
            scoreA = 10 * pieceVal(capA) - pieceVal(board.getPiece(a.fromX, a.fromY));

        if (capB != '.')
            scoreB = 10 * pieceVal(capB) - pieceVal(board.getPiece(b.fromX, b.fromY));

        return scoreA > scoreB;
    });
    if (legalMoves.empty()) {
        // Check for checkmate or stalemate
        if (isInCheck(board, isWhiteTurn)) {
            return isWhiteTurn ? -100000 : 100000; // Checkmate
        } else {
            return 0; // Stalemate
        }
    }

    if (isWhiteTurn) {
        int maxEval = -100000;
        for (auto& move : legalMoves) {
            char capturedPiece = board.getPiece(move.toX, move.toY);
            board.makeMove(move);
            int eval = alphaBeta(board, false, depth - 1, alpha, beta);
            board.undoMove(move, capturedPiece);
            maxEval = max(maxEval, eval);
            alpha = max(alpha, eval);
            if (beta <= alpha) {
                break; // Beta cut-off
            }
        }
        return maxEval;
    } else {
        int minEval = 100000;
        for (auto& move : legalMoves) {
            char capturedPiece = board.getPiece(move.toX, move.toY);
            board.makeMove(move);
            int eval = alphaBeta(board, true, depth - 1, alpha, beta);
            board.undoMove(move, capturedPiece);
            minEval = min(minEval, eval);
            beta = min(beta, eval);
            if (beta <= alpha) {
                break; // Alpha cut-off
            }
        }
        return minEval;
    }
}

Move findBestMove(Board& board, bool isWhiteTurn, int depth) {
    Move bestMove;
    int bestEval = isWhiteTurn ? -100000 : 100000;

    auto legalMoves = generateLegalMoves(board, isWhiteTurn);
    for (auto& move : legalMoves) {
        char capturedPiece = board.getPiece(move.toX, move.toY);
        board.makeMove(move);
        int eval = alphaBeta(board, !isWhiteTurn, depth - 1, -100000, 100000);
        board.undoMove(move, capturedPiece);

        if (isWhiteTurn && eval > bestEval) {
            bestEval = eval;
            bestMove = move;
        } else if (!isWhiteTurn && eval < bestEval) {
            bestEval = eval;
            bestMove = move;
        }
    }
    return bestMove;
}