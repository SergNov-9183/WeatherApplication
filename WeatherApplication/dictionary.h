#ifndef DICTIONARY_H
#define DICTIONARY_H

#define MAX_WORD_SIZE 30
#define MAX_WORD_FORM 5
#define MAX_KEY_SIZE 30

typedef struct { char word[MAX_WORD_SIZE]; } word_t;

typedef struct {
    int count;
    char key[MAX_KEY_SIZE];
    word_t words[MAX_WORD_FORM];
} words_t;

void putData(words_t words);
char *getWord(const char *key);


#endif // DICTIONARY_H
