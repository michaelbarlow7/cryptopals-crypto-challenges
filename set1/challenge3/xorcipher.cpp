#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// Assume firstString, secondString and resultString are the same length
void fixedXor(char * firstString, char * secondString, char * resultString){
    //printf("1:|%s|\n2:|%s|\n3:|%s|\n", firstString, secondString, resultString);
    int ptr = 0;
    while(firstString[ptr] && secondString[ptr]){
        resultString[ptr] = firstString[ptr] ^ secondString[ptr];
        ++ptr;
    }
}

void xorCipher(char * hexString, char * resultString, int resultStringLength){
    unsigned long int num;
    int bufferSize = 2;//sizeof(unsigned long int);
    char buffer[bufferSize];
    int ptr = 0;
    char firstString[resultStringLength];
    char secondString[resultStringLength];
    while(hexString[ptr]){
        buffer[ptr % bufferSize] = hexString[ptr];

        ++ptr;
        if (!hexString[ptr] || (ptr % bufferSize == 0)){
            num = strtoul(buffer, NULL, 16);
            char c = (char) num;
            firstString[(ptr/2) - 1] = c;
        }

    }

    firstString[ptr/2] = '\0';
    secondString[ptr/2] = '\0';
    char c = 0x00;
    do {
        for (int i = 0; i < ptr/2; ++i){
            secondString[i] = c;
        }
        fixedXor(firstString, secondString, resultString);
        printf("c is %c. Result: %s\n",c, resultString);
        // TODO: Need to use metric to determine what the result is.
        // The answer is 'X' and it says "Cooking MC's like a pound of bacon"
        ++c;
    } while (c != 0x00);
}

int main(int argc, char* argv[]){
    char hexString[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

    // Hacky but whatevs
    size_t strLength = 0;
    char * ptr = hexString;
    while (*ptr){
        ++strLength;
        ++ptr;
    }

    char resultString[strLength/2];

    xorCipher(hexString, resultString, strLength/2);
    return 0;
}
