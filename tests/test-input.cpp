#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "../include/input.hpp"

int main() {
    std::string a;
    printf("Erst Buchstabe dann Zahl\nKoordinaten eingeben: ");
    std::cin >> a;
    BoardPoint neu = inputTranslator(a);
    std::cout << '(' << neu.x << '|' << neu.y << ")\n";
    return EXIT_SUCCESS;
}
