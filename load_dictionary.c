#define _CRT_SECURE_NO_WARNINGS
#define MAX_DATA_SIZE 200

#include "load_dictionary.h"

#include <stdio.h>

#include "dictionary.h"



int readValue(int startPos, char* str, char* value) {
    int i = 0;
    for (; startPos < MAX_DATA_SIZE; ++startPos) {
        if (str[startPos] == ':') {
            value[i] = 0;
            return startPos;
        }
        if (str[startPos] == 0 || str[startPos] == '\n' || str[startPos] == '\r') {
            value[i] = 0;
            return -1;
        }

        value[i] = str[startPos];
        ++i;
    }
    return -1;
}

void loadDictionary(const char* fileName) {
    FILE* df = fopen(fileName, "rt");
    if (df == NULL) {
        printf("Error with openning file!");
        return ;
    }

    while (!feof(df)) {
        char str[MAX_DATA_SIZE];
        if (!fgets(str, MAX_DATA_SIZE, df)) {
            continue;
        }

        words_t words;
        words.count = 0;

        int pos = readValue(0, str, words.key);
        while (pos > -1) {
            pos = readValue(++pos, str, words.words[words.count++].word);
        }

        putData(words);
    }

    while (!feof(df)) {
    }

    fclose(df);
}
