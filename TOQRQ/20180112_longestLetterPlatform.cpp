#include <iostream>
#include <string>

using namespace std;

/*
 * This program is intend to solve the problem
 * input a string containing letters
 *
 * return an integer which is the longest length of a successive CAPTIAL or lower letter sequence
 *
 */
int main() {
    string input;
    std::cin >> input;
    int max = 0;
    int current = 0;
    int state = 0;
    for (int i = 0; i < input.length(); ++i) {
        if (!i) {
            //initialize
            state = input[i] - 'a' + 1;
            ++current;
        } else {
            if ((input[i] - 'a' + 1) * state > 0) {
                ++current;
            } else {
                max = max < current ? current : max;
                current = 1;
                state = input[i] - 'a' + 1;
            }
        }
    }
    max = max < current ? current : max;
    std::cout << max << std::endl;
    return 0;
}
