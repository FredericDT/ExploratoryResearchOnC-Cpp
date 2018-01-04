#include <iostream>
#include <string>

using namespace std;

int main() {
    string input = "";
    getline(std::cin, input);
    int thief[100] = {0};
    for (int i = 0; i < input.length(); ++i) {
        if (input[i] >= '0' && input[i] <= '9') {
            int pre = i - 1;
            int after = i + 1;
            int strength = input[i] - '0';
            while (strength--) {
                if (pre >= 0) {
                    if (input[pre] == 'X') {
                        thief[pre] = 1;
                    }
                }
                if (after < input.length()) {
                    if (input[after] == 'X') {
                        thief[after] = 1;
                    }
                }
                --pre;
                ++after;
            }
        }
    }
    int sum = 0;
    for (int i = 0; i < input.length(); ++i) {
        sum += thief[i];
    }
    std::cout << sum << std::endl;
    return 0;
}
