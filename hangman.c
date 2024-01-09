#include "hangman.h"

void displayHangman(int guesses);

void clearScreen() {
    printf("\033[2J\033[1;1H");
}

void displayLetterNotUsed(int letterUsed[26]) {
    printf("Lettres non utilisees: ");
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
    }
}

void startHangmanGame(const WordInfo *dictionary, int numWords, const char *difficulty, const char *category) {
    int numWrongGuesses = 0;
    int letterUsed[26] = {0};
    int validWords[MAX_DICTIONARY_SIZE];
    int numValidWords = 0;

    for (int i = 0; i < numWords; ++i) {
        if (strcmp(dictionary[i].difficulty, difficulty) == 0 &&
            (category == NULL || strcmp(dictionary[i].category, category) == 0)) {
            validWords[numValidWords++] = i;
        }
    }

    if (numValidWords == 0) {
        printf("Pas de mots disponibles pour la difficulte %s et la categorie %s\n", difficulty, category);
        return;
    }

    int wordIndex = validWords[rand() % numValidWords];
    const char *wordToGuess = dictionary[wordIndex].word;
    int wordLength = strlen(wordToGuess);
    char guessedLetters[wordLength];
    memset(guessedLetters, '_', wordLength);
    guessedLetters[wordLength] = '\0';

    while (numWrongGuesses < MAX_TRIES && strcmp(guessedLetters, wordToGuess) != 0) {
        clearScreen();
        displayHangman(numWrongGuesses);
        displayLetterNotUsed(letterUsed);
        printf("Categorie: %s\n", dictionary[wordIndex].category);
        printf("Difficulte: %s\n", dictionary[wordIndex].difficulty);
        printf("Mot a deviner: %s\n", guessedLetters);

        printf("Entrez une lettre: ");
        char guess;
        scanf(" %c", &guess);
        getchar();

        int found = 0;
        for (int i = 0; i < wordLength; ++i) {
            if (wordToGuess[i] == guess) {
                guessedLetters[i] = guess;
                found = 1;
            }
        }

        if (!found) {
            numWrongGuesses++;
        }

        letterUsed[guess - 'a'] = 1;
    }

    clearScreen();
    displayHangman(numWrongGuesses);
    printf("Categorie: %s\n", dictionary[wordIndex].category);
    printf("Difficulte: %s\n", dictionary[wordIndex].difficulty);
    printf("Mot a deviner: %s\n", guessedLetters);

    if (numWrongGuesses >= MAX_TRIES) {
        printf("Tu as perdu! Le mot etait: %s\n", wordToGuess);
    } else {
        printf("Tu as gagne!\n");
    }
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    WordInfo dictionary[MAX_DICTIONARY_SIZE];
    int numWords;
    const char *filename;
    const char *difficulty;
    const char *category = NULL;

    if (argc < 3 || argc > 4) {
        printf("Utilisation: %s <fichier> <difficulte> [categorie]\n", argv[0]);
        return 1;
    }

    filename = argv[1];
    difficulty = argv[2];

    if (argc == 4) {
        category = argv[3];
    }

    if (!isValidDifficulty(difficulty)) {
        printf("Difficulte invalide: %s\n", difficulty);
        return 1;
    }

    numWords = readDictionary(filename, dictionary, MAX_DICTIONARY_SIZE);
    if (numWords == -1) {
        printf("Impossible de lire le fichier %s\n", filename);
        return 1;
    }

    startHangmanGame(dictionary, numWords, difficulty, category);
    return 0;
}