#include <stdio.h>
int parse(int thief, int ability);
int allMin1(int thief);
int countThief(int before, int after);
int main() {
    int thief = 0;
    int count = 0;
    int i = getchar();
    int police = 0;
    while(i != '\n') {
        if (i == 'X') {
            if (police > 0) {
                count += 1;
            } else {
                thief = thief * 10 + 9;
            }
        } else if (i >= '1' && i <= '9') {
            int current = i - '0' + 1;
            int tmp = parse(thief, current);
            count += countThief(thief, tmp);
            thief = tmp;
            police = police > current ? police : current;
        }
        thief = allMin1(thief);
        police -= 1;
        i = getchar();
    }
    printf("%d", count);
}
int countThief(int before, int after) {
    while (after > 0) {
        before /= 10;
        after /= 10;
    }
    int count = 0;
    while (before > 0) {
        before /= 10;
        count += 1;
    }
    return count;
}
int parse(int thief, int ability) {
    int current = 1;
    int prefix = thief / current;
    //int count = 0;
    while (prefix > 0) {
        if (10 - prefix % 10 <= ability) {
            //count += 1;
            thief = prefix / 10 + thief % current;
        } else {
            current *= 10;
        }
        prefix = thief / current;
    }
    //return count;
    return thief;
}
int allMin1(int thief) {
    int result = 0;
    while(thief > 0) {
        result = result * 10 + thief % 10 - 1;
        thief /= 10;
    }
    return result;
}
