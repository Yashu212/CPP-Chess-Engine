#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <cctype>
#include "attack.h"

#include "board.h"
#include "movegen.h"
#include "search.h"

using namespace std;

Move parseMove(const string& input) {

    Move move;

    move.fromY = input[0] - 'a';
    move.fromX = '8' - input[1];

    move.toY   = input[2] - 'a';
    move.toX   = '8' - input[3];

    move.promotionPiece = '.';

    if (input.length() == 5) {
        move.promotionPiece = isupper(input[4]) ? input[4]
                                                : toupper(input[4]);
    }

    return move;
}


void playGame() {

    Board board;
    bool whiteToMove = true;

    while (true) {
        auto legalMoves = generateLegalMoves(board, whiteToMove);
        
        board.printBoard();

        if (legalMoves.empty()) {

            if (isInCheck(board, whiteToMove))
                cout << (whiteToMove ? "White" : "Black") << " is checkmated!\n";
            else
                cout << "Stalemate!\n";

            break;
        }

        if (whiteToMove) {
            cout << "Your move (e2e4): ";
            string input;
            getline(cin, input);

            if (input == "quit")
                break;

            Move move = parseMove(input);

            auto legalMoves = generateLegalMoves(board, true);

            bool found = false;
            for (auto& m : legalMoves) {
                if (m == move) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Illegal move.\n";
                continue;
            }

            char captured = board.getPiece(move.toX, move.toY);
            board.makeMove(move);
        }
        else {
            cout << "Engine thinking...\n";

            auto start = chrono::high_resolution_clock::now();

            Move bestMove = findBestMove(board, false, 4);

            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> diff = end - start;

            char fromFile = 'a' + bestMove.fromY;
            char fromRank = '8' - bestMove.fromX;
            char toFile   = 'a' + bestMove.toY;
            char toRank   = '8' - bestMove.toX;

            cout << "Engine plays: "
                 << fromFile << fromRank
                 << toFile << toRank
                 << " ("
                 << diff.count() << "s)\n";

            char captured = board.getPiece(bestMove.toX, bestMove.toY);
            board.makeMove(bestMove);
        }

        whiteToMove = !whiteToMove;
    }
}

void runPerftMode() {

    Board board;

    for (int depth = 1; depth <= 5; depth++) {

        auto start = chrono::high_resolution_clock::now();

        long long nodes = perft(board, true, depth);

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> diff = end - start;

        cout << "Depth " << depth << " Nodes: " << nodes << " Time: " << diff.count() << "s\n";
    }
}



int main() {

    cout << "==== CPP Chess Engine ====\n";
    cout << "1. Play vs Engine\n";
    cout << "2. Run Perft\n";
    cout << "Choose: ";

    int choice;
    cin >> choice;
    cin.ignore();

    if (choice == 1)
        playGame();
    else
        runPerftMode();

    return 0;
}
