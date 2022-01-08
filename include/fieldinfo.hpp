#ifndef INCLUDE_GUARD_FIELDINFO_HPP
#define INCLUDE_GUARD_FIELDINFO_HPP

#include <array>
#include <cstddef>
#include <cstdint>

// All the states a field on the board can be in.
enum class FieldValue : std::uint_least8_t {
    // Nothing is here and this field is not adjacent to a ship
    EMPTY,
    // A ship parts is located here
    SHIP,
    // This ship part was already hit
    SHIP_HIT,
    // Previous target of failed shot. Nothing is here.
    MISS,
    // Nothing is here. Directly adjacent to a ship.
    // (Used to prevent generation of touching ships)
    PLACEHOLDER
};

// Configuration for game board sizes
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
