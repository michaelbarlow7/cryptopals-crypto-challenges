#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <string.h>

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

void repeatingKeyXor(char * key, vector<BYTE> text, char * xorred, int size, int keySize){
    //strncpy(xorred, text, size + 1);
    for (int i = 0; i < size; i++){
        xorred[i] = text[i];
    }
    xorred[size] = '\0';

    //int keySize = getArraySize(key);
    for (int i = 0; i < size; i++){
        xorred[i] ^= key[i % keySize];
        //printf("%02x", xorred[i]);
    }
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

    float smallestHammingDist = 8 * maxGuessSize;
    int likelyKeySize = -1;

    float distances[maxGuessSize];

    // Get four blocks, each of keysize length, and get hamming distances between each other (averaging)
    for (int keySize = 2; keySize <= maxGuessSize; ++keySize){
        char string1[keySize];
        char string2[keySize];
        for (int i = 0; i < keySize; i++){
            string1[i] = encryptedBytes[i];
            string2[i] = encryptedBytes[i + keySize];
        }
        float hammingDist = hammingDistance(string1, string2) / (float) keySize;

        // This is an average of all hamming distances
        //float hammingDist = (hammingDist1 + hammingDist2 + hammingDist3 + hammingDist4 + hammingDist5 + hammingDist6) / 6.0f;
        cout << hammingDist << ": Hamming distance: " << keySize << '\n';
        if (hammingDist < smallestHammingDist){
            smallestHammingDist = hammingDist;
            likelyKeySize = keySize;
        }
    }
    //TODO: Get top 4 sizes, then try each one and assess based on score.
    cout << "Likey KeySize: " << likelyKeySize << " with hamming distance: " << smallestHammingDist << '\n';
    return 0;
    //likelyKeySize = 29;

    // Top 4 in order were 23, 28, 40, 33
    // I think the naswer is 29. Need to fix the hamming distance thing above
    /*
     * 1. Now that you probably know the KEYSIZE: break the ciphertext into blocks of KEYSIZE length.
        2. Now transpose the blocks: make a block that is the first byte of every block, and a block that is the second byte of every block, and so on.
        3. Solve each block as if it was single-character XOR. You already have code to do this.
        4.For each block, the single-byte XOR key that produces the best looking histogram is the repeating-key XOR key byte for that block. Put them together and you have the key.
    */

    // An array of BYTE vectors
    vector<BYTE> encryptedBlocks[likelyKeySize];
    for (int i = 0; i < encryptedBytes.size(); i++) {
        encryptedBlocks[i % likelyKeySize].push_back(encryptedBytes[i]);
    }

    char xorKey[likelyKeySize];
    // Do each as a single-char xor
    for (int i = 0; i < likelyKeySize; i++){
        char maxChar = xorCipher(encryptedBlocks[i], encryptedBlocks[i].size());
        //cout << "MaxChar is: " << maxChar << "\n";
        cout << maxChar;
        xorKey[i] = maxChar;
    }
    cout << '\n';

    // xor with xorkey
    char xorred[encryptedBytes.size()];
    repeatingKeyXor(xorKey, encryptedBytes, xorred, encryptedBytes.size(), likelyKeySize);

    cout << "Xorred:\n" << xorred << "\n";

    return 0;
}
