#ifndef INCLUDE_GUARD_INPUT_HPP
#define INCLUDE_GUARD_INPUT_HPP

#include <string>
#include "./boardpoint.hpp"

// Reads target coordinates from user input
// Throws if they could not be parsed
BoardPoint inputTranslator(const std::string input);

#endif  // INCLUDE_GUARD_INPUT_HPP
