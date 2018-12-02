#include <iostream>
#include <unordered_set>

bool i(unsigned x) {
    std::unordered_set<unsigned> s{};
    do {
        s.insert(x);
        unsigned sum = 0;
        std::string str = std::to_string(x);
        for (char c : str) {
            unsigned v = c - '0';
            sum += v * v;
        }
        if (sum == 1) {
            return true;
        }
        x = sum;
    } while (s.find(x) == s.end());
    return false;
}

int main() {
    while (!std::cin.eof()) {
        std::cout << "input: ";
        unsigned in;
        std::cin >> in;
        bool ir = i(in);
        std::cout << ", output: " << ir << std::endl;
    }
    return 0;
}