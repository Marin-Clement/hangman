#include "hangman.h"

int isValidDifficulty(const char *difficulty) {
    return (strcmp(difficulty, "facile") == 0 || strcmp(difficulty, "moyen") == 0 || strcmp(difficulty, "difficile") == 0);
}

int readDictionary(const char *filename, WordInfo *dictionary, int maxWords) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return 0;
    }

    int validWordCount = 0;
    int lineCount = 0;
    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), file) && validWordCount < maxWords) {
        lineCount++;
        if (line[0] == '#') {
            continue;
        }

        WordInfo wordInfo;
        int readItems = sscanf(line, "%[^,],%[^,],%s", wordInfo.word, wordInfo.category, wordInfo.difficulty);

        if (readItems != 3 || !isValidDifficulty(wordInfo.difficulty)) {
            printf("Error in line %d: %s", lineCount, line);
            continue;
        }

        dictionary[validWordCount++] = wordInfo;
    }

    fclose(file);

    return validWordCount;
}