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
    const size_t rows = 10;
    const size_t columns = 10;
} BoardDimensions;

using BoardType = std::array<std::array<FieldValue, BoardDimensions.columns>,
                             BoardDimensions.rows>;

#endif  // INCLUDE_GUARD_FIELDINFO_HPP
