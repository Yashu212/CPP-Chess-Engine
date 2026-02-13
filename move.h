#ifndef MOVE_H
#define MOVE_H

struct Move {
    int fromX, fromY;
    int toX, toY;
    char promotionPiece = '.'; // For pawn promotion, otherwise set to '.'

    bool operator==(const Move& other) const {
        return fromX == other.fromX && fromY == other.fromY &&
               toX == other.toX && toY == other.toY &&
               promotionPiece == other.promotionPiece;
    }
};

#endif