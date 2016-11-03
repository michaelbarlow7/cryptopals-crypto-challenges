#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <ctype.h>
#include <map>

using namespace std;

static const int strLength = 30; // We could calculate this but we're given it

// Assume firstString, secondString and resultString are the same length
void fixedXor(char * firstString, char * secondString, char * xorredString, int length){
    for (int i = 0; i < length; ++i) {
        xorredString[i] = firstString[i] ^ secondString[i];
    }
}

static map<char, int> scoreMap;

map<char, int> getScoreMap(){
    if (scoreMap.empty()){
        //printf("Empty\n");
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
    //}else{
        //printf("Not empty\n");
    }
    return scoreMap;
}

int scoreChar(char c){
    return getScoreMap()[c];
    /*
    c = tolower(c);
    if(isalpha(c)){
        return 1;
    }
    return 0;
    */
}

int xorCipher(char * firstString, char * resultString, int resultStringLength){
    int ptr = 0;
    char secondString[resultStringLength];

    char c = 0x00;
    int maxScore = 0;
    char maxScoredChar = c;

    char xorredString[resultStringLength];
    do {
        for (int i = 0; i < resultStringLength; ++i){
            secondString[i] = c;
        }
        fixedXor(firstString, secondString, xorredString, resultStringLength);
        //printf("%s\n", xorredString);

        int score = 0;
        ptr = 0;
        for (int i =0; i < resultStringLength; ++i) {
            //if(isalpha(xorredString[i])){
                //++score;
            //}
            score += scoreChar(xorredString[i]);
            ++ptr;
        }
        if (score > maxScore){
            maxScore = score;
            maxScoredChar = c;
            strncpy(resultString, xorredString, resultStringLength);
        }
        ++c;
    } while (c != 0x00);

    //printf("Winning xorred character is %c with score %d. Result: %s\n", maxScoredChar, maxScore, resultString);
    return maxScore;
}

int main(int argc, char* argv[]){
    string line;
    ifstream myfile ("4.txt");

    char bestString[strLength];

    if (myfile.is_open()){
        int highestScore = -1;
        while (getline (myfile, line)){
            const char * lineChars = line.c_str();
            int ptr = 0;
            char buffer[2];
            char unencoded[strLength];
            while(lineChars[ptr]){
                buffer[ptr % 2] = lineChars[ptr];
                ++ptr;
                if (!lineChars[ptr] || (ptr % 2 == 0)){
                    int num = strtoul(buffer, NULL, 16);
                    char c = (char) num;
                    unencoded[(ptr/2) - 1] = c;
                }
            }
            //printf("%s\n", unencoded);
            char resultString[strLength];

            int score = xorCipher(unencoded, resultString, strLength);
            printf("%d, resultString: %s\n", score, resultString);

            if (score > highestScore){
                strncpy(bestString, resultString, strLength);
            }

        }

        //printf("Best string %s\n", bestString);
        myfile.close();
    }else{
        cout << "Unable to open file\n";
    }

    return 0;
}
