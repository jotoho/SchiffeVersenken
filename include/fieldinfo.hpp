#ifndef INCLUDE_GUARD_FIELDINFO_HPP
#define INCLUDE_GUARD_FIELDINFO_HPP

#include <array>
#include <cstddef>
#include <cstdint>
#include <stdexcept>

enum class FieldValue : std::uint_least8_t {
    EMPTY,
    SHIP,
    SHIP_HIT,
    MISS,
    PLACEHOLDER
};

constexpr struct {
    const size_t rows = 10;
    const size_t columns = 10;
} BoardDimensions;

using BoardType = std::array<std::array<FieldValue, BoardDimensions.columns>,
                             BoardDimensions.rows>;

// Sets how many ships of which types there should be on the board
// index = length of ship
constexpr std::array<std::uint_least8_t, 6> ShipDistribution = {0, 0, 4,
                                                                4, 2, 2};

// Boundschecked abstraction for points on the game board
struct BoardPoint {
    // Horizontal position; 0 is the left border
    const std::size_t x;
    // Vertical position; 0 is the upper border
    const std::size_t y;

    BoardPoint() = delete;
    constexpr BoardPoint(const std::size_t x, const std::size_t y)
        : x(x), y(y) {
        if (x >= BoardDimensions.columns || y >= BoardDimensions.rows)
            throw std::invalid_argument{
                "BoardPoints must be within the size constraints of the board"};
    }

    constexpr BoardPoint operator+(const BoardPoint& otherPoint) const {
        return BoardPoint{this->x + otherPoint.x, this->y + otherPoint.y};
    }
    constexpr BoardPoint operator-(const BoardPoint& otherPoint) const {
        // Leaving out the braces on this if will make gcc 11.1.0 not correctly
        // connect it with the else-block
        if (this->x < otherPoint.x || this->y < otherPoint.y) {
            throw std::range_error{
                "Point does not exist on board (coords would have "
                "underflowed)"};
        } else
            return BoardPoint{this->x - otherPoint.x, this->y - otherPoint.y};
    }

    constexpr bool operator==(const BoardPoint& otherPoint) const {
        return this->x == otherPoint.x && this->y == otherPoint.y;
    }
};

#endif  // INCLUDE_GUARD_FIELDINFO_HPP
