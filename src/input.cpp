#include <iostream>
#include "../include/fieldinfo.hpp"

BoardPoint inputTranslator(const std::string input) {
    const std::size_t letter = (int)(input[0] - 'A');
    const std::string numberString = input.substr(1);
    const std::size_t number = std::atoi(numberString.c_str());
    if (number == 0) {
        std::cerr << "ERROR: There is no column 0\n";
        std::exit(1);
    }
    BoardPoint playerInput{number - 1, letter};
    return playerInput;
}
