#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// Assume firstString, secondString and resultString are the same length
void fixedXor(char * firstString, char * secondString, char * resultString){
    unsigned long int firstNum;
    unsigned long int secondNum;
    unsigned long int resultNum;

    unsigned long int bufferSize = sizeof(unsigned long int);
    char firstBuffer[bufferSize];
    char secondBuffer[bufferSize];
    char resultBuffer[bufferSize];
    int ptr = 0;
    while(firstString[ptr]){
        firstBuffer[ptr % bufferSize] = firstString[ptr];
        secondBuffer[ptr % bufferSize] = secondString[ptr];

        ptr++;
        if (!firstString[ptr] ||  (ptr % bufferSize == 0)){
            // Calculate result
            firstNum = strtoul(firstBuffer, NULL, 16);
            secondNum = strtoul(secondBuffer, NULL, 16);
            resultNum = firstNum ^ secondNum;

            // Convert to string
            sprintf(resultBuffer, "%lx", resultNum);

            // Copy result into resultString buffer
            strncpy(resultString, resultBuffer, bufferSize);
            resultString += bufferSize;

            // Clear buffers
            for (int i = 0; i < bufferSize; ++i){
                firstBuffer[i] = 0;
                secondBuffer[i] = 0;
                resultBuffer[i] = 0;
            }
        }
    }

}

int main(int argc, char* argv[]){
    char firstString[] = "1c0111001f010100061a024b53535009181c";
    char secondString[] = "686974207468652062756c6c277320657965";

    // Hacky but whatevs
    size_t strLength = 0;
    char * ptr = firstString;
    while (*ptr){
        ++strLength;
        ++ptr;
    }
    char resultString[strLength];

    fixedXor(firstString, secondString, resultString);
    printf("Result: %s\n", resultString);
    return 0;
}
