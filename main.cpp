#include <iostream>
#include "board.h"
#include "movegen.h"

using namespace std;

int main() {
    
    cout<< "All White moves:"<<endl;
    Board board;
    auto allMoves = generateAllMoves(board, true);
    for (auto& m : allMoves)
         cout << "(" << m.fromX << "," << m.fromY << ") -> ("<< m.toX << "," << m.toY << ")"<< endl;
    return 0;
}
