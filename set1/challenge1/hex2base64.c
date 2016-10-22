#include <stdio.h>

static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};

char * hexToBase64(char hexString[]){
    char buffer[6];
    buffer[6] = '\0';
    while (*hexString){
        //TODO: Handle case where 3 bytes (6 chars) aren't available
        strncpy(buffer, hexString, 6);
        hexString += 6;

        //printf("buffer: %s\n", buffer);

        unsigned long int num = strtoul(buffer, NULL, 16);
        //printf("num is %x\n", num);

        // Get first 6 bits, shift them
        unsigned char b64index = (num & 0xFFFFFF) >> 18;
        char b64char = encoding_table[b64index];
        printf("%c", b64char);

        b64index = (num & 0x03FFFF) >> 12;
        b64char = encoding_table[b64index];
        printf("%c", b64char);

        b64index = (num & 0x000FFF) >> 6;
        b64char = encoding_table[b64index];
        printf("%c", b64char);

        b64index = (num & 0x00003F);
        b64char = encoding_table[b64index];
        printf("%c", b64char);
    }
    printf("\n");
    //TODO: Add chars to an array (fuck why did I pick C :/)
    //char array1[18] = "abcdefgh";
    //strncpy(buffer, hexString, 6);
    //char array2[3];

    //strncpy(array2, hexString, 3);
    //array2[3] = '\0';
    //printf("buffer: %s\n", buffer);
    //char * str = "0f";
    //unsigned long int num = strtoul(str, NULL, 16);
    //printf("num is %d\n", num);
    return hexString;
}

int main(int argc, char* argv[]){
    char * hexString = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    // Should be SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t
    char * base64String = hexToBase64(hexString);
    printf("%s\n", "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t");
    //printf("%s\n", hexString);
    //printf("%s\n", base64String);
    return 0;
}
