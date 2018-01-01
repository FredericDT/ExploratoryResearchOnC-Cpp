#include <cstdio>
#include <cstdlib>

void deepCopy(int *src, int *dest, int length);
void parseLongest(char *inputArray, int i, int j, int *travelled, int length, int *longest, int row, int column);

int main() {
    //handle ini input
    int n = 0;//row
    int m = 0;//column
    scanf("%d%d", &n, &m);
    char *inputArray = (char *) malloc(n * m * sizeof(char));
    for (int i = 0; i < n; ++i) {
        char *currentRow = inputArray + i * m;
        for (int j = 0; j < m; ++j) {
            char c = getchar();
            while (! (c >= 'A' && c <= 'Z')) {
                c = getchar();
            }
            *(currentRow + j) = c;
        }
    }
    //end of input handle
    int longest = 0;
    int travelled[26] = {0};
    parseLongest(inputArray, 0, 0, travelled, 0, &longest, n, m);
    printf("%d\n", longest);
    free(inputArray);
    return 0;
}

void parseLongest(char *inputArray, int i, int j, int *travelled, int length, int *longest, int row, int column) {
    int currentTravelled[26] = {0};
    deepCopy(travelled, currentTravelled, 26);
    currentTravelled[*(inputArray + i * column + j) - 'A'] = 1;
    length += 1;
    if (*longest < length) {
        *longest = length;
    }
    //rightward
    if (j + 1 < column) {
        if (!currentTravelled[*(inputArray + i * column + j + 1) - 'A']) {
            parseLongest(inputArray, i, j + 1, currentTravelled, length, longest, row, column);
        }
    }
    //downward
    if (i + 1 < row) {
        if (!currentTravelled[*(inputArray + (i + 1) * column + j) - 'A']) {
            parseLongest(inputArray, i + 1, j, currentTravelled, length, longest, row, column);
        }
    }
    //leftward
    if (j > 0) {
        if (!currentTravelled[*(inputArray + i * column + j - 1) - 'A']) {
            parseLongest(inputArray, i, j - 1, currentTravelled, length, longest, row, column);
        }
    }
    //upward
    if (i > 0) {
        if (!currentTravelled[*(inputArray + (i - 1) * column + j) - 'A']) {
            parseLongest(inputArray, i - 1, j, currentTravelled, length, longest, row, column);
        }
    }
}

void deepCopy(int *src, int *dest, int length) {
    for (int i = 0; i < length; ++i) {
        *(dest + i) = *(src + i);
    }
}
