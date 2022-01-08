#include <charconv>
#include <iostream>
#include "../include/boardpoint.hpp"
#include "../include/global-config.hpp"

// Gets the input from the user and attempts to parse
// the row and column coordinates in the format:
// "{upper-case letter representing row}{unsigned number representing column}"
BoardPoint inputTranslator(const std::string input) {
    const std::size_t rowCoordinate = input[0] - 'A';
    const std::string numberString = input.substr(1);
    std::size_t number{};
    std::from_chars(numberString.c_str(),
                    numberString.c_str() + numberString.size(), number);

    if (number == 0)
        throw std::invalid_argument{"There is no column 0!"};

    if constexpr (GlobalConf.debugMode) {
        std::cerr << "Creating board point object with coordinates ("
                  << std::to_string(number - 1) << ", "
                  << std::to_string(rowCoordinate) << ')' << std::endl;
    }

    const BoardPoint playerInput{number - 1, rowCoordinate};
    return playerInput;
}
