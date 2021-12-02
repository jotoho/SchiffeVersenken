#ifndef INCLUDE_GUARD_FIELDINFO_HPP
#define INCLUDE_GUARD_FIELDINFO_HPP

#include <cstdint>
#include <cstddef>
#include <array>

enum class FieldValue : std::uint_least8_t {
    EMPTY, SHIP, SHIP_HIT, MISS, PLACEHOLDER
};

constexpr size_t rows = 10;
constexpr size_t columns = 10;
using BoardType = std::array<std::array<FieldValue, columns>, rows>;

#endif // INCLUDE_GUARD_FIELDINFO_HPP
