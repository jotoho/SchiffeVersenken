#include <cstdlib>
#include <iostream>
#include <type_traits>
#include "../include/boardpoint.hpp"
#include "../include/global-config.hpp"

/*
    The version of gcc currently installed in the WPU is only
    7.5.0 and not fully standard compliant with C++17.

    (charconv and from_chars for integers was added in version 8.1)

    Because of this we need to use a horrible preprocessor hack
    to use legacy conversion functions instead, if charconv and
    from_chars are not available.
*/
#if __has_include(<charconv>)
#include <charconv>
#endif

// Gets the input from the user and attempts to parse
// the row and column coordinates in the format:
// "{upper-case letter representing row}{unsigned number representing column}"
BoardPoint inputTranslator(const std::string input) {
    const std::size_t rowCoordinate = input[0] - 'A';
    const std::string numberString = input.substr(1);

#if __has_include(<charconv>)
    std::size_t number{};
    std::from_chars(numberString.c_str(),
                    numberString.c_str() + numberString.size(), number);
#else
    // To simplify the code, I have decided to assume that std::size_t
    // is unsigned long in this hack.
    // This should work on x86_64 but compiling for other
    // architectures will probably require using a more modern compiler
    static_assert(std::is_same<std::size_t, unsigned long>::value);
    std::size_t number = std::strtoul(numberString.c_str(), nullptr, 10);
#endif

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
