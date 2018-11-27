#include <iostream>
#include <string>

bool equals(char s, char p) {
    return s == p;
}

long indexOf(std::string const &source, std::string const &pattern, long startIndex, bool (*eqf)(char s, char p)) {
    if (startIndex < 0) {
        return -1;
    }
    if (pattern.length() < 1) {
        return 0;
    }
    while (true) {
        if (startIndex + pattern.length() > source.length()) {
            return -1;
        }
        long currentPatternIndex = pattern.length() - 1;
        long currentSourceIndex = startIndex + currentPatternIndex;
        while (currentPatternIndex >= 0 && eqf(source[currentSourceIndex], pattern[currentPatternIndex])) {
            --currentPatternIndex;
            --currentSourceIndex;
        }
        if (currentPatternIndex < 0) {
            return startIndex;
        }
        long badPatternIndex = currentPatternIndex;
        char lastOfSource = source[badPatternIndex];
        while (--badPatternIndex >= 0 && !eqf(pattern[badPatternIndex], lastOfSource));
        long moveTo = startIndex + currentPatternIndex - badPatternIndex;

        long foundGoodHead = -1;
        long goodPatternStartBase = currentSourceIndex - 1;
        while (goodPatternStartBase < currentPatternIndex) {
            long goodPatternStart = goodPatternStartBase;
            long goodPatternEnd = currentPatternIndex;
            while (++goodPatternEnd < pattern.length() && eqf(pattern[goodPatternEnd], pattern[goodPatternStart++]));
            if (goodPatternEnd >= pattern.length()) {
                foundGoodHead = goodPatternStartBase + pattern.length() - currentPatternIndex;
                break;
            }
            if (foundGoodHead >= 0) {
                break;
            }
            ++goodPatternStartBase;
        }
        long goodMoveTo = startIndex + pattern.length() - 1 - foundGoodHead;
        moveTo = moveTo > goodMoveTo ? moveTo : goodMoveTo;

        startIndex = moveTo;
    }
}

int main(int argc, char **argv) {
    std::string s = "i m here thio say .hi";
    std::string p = "hi";
    std::cout << indexOf(s, p, 0, &equals) << std::endl;
    return 0;
}