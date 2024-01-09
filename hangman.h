#ifndef HANGMAN_H
#define HANGMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100
#define MAX_DICTIONARY_SIZE 100

typedef struct {
    char word[MAX_LINE_LENGTH];
    char category[MAX_LINE_LENGTH];
    char difficulty[MAX_LINE_LENGTH];
} WordInfo;

int isValidDifficulty(const char *difficulty);

int readDictionary(const char *filename, WordInfo *dictionary, int maxWords);

void startHangmanGame(const WordInfo *dictionary, int numWords, const char *difficulty);

#endif