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

void xorCipher(char * hexString, char * resultString, int resultStringLength){
    unsigned long int num;
    int bufferSize = 2;//sizeof(unsigned long int);
    char buffer[bufferSize];
    int ptr = 0;
    while(hexString[ptr]){
        buffer[ptr % bufferSize] = hexString[ptr];

        ++ptr;
        if (!hexString[ptr] || (ptr % bufferSize == 0)){
            num = strtoul(buffer, NULL, 16);
            char c = (char) num;
            resultString[(ptr/2) - 1] = c;
        }

    }
    printf("\n");
    resultString[ptr/2] = '\0';
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
    printf("Result: %s\n", resultString);
    return 0;
}
