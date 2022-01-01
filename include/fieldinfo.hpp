#ifndef INCLUDE_GUARD_FIELDINFO_HPP
#define INCLUDE_GUARD_FIELDINFO_HPP

#include <array>
#include <cstddef>
#include <cstdint>

enum class FieldValue : std::uint_least8_t {
    EMPTY,
    SHIP,
    SHIP_HIT,
    MISS,
    PLACEHOLDER
};

constexpr struct {
    const size_t rows = 15;
    const size_t columns = 15;
} BoardDimensions;

// There must never be more rows than can be expressed by one upper-case
// alphanumeric letter
static_assert(BoardDimensions.rows <= 'Z' - 'A' + 1);

using BoardType = std::array<std::array<FieldValue, BoardDimensions.columns>,
                             BoardDimensions.rows>;

// Sets how many ships of which types there should be on the board
// index = length of ship
constexpr std::array<std::uint_least8_t, 6> ShipDistribution = {0, 0, 4,
                                                                4, 2, 2};

#endif  // INCLUDE_GUARD_FIELDINFO_HPP
