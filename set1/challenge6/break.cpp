#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

typedef unsigned char BYTE;

static const std::string base64_chars = 
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";


static inline bool is_base64(BYTE c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}

/*vector<BYTE>*/void base64_decode(string const& encoded_string, vector<BYTE> * ret) {
    int in_len = encoded_string.size();
    int i = 0;
    int j = 0;
    int in_ = 0;
    BYTE char_array_4[4], char_array_3[3];

    while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
        char_array_4[i++] = encoded_string[in_]; in_++;
        if (i ==4) {
            for (i = 0; i <4; i++)
                char_array_4[i] = base64_chars.find(char_array_4[i]);

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; (i < 3); i++)
                ret->push_back(char_array_3[i]);
            i = 0;
        }
    }

    if (i) {
        for (j = i; j <4; j++)
            char_array_4[j] = 0;

        for (j = 0; j <4; j++)
            char_array_4[j] = base64_chars.find(char_array_4[j]);

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (j = 0; (j < i - 1); j++) ret->push_back(char_array_3[j]);
    }
}

int hammingDistance(char string1[], char string2[]){
    int ptr = 0;
    int count = 0;
    while(string1[ptr] && string2[ptr]){
        char diff = string1[ptr] ^ string2[ptr];
        for (int i = 0; i < 8; ++i){
            count += (diff >> i) & 0x01;
        }
        ptr++;
    }
    return count;
}

int main(int argc, char * argv[]){
    /*
    char string1[] = "this is a test";
    char string2[] = "wokka wokka!!!";
    int distance = hammingDistance(string1, string2);
    printf("Distance is %d\n", distance);
    */

    char c;
    ifstream myfile ("6.txt");

    string line;
    vector<BYTE> ret;
    if (myfile.is_open()){
        while (getline(myfile, line)){
            base64_decode(line, &ret);
        }
    } else {
        cout << "Unable to open file\n";
    }

    int maxGuessSize = 40;

    float smallestHammingDist = 8 * maxGuessSize;
    int likelyKeySize = -1;

    for (int keySize = 2; keySize <= maxGuessSize; ++keySize){
        char string1[keySize];
        char string2[keySize];
        for (int i = 0; i < keySize; i++){
            string1[i] = ret[i];
            string2[i] = ret[i + keySize];
        }
        float hammingDist = hammingDistance(string1, string2) / (float) keySize;
        //cout << keySize << ": Hamming distance: " << hammingDist << '\n';
        if (hammingDist < smallestHammingDist){
            smallestHammingDist = hammingDist;
            likelyKeySize = keySize;
        }
    }
    cout << "Likey KeySize: " << likelyKeySize << " with hamming distance: " << smallestHammingDist << '\n';

    // Top 4 were 30, 28, 40, 25

    return 0;
}
