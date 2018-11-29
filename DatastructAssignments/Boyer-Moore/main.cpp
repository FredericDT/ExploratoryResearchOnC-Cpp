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

    long indexOf(std::string const &source, std::string const &pattern, long startIndex) {
        for (long i = startIndex; i < source.length(); ++i) {
            long ii = i;
            long j = 0;
            while(j < pattern.length() && pattern[j] == source[ii]) {
                ++j;
                ++ii;
            }
            if (j >= pattern.length()) {
                return i;
            }
        }
        return -1;
    }

    std::vector<long> getAllIndexsOf(std::string const &source, std::string const &pattern) {
        long i = -pattern.length();
        i = indexOf(source, pattern, i + pattern.length());
        std::vector<long> v{};
        while(i >= 0) {
            v.push_back(i);
            i = indexOf(source, pattern, i + pattern.length());
        }
        return v;
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

        // horspool
        long getBadPatternIndex(long index, char target) {
            if (index > 0) {
                std::map<char, long> m = this->badCharacterMaps[index - 1];
                return m.find(target) == m.end() ? -1 : m[target];
            }
            return -1;
        }

        bool (*eqf)(char s, char p);

        long *goodEquals;

        void parseGoodSuffix() {
            for (long i = 1; i < pattern.length(); ++i) {
                for (long j = 0; j < i; ++j) {
                    long ii = i;
                    long jj = j;
                    while (ii < pattern.length() && pattern[ii] == pattern[jj]) {
                        ++ii;
                        ++jj;
                    }
                    if (ii >= pattern.length()) {
                        goodEquals[i - 1] = j + pattern.length();
                    } else {
                        goodEquals[i - 1] = -1;
                    }
                }
            }
            for (long k = 0; k < pattern.length(); ++k) {
                if (goodEquals[k] < 0) {
                    for (long i = k + 1; i < pattern.length(); ++i) {
                        if (goodEquals[i] >= 0) {
                            goodEquals[k] = goodEquals[i];
                            break;
                        }
                    }
                }
            }
        }

    public:
        BoyerMoorePattern(std::string const &pattern, bool (*equalsFunction)(char s, char p))
                : badCharacterMaps{}, eqf(equalsFunction) {
            this->pattern = std::string(pattern);
            this->goodEquals = new long[pattern.length()];
            this->initBadCharacterMap();
            this->parseGoodSuffix();
        }

        ~BoyerMoorePattern() = default;

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

                long badPatternIndex = getBadPatternIndex(currentPatternIndex, source[currentSourceIndex]);
                long moveTo = startIndex + currentPatternIndex - badPatternIndex;

                if (currentPatternIndex + 1 == pattern.length()) {
                    startIndex = moveTo;
                    continue;
                }

                long goodMoveTo = startIndex + pattern.length() - 1 - goodEquals[currentPatternIndex];

                moveTo = moveTo > goodMoveTo ? moveTo : goodMoveTo;
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

    std::string read_file_to_string(std::string const &path) {
        std::ifstream inFile;
        inFile.open(path);
        std::stringstream stringStream;
        stringStream << inFile.rdbuf();
        std::string s = stringStream.str();
        inFile.close();
        return s;
    }
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
    std::string s(fdt::read_file_to_string(argv[1]));
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