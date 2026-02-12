#include <iostream>
#include "board.h"
#include "movegen.h"
#include "search.h"

using namespace std;

int main() {
    Board board;
    board.printBoard();

    cout << "\nEngine thinking...\n";

    Move best = findBestMove(board, true, 5); // depth 5

    cout << "Best move found:\n";
    cout << "(" << best.fromX << "," << best.fromY << ") -> (" << best.toX << "," << best.toY << ")\n";

    board.makeMove(best);
    board.printBoard();

    return 0;
}
