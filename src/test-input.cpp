#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <array>
#include <iostream>

#include "../src/input.cpp"

int main() {
    char a = '\0';
    printf("Erst Buchstabe dann Zahl \nKoordinaten eingeben :");
    scanf("%s", &a);
    struct BoardPoint neu = inputTranslator(&a);
    printf("(%d|%d)\n", neu.x, neu.y);
    return EXIT_SUCCESS;
}