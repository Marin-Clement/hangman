#ifndef HANGMAN_H
#define HANGMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 100
#define MAX_DICTIONARY_SIZE 100

#define MAX_TRIES 6

typedef struct {
    char word[MAX_LINE_LENGTH];
    char category[MAX_LINE_LENGTH];
    char difficulty[MAX_LINE_LENGTH];
} WordInfo;

void displayHangman(int guesses);

int isValidDifficulty(const char *difficulty);

int readDictionary(const char *filename, WordInfo *dictionary, int maxWords);

void startHangmanGame(const WordInfo *dictionary, int numWords, const char *difficulty, const char *category);

int selectValidWord(const WordInfo *dictionary, int numWords, const char *difficulty, const char *category);

void processUserGuess(const char *wordToGuess, char *guessedLetters, int *numWrongGuesses, int *letterUsed);

void printGameStatus(const WordInfo *wordInfo, const char *guessedLetters);

void printError(const char *message);

#endif