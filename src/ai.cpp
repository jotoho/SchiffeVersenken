#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "../include/boardpoint.hpp"

void hitShip(BoardType& board, const BoardPoint& lastShot) {
    const auto newLocation =
        stepsFromPoint(lastShot, static_cast<CardinalDirection>(rand() % 4), 1);

    switch (getRefFromPoint(board, newLocation)) {
        case FieldValue::EMPTY:
            [[fallthrough]];
        case FieldValue::PLACEHOLDER:
            getRefFromPoint(board, newLocation) = FieldValue::MISS;
            //std::puts("Daneben!");
            break;
        case FieldValue::SHIP:
            getRefFromPoint(board, newLocation) = FieldValue::SHIP_HIT;
            //std::puts("Treffer!");
            hitShip(board, newLocation);
            break;
        case FieldValue::MISS:
            [[fallthrough]];
        case FieldValue::SHIP_HIT:
            hitShip(board, lastShot);
            break;
    }
}

void aiShotRandom(BoardType& board) {
    const BoardPoint target{std::rand() % BoardDimensions.columns,
                            std::rand() % BoardDimensions.rows};

    switch (getRefFromPoint(board, target)) {
        case FieldValue::EMPTY:
            [[fallthrough]];
        case FieldValue::PLACEHOLDER:
            getRefFromPoint(board, target) = FieldValue::MISS;
            //std::puts("Daneben!");
            break;
        case FieldValue::SHIP:
            getRefFromPoint(board, target) = FieldValue::SHIP_HIT;
            //std::puts("Treffer!");
            hitShip(board, target);
            break;
        case FieldValue::MISS:
            [[fallthrough]];
        case FieldValue::SHIP_HIT:
            aiShotRandom(board);
            break;
    }
}
