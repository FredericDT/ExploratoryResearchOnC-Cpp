#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>

//#define DEBUG

namespace fdt {
    bool equals(char s, char p) {
        return s == p;
    }

    bool equalsWithGeneric(char s, char p) {
        return s == p || p == '*';
    }

    class BoyerMoorePattern {
    private:
        BoyerMoorePattern() : eqf(nullptr) {
            throw "Error";
        }

        std::string pattern;
        std::vector<std::map<char, long>> badCharacterMaps;

        void initBadCharacterMap() {
            for (long i = 1; i < pattern.length(); ++i) {
                std::map<char, long> cm{};
                if (!this->badCharacterMaps.empty()) {
                    cm = this->badCharacterMaps[this->badCharacterMaps.size() - 1];
                }
                cm[pattern[i]] = i;
                this->badCharacterMaps.push_back(cm);
            }
        }

        long getBadPatternIndex(long index, char target) {
            if (index > 0) {
                std::map<char, long> m = this->badCharacterMaps[index - 1];
                return m.find(target) == m.end() ? -1 : m[target];
            }
            return -1;
        }

        bool (*eqf)(char s, char p);

    public:
        BoyerMoorePattern(std::string const &pattern, bool (*equalsFunction)(char s, char p))
                : badCharacterMaps{}, eqf(equalsFunction) {
            this->pattern = std::string(pattern);
            this->initBadCharacterMap();
        }

        ~BoyerMoorePattern() = default;

        void parseGoodSuffix(std::string const &pattern, long goodSuffix[]) {
            for (long i = pattern.length() - 1; i >= 0; --i) {
                long longestLength = 1;
                long index = -1;
                for (long j = i - 1; j >= 0; --j) {
                    long ii = i;
                    long jj = j;
                    while (jj >= 0 && pattern[ii] == pattern[jj]) {
                        --ii;
                        --jj;
                    }
                    long cl = j - jj;
                    if (cl >= longestLength) {
                        longestLength = cl;
                        index = j;
                    }
                }
                goodSuffix[i] = index;
            }
        }

        long indexOf(std::string const &source, long startIndex) {
            if (startIndex < 0) {
                return -1;
            }
            if (pattern.length() < 1) {
                return 0;
            }
            while (startIndex + pattern.length() <= source.length()) {
                long currentPatternIndex = pattern.length() - 1;
                long currentSourceIndex = startIndex + currentPatternIndex;
                while (currentPatternIndex >= 0 && eqf(source[currentSourceIndex], pattern[currentPatternIndex])) {
                    --currentPatternIndex;
                    --currentSourceIndex;
                }
                if (currentPatternIndex < 0) {
                    return startIndex;
                }
//                long badPatternIndex = currentPatternIndex;
//                char lastOfSource = source[currentSourceIndex];
//                while (--badPatternIndex >= 0 && !eqf(lastOfSource, pattern[badPatternIndex]));
                long badPatternIndex = getBadPatternIndex(currentPatternIndex, source[currentSourceIndex]);
                long moveTo = startIndex + currentPatternIndex - badPatternIndex;

                if (currentPatternIndex + 1 == pattern.length()) {
                    startIndex = moveTo;
                    continue;
                }

//        long foundGoodHead = -1;
//        long goodPatternStartBase = currentSourceIndex - 1;
//        while (goodPatternStartBase < currentPatternIndex) {
//            long goodPatternStart = goodPatternStartBase;
//            long goodPatternEnd = currentPatternIndex;
//            while (++goodPatternEnd < pattern.length() && eqf(pattern[goodPatternEnd], pattern[goodPatternStart++]));
//            if (goodPatternEnd >= pattern.length()) {
//                foundGoodHead = goodPatternStartBase + pattern.length() - currentPatternIndex;
//                break;
//            }
//            if (foundGoodHead >= 0) {
//                break;
//            }
//            ++goodPatternStartBase;
//        }
//        long goodMoveTo = startIndex + pattern.length() - 1 - foundGoodHead;
//        moveTo = moveTo > goodMoveTo ? moveTo : goodMoveTo;

                startIndex = moveTo;
            }
            return -1;
        }

        std::vector<long> getAllIndexOf(std::string const &source, long startIndex) {
            std::vector<long> v{};
            long pos = startIndex - pattern.length();
            while (true) {
                pos = indexOf(source, pos + pattern.length());
                if (pos != -1) {
                    v.push_back(pos);
                } else {
                    break;
                }
            }
            return v;
        }
    };
}

int main(int argc, char **argv) {
#ifndef DEBUG
    if (argc < 3) {
        std::cout << "Usage: Boyer_Moore <filepath> <pattern> [withGeneric<0|1>]" << std::endl;
        exit(1);
    }
    bool (*eqf)(char s, char p) = &fdt::equals;
    if (argc == 4) {
        if (*argv[3] == '1') {
            eqf = &fdt::equalsWithGeneric;
        }
    }
    std::ifstream inFile;
    inFile.open(argv[1]);
    std::stringstream stringStream;
    stringStream << inFile.rdbuf();
    std::string s = stringStream.str();
    inFile.close();
    std::string p(argv[2]);
#else
    std::string s("HERE_IS_A_SIMPLE_EXAMPLE");
    std::string p("EXAMPLE");
    bool (*eqf)(char s, char p) = &fdt::equals;
#endif
    fdt::BoyerMoorePattern bmp(p, eqf);
    std::vector<long> v = bmp.getAllIndexOf(s, 0);
    for (auto &i : v) {
        std::cout << i << std::endl;
    }
    return 0;
}