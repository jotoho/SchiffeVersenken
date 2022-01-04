#include <algorithm>
#include <stdexcept>

#include "../include/boardpoint.hpp"

BoardPoint::BoardPoint(const std::size_t x, const std::size_t y) : x(x), y(y) {
    if (x >= BoardDimensions.columns || y >= BoardDimensions.rows)
        throw std::invalid_argument{
            "BoardPoints must be within the size constraints of the board"};
}

BoardPoint BoardPoint::operator+(const BoardPoint& otherPoint) const {
    return BoardPoint{this->x + otherPoint.x, this->y + otherPoint.y};
}

BoardPoint BoardPoint::operator-(const BoardPoint& otherPoint) const {
    // Leaving out the braces on this if will make gcc 11.1.0 not correctly
    // connect it with the else-block
    if (this->x < otherPoint.x || this->y < otherPoint.y) {
        throw std::range_error{
            "Point does not exist on board (coords would have "
            "underflowed)"};
    } else
        return BoardPoint{this->x - otherPoint.x, this->y - otherPoint.y};
}

bool BoardPoint::operator==(const BoardPoint& otherPoint) const {
    return this->x == otherPoint.x && this->y == otherPoint.y;
}

BoardPointRange generatePointRangeBetween(const BoardPoint& startPoint,
                                          const BoardPoint& endPoint,
                                          const CardinalDirection direction) {
    BoardPointRange shipPoints;
    shipPoints.emplace_back(startPoint);

    // While list does not contain endPoint
    while (std::find(shipPoints.begin(), shipPoints.end(), endPoint) ==
           shipPoints.end()) {
        const auto lastPoint = shipPoints.at(shipPoints.size() - 1);
        shipPoints.emplace_back(stepsFromPoint(lastPoint, direction, 1));
    }

    return shipPoints;
}

BoardPoint stepsFromPoint(const BoardPoint& originPoint,
                          const CardinalDirection direction,
                          const std::size_t numberOfSteps) {
    switch (direction) {
        case CardinalDirection::NORTH:
            return originPoint - BoardPoint{0, numberOfSteps};
        case CardinalDirection::EAST:
            return originPoint + BoardPoint{numberOfSteps, 0};
        case CardinalDirection::SOUTH:
            return originPoint + BoardPoint{0, numberOfSteps};
        case CardinalDirection::WEST:
            return originPoint - BoardPoint{numberOfSteps, 0};
        default:
            throw std::invalid_argument{"Invalid direction was provided"};
    }
}

FieldValue& getRefFromPoint(BoardType& board, const BoardPoint& point) {
    return board[point.y][point.x];
}

const FieldValue& getRefFromPoint(const BoardType& board,
                                  const BoardPoint& point) {
    return board[point.y][point.x];
}
