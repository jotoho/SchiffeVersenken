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

constexpr size_t rows = 10;
constexpr size_t columns = 10;
using BoardType = std::array<std::array<FieldValue, columns>, rows>;

// Sets how many ships of which types there should be on the board
constexpr struct {
    // XX
    const std::uint_least8_t numSize2 = 4;
    // XXX
    const std::uint_least8_t numSize3 = 4;
    // XXXX
    const std::uint_least8_t numSize4 = 2;
    // XXXXX
    const std::uint_least8_t numSize5 = 2;
} ShipDistribution;

#endif  // INCLUDE_GUARD_FIELDINFO_HPP
