#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

using namespace std;

static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};

void hexToBase64(char hexString[], vector<char> * charVec){
    char buffer[6];
    buffer[6] = '\0';
    while (*hexString){
        strncpy(buffer, hexString, 6);
        hexString += 6;

        unsigned long int num = strtoul(buffer, NULL, 16);

        unsigned char b64index;
        char b64char;

        b64index = num >> 18;
        b64char = encoding_table[b64index];
        charVec->push_back(b64char);

        b64index = (num & 0x03FFFF) >> 12;
        b64char = encoding_table[b64index];
        charVec->push_back(b64char);

        if (hexString[1] == '\0' || hexString[2] == '\0'){
            charVec->push_back('=');
            charVec->push_back('=');
            break;
        }
        b64index = (num & 0x000FFF) >> 6;
        b64char = encoding_table[b64index];
        charVec->push_back(b64char);

        if (hexString[3] == '\0' || hexString[4] == '\0'){
            charVec->push_back('=');
            break;
        }
        b64index = (num & 0x00003F);
        b64char = encoding_table[b64index];
        charVec->push_back(b64char);
    }
}

int main(int argc, char* argv[]){
    char * hexString = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    vector<char> charVec;
    hexToBase64(hexString, &charVec);

    int i = 0;
    while (charVec[i]) {
        printf("%c", charVec[i++]);
    }
    printf("\n");
    // Should be SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t

    return 0;
}
