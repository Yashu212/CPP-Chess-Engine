#include <iostream>
#include "board.h"
#include "movegen.h"

using namespace std;

int main() {
    /*
    Board board;
    board.printBoard();

    Move m{6, 4, 4, 4}; // e2 -> e4
    board.makeMove(m);
    board.printBoard();
    */

    Board board;
    board.printBoard();

    auto pawnMoves = generatePawnMoves(board, true);

    cout << "White pawn moves:"<<endl;
    for (auto& m : pawnMoves)
        cout << "(" << m.fromX << "," << m.fromY << ") -> ("<< m.toX << "," << m.toY << ")"<< endl;

    cout << "White Knight moves:"<<endl;
    auto knightMoves = generateKnightMoves(board, true);
    for (auto& m : knightMoves)
        cout << "(" << m.fromX << "," << m.fromY << ") -> ("<< m.toX << "," << m.toY << ")"<< endl;

    return 0;
}
