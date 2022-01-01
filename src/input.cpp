#include <charconv>
#include <iostream>
#include "../include/boardpoint.hpp"
#include "../include/global-config.hpp"

BoardPoint inputTranslator(const std::string input) {
    const std::size_t rowCoordinate = input[0] - 'A';
    const std::string numberString = input.substr(1);
    std::size_t number{};
    std::from_chars(numberString.c_str(),
                    numberString.c_str() + numberString.size(), number);

    if (number == 0) {
        std::cerr << "ERROR: There is no column 0\n";
        std::exit(EXIT_FAILURE);
    }

    if constexpr (GlobalConf.debugMode) {
        std::cerr << "Creating board point object with coordinates ("
                  << std::to_string(number - 1) << ", "
                  << std::to_string(rowCoordinate) << ')' << std::endl;
    }

    const BoardPoint playerInput{number - 1, rowCoordinate};
    return playerInput;
}
