#include <stdio.h>
#define error "The letters are not adjacent with each other."
#define ok "The letters are adjacent with each other."
int main() {

    char last = ' ', current = ' ';
    current = getchar();
    last = current - 1;
    for(int i = 0; i < 3; i++) {
        if (current > 'z' || (current < 'a' && current > 'Z') || current < 'A' || current - last != 1) {
            printf(error);
            return 0;
        }
        last = current;
        current = getchar();
    }

    if (current == '\n') {
        printf(ok);
        return 0;
    }
    printf(error);
    return 0;
}

