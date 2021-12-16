#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <array>
#include <iostream>

#include "../include/fieldinfo.hpp"

struct coordinates{ 
    int number=0;
    int letter=0;
};

coordinates inputTranslator(char *input){
   struct coordinates transInput;
   transInput.letter= (int) (input[0]-'A'+1);
   input[0]='0';
   transInput.number= atoi(input);
   return transInput;
}

int main(){
    char a='\0';
    printf("Erst Buchstabe dann Zahl \nKoordinaten eingeben :");
    scanf("%s",&a);
    struct coordinates neu = inputTranslator(&a);
    printf("(%d|%d)\n",neu.letter,neu.number);
    return EXIT_SUCCESS;
}