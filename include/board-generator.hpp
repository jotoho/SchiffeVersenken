// SPDX-License-Identifier: GPL-3.0-or-later
/*
SchiffeVersenken - An implementation of Battleships
Copyright (C) 2022 SchiffeVersenken contributors

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef INCLUDE_GUARD_BOARDGEN_HPP
#define INCLUDE_GUARD_BOARDGEN_HPP

#include "fieldinfo.hpp"

// Returns an empty gameboard (all field set to EMPTY)
BoardType generateGameBoardEmpty();
// Return a randomly populated game board
BoardType generateGameBoardRandom();

#endif  // INCLUDE_GUARD_BOARDGEN_HPP
