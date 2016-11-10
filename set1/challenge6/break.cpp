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

void base64_decode(string const& encoded_string, vector<BYTE> * ret) {
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
    /*
    for (int i = 0; i < ret.size(); i++){
        cout << ret[i];
    }
    cout << '\n';
    */

    int maxGuessSize = 40;

    float smallestHammingDist = 8 * maxGuessSize;
    int likelyKeySize = -1;

    for (int keySize = 2; keySize <= maxGuessSize; ++keySize){
        char string1[keySize];
        char string2[keySize];
        char string3[keySize];
        char string4[keySize];
        for (int i = 0; i < keySize; i++){
            string1[i] = ret[i];
            string2[i] = ret[i + keySize];
            string3[i] = ret[i + 2*keySize];
            string4[i] = ret[i + 3*keySize];
        }
        float hammingDist1 = hammingDistance(string1, string2) / (float) keySize;
        float hammingDist2 = hammingDistance(string1, string3) / (float) keySize;
        float hammingDist3 = hammingDistance(string1, string4) / (float) keySize;
        float hammingDist4 = hammingDistance(string2, string3) / (float) keySize;
        float hammingDist5 = hammingDistance(string2, string4) / (float) keySize;
        float hammingDist6 = hammingDistance(string3, string4) / (float) keySize;

        float hammingDist = (hammingDist1 + hammingDist2 + hammingDist3 + hammingDist4 + hammingDist5 + hammingDist6) / 6.0f;
        //cout << hammingDist << ": Hamming distance: " << keySize << '\n';
        if (hammingDist < smallestHammingDist){
            smallestHammingDist = hammingDist;
            likelyKeySize = keySize;
        }
    }
    //cout << "Likey KeySize: " << likelyKeySize << " with hamming distance: " << smallestHammingDist << '\n';

    //vec<BYTE*>
    for (int i = 0; i < ret.size(); i++){
    }
    // Top 4 in order were 23, 28, 40, 33
    /*
     * 1. Now that you probably know the KEYSIZE: break the ciphertext into blocks of KEYSIZE length.
        2. Now transpose the blocks: make a block that is the first byte of every block, and a block that is the second byte of every block, and so on.
        3. Solve each block as if it was single-character XOR. You already have code to do this.
        4.For each block, the single-byte XOR key that produces the best looking histogram is the repeating-key XOR key byte for that block. Put them together and you have the key.
    */

    return 0;
}
