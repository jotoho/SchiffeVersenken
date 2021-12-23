#ifndef INCLUDE_GUARD_BOARDPOINT_HPP
#define INCLUDE_GUARD_BOARDPOINT_HPP

#include <vector>
#include "./fieldinfo.hpp"

// Boundschecked abstraction for points on the game board
struct BoardPoint {
    // Horizontal position; 0 is the left border
    const std::size_t x;
    // Vertical position; 0 is the upper border
    const std::size_t y;

    BoardPoint() = delete;
    BoardPoint(const std::size_t x, const std::size_t y);

    BoardPoint operator+(const BoardPoint& otherPoint) const;
    BoardPoint operator-(const BoardPoint& otherPoint) const;

    bool operator==(const BoardPoint& otherPoint) const;
};

using BoardPointRange = std::vector<BoardPoint>;
enum class CardinalDirection : std::uint_least8_t { NORTH, EAST, SOUTH, WEST };

BoardPointRange generatePointRangeBetween(const BoardPoint& startPoint,
                                          const BoardPoint& endPoint,
                                          const CardinalDirection direction);

BoardPoint stepsFromPoint(const BoardPoint& originPoint,
                          const CardinalDirection direction,
                          const std::size_t numberOfSteps);

FieldValue& getRefFromPoint(BoardType& board, const BoardPoint& point);
const FieldValue& getRefFromPoint(const BoardType& board,
                                  const BoardPoint& point);

#endif  // INCLUDE_GUARD_BOARDPOINT_HPP
