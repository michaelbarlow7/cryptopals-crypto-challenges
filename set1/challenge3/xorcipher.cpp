#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

using namespace std;

// Assume firstString, secondString and resultString are the same length
void fixedXor(char * firstString, char * secondString, char * xorredString, int length){
    for (int i = 0; i < length; ++i) {
        xorredString[i] = firstString[i] ^ secondString[i];
    }
}

void xorCipher(char * hexString, char * resultString, int resultStringLength){
    unsigned long int num;
    int bufferSize = 2; // 2 hex characters == 1 byte (1 char)
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

    char c = 0x00;
    int maxScore = 0;
    char maxScoredChar = c;

    char xorredString[resultStringLength];
    do {
        for (int i = 0; i < resultStringLength; ++i){
            secondString[i] = c;
        }
        fixedXor(firstString, secondString, xorredString, resultStringLength);

        int score = 0;
        ptr = 0;
        for (int i =0; i < resultStringLength; ++i) {
            if(isalpha(xorredString[i])){
                ++score;
            }
            ++ptr;
        }
        if (score > maxScore){
            maxScore = score;
            maxScoredChar = c;
            strncpy(resultString, xorredString, resultStringLength);
        }
        ++c;
    } while (c != 0x00);

    printf("Winning xorred character is %c with score %d. Result: %s\n", maxScoredChar, maxScore, resultString);
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
