
#include <stdio.h>

int main() {
    void swap(int *a, int *b);
    int array[20] = {0};
    int size = 0;
    int i = 0;
    scanf("%d", &i);
    while (i != -1) {//鬼 tm 信 0 是正整数
        array[size++] = i;
        scanf("%d", &i);
    }
    int pass = 1;
    if (size < 2) {
        if (size < 1) {
            printf("\n");
            return 0;
        }
        printf("%d\n", array[0]);
        return 0;
    }
    while (pass) {
        pass = 0;
        for (i = 1; i < size; ++i) {
            if (array[i - 1] % 2) {
                if (array[i] % 2) {
                    if (array[i] < array[i - 1]) {
                        swap(array + i, array + i - 1);
                        pass = 1;
                    }
                } else {
                    //do nothing
                }
            } else {
                if (array[i] % 2) {
                    swap(array + i, array + i - 1);
                    pass = 1;
                } else {
                    //do nothing
                }
            }
        }
    }
    for (i = 0; i < size; ++i) {
        printf("%d%s", array[i], i + 1 == size ? "\n" : " ");
    }
    return 0;
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
