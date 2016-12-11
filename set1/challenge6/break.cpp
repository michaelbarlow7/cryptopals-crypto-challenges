#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <string.h>

#define KEYSIZE_GUESS_AMOUNT 4

using namespace std;

typedef unsigned char BYTE;


static map<char, int> scoreMap;

map<char, int> getScoreMap(){
    if (scoreMap.empty()){
        scoreMap['e'] = 26;
        scoreMap['t'] = 25;
        scoreMap['a'] = 24;
        scoreMap['o'] = 23;
        scoreMap['i'] = 22;
        scoreMap['n'] = 21;
        scoreMap['s'] = 20;
        scoreMap['h'] = 19;
        scoreMap['r'] = 18;
        scoreMap['d'] = 17;
        scoreMap['l'] = 16;
        scoreMap['c'] = 15;
        scoreMap['u'] = 14;
        scoreMap['m'] = 13;
        scoreMap['w'] = 12;
        scoreMap['f'] = 11;
        scoreMap['g'] = 10;
        scoreMap['y'] = 9;
        scoreMap['p'] = 8;
        scoreMap['b'] = 7;
        scoreMap['v'] = 6;
        scoreMap['k'] = 5;
        scoreMap['j'] = 4;
        scoreMap['x'] = 3;
        scoreMap['q'] = 2;
        scoreMap['z'] = 1;
    }
    return scoreMap;
}

int scoreChar(char c){
    return getScoreMap()[c];
}

// XOR first string with second string and put result in xorredString
void fixedXor(vector<BYTE> firstString, char * secondString, char * xorredString, int length){
    for (int i = 0; i < length; ++i) {
        xorredString[i] = firstString[i] ^ secondString[i];
    }
}

char xorCipher(vector<BYTE> firstString, int resultStringLength){
    int ptr = 0;
    char secondString[resultStringLength];
    char xorredString[resultStringLength];
    char resultString[resultStringLength];

    char c = 0x00;
    int maxScore = 0;
    char maxScoredChar = c;

    do {
        // Second string is just a string with all characters set to c
        for (int i = 0; i < resultStringLength; ++i) {
            secondString[i] = c;
        }
        fixedXor(firstString, secondString, xorredString, resultStringLength);

        int score = 0;
        ptr = 0;

        for (int i =0; i < resultStringLength; ++i) {
            score += scoreChar(xorredString[i]);
            ++ptr;
        }

        /*
        if (c == 'n'){
            cout << c << ": ";
            for (int i =0; i < resultStringLength; ++i) {
                cout << xorredString[i];
            }
            cout << '\n';
        }
        */

        if (score > maxScore){
            maxScore = score;
            maxScoredChar = c;
            strncpy(resultString, xorredString, resultStringLength);
        }
        ++c;
    } while (c != 0x00);

    /*
    cout << maxScoredChar << ": ";
    for (int i =0; i < resultStringLength; ++i) {
        cout << resultString[i];
    }
    cout << '\n';
    */


    return maxScoredChar;
}

int repeatingKeyXor(char * key, vector<BYTE> text, char * xorred, int size, int keySize){
    //strncpy(xorred, text, size + 1);
    for (int i = 0; i < size; i++){
        xorred[i] = text[i];
    }
    xorred[size] = '\0';

    int score = 0;
    //int keySize = getArraySize(key);
    for (int i = 0; i < size; i++){
        xorred[i] ^= key[i % keySize];
        //printf("%02x", xorred[i]);
        score += scoreChar(xorred[i]);
    }
    return score;
    //printf("\n");
}

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
    vector<BYTE> encryptedBytes;
    if (myfile.is_open()){
        while (getline(myfile, line)){
            base64_decode(line, &encryptedBytes);
        }
    } else {
        cout << "Unable to open file\n";
    }

    /*
    for (int i = 0; i < encryptedBytes.size(); i++){
        cout << encryptedBytes[i];
    }
    cout << '\n';
    */

    // We have the file decoded from base64 now

    int maxGuessSize = 40;

    float distances[maxGuessSize];

    // Get four blocks, each of keysize length, and get hamming distances between each other (averaging)
    for (int keySize = 2; keySize <= maxGuessSize; ++keySize){
        char string1[keySize];
        char string2[keySize];
        for (int i = 0; i < keySize; i++){
            string1[i] = encryptedBytes[i];
            string2[i] = encryptedBytes[i + keySize];
        }
        distances[keySize] = hammingDistance(string1, string2) / (float) keySize;
    }
    float largestSmallest = -1.0f;
    int keySizes[KEYSIZE_GUESS_AMOUNT];
    for (int i = 0; i < KEYSIZE_GUESS_AMOUNT; i++){
        float smallestHammingDist = 8 * maxGuessSize;
        int smallestKeySize = -1;
        for (int j = 2; j <= maxGuessSize; j++){
            if (distances[j] <= largestSmallest){
                continue;
            }
            if (distances[j] < smallestHammingDist){
                smallestHammingDist = distances[j];
                smallestKeySize = j;
            }
        }
        keySizes[i] = smallestKeySize;
        largestSmallest = smallestHammingDist;
    }

    char maxXorred[encryptedBytes.size()];
    int maxScore = -1;
    for (int j = 0; j < KEYSIZE_GUESS_AMOUNT; j++) {
        int likelyKeySize = keySizes[j];
        char xorKey[likelyKeySize];
        // An array of BYTE vectors
        vector<BYTE> encryptedBlocks[likelyKeySize];
        for (int i = 0; i < encryptedBytes.size(); i++) {
            encryptedBlocks[i % likelyKeySize].push_back(encryptedBytes[i]);
        }

        char tmpXorKey[likelyKeySize];
        // Do each as a single-char xor
        for (int i = 0; i < likelyKeySize; i++){
            char maxChar = xorCipher(encryptedBlocks[i], encryptedBlocks[i].size());
            xorKey[i] = maxChar;
        }

        char xorred[encryptedBytes.size()];
        // Find highest score
        int score = repeatingKeyXor(xorKey, encryptedBytes, xorred, encryptedBytes.size(), likelyKeySize);
        if (score > maxScore){
            maxScore = score;
            strncpy(maxXorred, xorred, encryptedBytes.size());
        }
    }
    cout << maxXorred << "\n";
    return 0;
}
