#include "hangman.h"

void clearScreen() {
    printf("\033[2J\033[1;1H");
}

void displayLetterNotUsed(int letterUsed[26]) {
    printf("Letters not used: ");
    for (int i = 0; i < 26; ++i) {
        if (!letterUsed[i]) {
            printf("%c ", 'a' + i);
        }
    }
    printf("\n");
}

void displayHangman(int guesses) {
    switch (guesses) {
        case 0:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("      |\n");
            printf("      |\n");
            printf("      |\n");
            printf("      |\n");
            printf("=========\n");
            break;
        case 1:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf("      |\n");
            printf("      |\n");
            printf("      |\n");
            printf("=========\n");
            break;
        case 2:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf("  |   |\n");
            printf("      |\n");
            printf("      |\n");
            printf("=========\n");
            break;
        case 3:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf(" /|   |\n");
            printf("      |\n");
            printf("      |\n");
            printf("=========\n");
            break;
        case 4:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf(" /|\\  |\n");
            printf("      |\n");
            printf("      |\n");
            printf("=========\n");
            break;
        case 5:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf(" /|\\  |\n");
            printf(" /    |\n");
            printf("      |\n");
            printf("=========\n");
            break;
        case 6:
            printf("  +---+\n");
            printf("  |   |\n");
            printf("  O   |\n");
            printf(" /|\\  |\n");
            printf(" / \\  |\n");
            printf("      |\n");
            printf("=========\n");
            break;
        default:
            printf("[ERROR] Invalid number of wrong guesses: %d\n", guesses);
    }
}

void startHangmanGame(const WordInfo *dictionary, int numWords, const char *difficulty, const char *category) {
    int numWrongGuesses = 0;
    int letterUsed[26] = {0};
    int gameWon = 0;

    int wordIndex = selectValidWord(dictionary, numWords, difficulty, category);
    if (wordIndex == -1) {
        printf("No words available for difficulty %s and category %s\n", difficulty, category);
        return;
    }

    const char *wordToGuess = dictionary[wordIndex].word;
    int wordLength = strlen(wordToGuess);
    char guessedLetters[wordLength + 1];
    memset(guessedLetters, '_', wordLength);
    guessedLetters[wordLength] = '\0';

    while (numWrongGuesses < MAX_TRIES && strcmp(guessedLetters, wordToGuess) != 0) {
        clearScreen();
        displayHangman(numWrongGuesses);
        displayLetterNotUsed(letterUsed);
        printGameStatus(&dictionary[wordIndex], guessedLetters);

        processUserGuess(wordToGuess, guessedLetters, &numWrongGuesses, letterUsed);

        if (strcmp(guessedLetters, wordToGuess) == 0) {
            gameWon = 1; // Set the flag to indicate that the game is won
        }
    }

    clearScreen();
    displayHangman(numWrongGuesses);
    printGameStatus(&dictionary[wordIndex], guessedLetters);

    if (gameWon) {
        printf("You won!\n");
    } else {
        printf("You lost! The word was: %s\n", wordToGuess);
    }
}

// New function to select a valid word based on difficulty and category
int selectValidWord(const WordInfo *dictionary, int numWords, const char *difficulty, const char *category) {
    int validWords[MAX_DICTIONARY_SIZE];
    int numValidWords = 0;

    for (int i = 0; i < numWords; ++i) {
        if (strcmp(dictionary[i].difficulty, difficulty) == 0 &&
            (category == NULL || strcmp(dictionary[i].category, category) == 0)) {
            validWords[numValidWords++] = i;
        }
    }

    return (numValidWords > 0) ? validWords[rand() % numValidWords] : -1;
}

void processUserGuess(const char *wordToGuess, char *guessedLetters, int *numWrongGuesses, int *letterUsed) {
    char letter;
    printf("Enter a letter: ");
    scanf(" %c", &letter);

    if (!isalpha(letter)) {
        printf("Error: you must enter a letter\n");
        return;
    }

    letter = tolower(letter);

    if (letterUsed[letter - 'a']) {
        printf("You've already entered the letter %c\n", letter);
        return;
    }

    letterUsed[letter - 'a'] = 1;

    int found = 0;
    for (int i = 0; wordToGuess[i] != '\0'; ++i) {
        if (wordToGuess[i] == letter) {
            guessedLetters[i] = letter;
            found = 1;
        }
    }

    if (!found) {
        (*numWrongGuesses)++;
    }
}

// New function to print game status
void printGameStatus(const WordInfo *wordInfo, const char *guessedLetters) {
    printf("Category: %s\n", wordInfo->category);
    printf("Difficulty: %s\n", wordInfo->difficulty);
    printf("Word to guess: %s\n", guessedLetters);
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    WordInfo dictionary[MAX_DICTIONARY_SIZE];
    int numWords;
    const char *filename;
    const char *difficulty;
    const char *category = NULL;

    if (argc < 3 || argc > 4) {
        printf("Usage: %s <file> <difficulty> [category]\n", argv[0]);
        return 1;
    }

    filename = argv[1];
    difficulty = argv[2];

    if (argc == 4) {
        category = argv[3];
    }

    if (!isValidDifficulty(difficulty)) {
        printf("Invalid difficulty: %s\n", difficulty);
        return 1;
    }

    numWords = readDictionary(filename, dictionary, MAX_DICTIONARY_SIZE);
    if (numWords == -1) {
        printf("Unable to read file %s\n", filename);
        return 1;
    }

    do {
        startHangmanGame(dictionary, numWords, difficulty, category);

        char answer;
        printf("Do you want to play another round? (y/n) ");
        scanf(" %c", &answer);
        if (answer != 'y' && answer != 'Y') {
            break;
        }
    } while (1);

    return 0;
}
