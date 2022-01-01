#include <cstdlib>
#include <ctime>
#include <iostream>
#include "../include/boardpoint.hpp"

void hitShip(BoardType& board, const BoardPoint& lastShot) {
    const auto newLocation =
        stepsFromPoint(lastShot, static_cast<CardinalDirection>(rand() % 4), 1);

    switch (getRefFromPoint(board, newLocation)) {
        case FieldValue::EMPTY:
            [[fallthrough]];
        case FieldValue::PLACEHOLDER:
            getRefFromPoint(board, newLocation) = FieldValue::MISS;
            break;
        case FieldValue::SHIP:
            getRefFromPoint(board, newLocation) = FieldValue::SHIP_HIT;
            hitShip(board, newLocation);
            break;
        case FieldValue::MISS:
            [[fallthrough]];
        case FieldValue::SHIP_HIT:
            hitShip(board, lastShot);
            break;
    }
}

bool aiShotRandom(BoardType& board) {
    const BoardPoint target{std::rand() % BoardDimensions.columns,
                            std::rand() % BoardDimensions.rows};

    switch (getRefFromPoint(board, target)) {
        case FieldValue::EMPTY:
            [[fallthrough]];
        case FieldValue::PLACEHOLDER:
            getRefFromPoint(board, target) = FieldValue::MISS;
            return false;
        case FieldValue::SHIP:
            getRefFromPoint(board, target) = FieldValue::SHIP_HIT;
            hitShip(board, target);
            return true;
        case FieldValue::MISS:
            [[fallthrough]];
        case FieldValue::SHIP_HIT:
            return aiShotRandom(board);
        default:
            std::cerr << "siShotRandom: Unexpected value in field, closing application." << std::endl;
            std::exit(EXIT_FAILURE);
    }
}
