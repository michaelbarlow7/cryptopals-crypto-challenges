#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;
/*
 * get length of line
 * make a new char buffer, copy line
 * for each char in key
 *  XOR against buffer and store in buffer
 *  print buffer
*/

int getArraySize(char * array){
    int ptr = 0;
    while (array[ptr]){
        ptr++;
    }
    return ptr;
}

void repeatingKeyXor(char * key, char * text, char * encrypted, int size){
    strncpy(encrypted, text, size + 1);

    int keySize = getArraySize(key);
    for (int i = 0; i < size; i++){
        encrypted[i] ^= key[i % keySize];
        printf("%02x", encrypted[i]);
    }
    printf("\n");
}


int main(int argc, char* argv[]){
    char key[] = "ICE";
    char line[] = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
    int size = getArraySize(line);
    char encrypted[size];
    repeatingKeyXor(key, line, encrypted, size);
    
    return 0;
}
