#include <iostream>

//n

int main() {
    std::string s1;
    std::string s2;
    std::cin >> s1 >> s2;
    unsigned long long target = 1;
    for (auto &i : s1) {
        target *= i;
    }

    unsigned long long current = 1;
    bool f = false;

    unsigned long e = 0;

    for (unsigned long i = 0; i < s2.length(); ++i) {
        if (i >= s1.length()) {
            current /= s2[i - s1.length()];
        }
        current *= s2[i];
        if (current == target) {
            e = i + 1;
            f = true;
            break;
        }
    }

    std::cout << std::boolalpha << f << std::endl;
    if (f) {
        for (unsigned long i = e - s1.length(); i < e; ++i) {
            std::cout << s2[i];
        }
        std::cout << std::endl;
    }

    return 0;
}