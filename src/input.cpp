#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <array>
#include <iostream>

#include "../include/fieldinfo.hpp"

BoardPoint inputTranslator(char* input) {
    int letter = (int)(input[0] - 'A' + 1);
    input[0] = '0';
    int number = atoi(input);
    struct BoardPoint PlayerInput(number, letter);
    return PlayerInput;
}

