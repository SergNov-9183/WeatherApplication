#include "dictionary.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS
#define MAX_WORD_COUNT 500

words_t dictionary[MAX_WORD_COUNT];
int wordCout = 0;
char badWord[MAX_WORD_SIZE] = {0};

int firstUse = 1;
int random(int count) {
    if (firstUse == 1) {
        firstUse = 0;
        srand((unsigned int)time(NULL));
    }
    return rand() % count;
}

void putData(words_t words) {
    dictionary[wordCout] = words;
    ++wordCout;
}

char* getWord(const char* key) {
    for (int i = 0; i < wordCout; ++i) {
        if (strcmp(key, dictionary[i].key) == 0) {
            return dictionary[i].words[random(dictionary[i].count)].word;
        }
    }
    return badWord;
}
