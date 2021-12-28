#ifndef INCLUDE_GUARD_GAMELOGIC_HPP
#define INCLUDE_GUARD_GAMELOGIC_HPP

#include <cstdint>
#include "./fieldinfo.hpp"

/*
    Returns
*/
std::uint_least8_t checkWinner(const BoardType& boardPlayer1,
                               const BoardType& boardPlayer2);

#endif  // INCLUDE_GUARD_GAMELOGIC_HPP
