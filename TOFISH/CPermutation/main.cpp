/**
 * 从键盘输入一个5位正整数，首先分离出该正整数中的每一位数字，
 * 然后用分离出的每位数字组成一个最接近40000的数和一个最接近60000的数。
 * 要求检查输入数据的合法性
 */
#include <iostream>
#include <cmath>

int main() {
    int n;
    std::cout << "input: ";
    std::cin >> n;
    std::cout << n << std::endl;

    if (n < 10000 || n >= 100000) {
        std::cout << "Input Error!" << std::endl;
        return 1;
    }

    int p[] = {0, 0, 0, 0, 0};
    int t = n;
    for (int i = 0; i < 5; ++i) {
        p[i] = t % 10;
        t /= 10;
    }
    int N;
    int minimumDistantValueTo4 = -1;
    int minimumDistantValueTo6 = -1;
    for (int A = 0; A < 5; ++A) {
        for (int B = 0; B < 5; ++B) {
            if (B == A) {
                continue;
            }
            for (int C = 0; C < 5; ++C) {
                if (C == A || C == B) {
                    continue;
                }
                for (int D = 0; D < 5; ++D) {
                    if (A == D || B == D || C == D) {
                        continue;
                    }
                    for (int E = 0; E < 5; ++E) {
                        if (A == E || B == E || C == E || D == E) {
                            continue;
                        }
                        N = 10000 * p[A] + 1000 * p[B] + 100 * p[C] + 10 * p[D] + p[E];

                        if (minimumDistantValueTo4 >= 0) {
                            if (abs(N - 40000) < abs(minimumDistantValueTo4 - 40000)) {
                                minimumDistantValueTo4 = N;
                            }
                        } else {
                            minimumDistantValueTo4 = N;
                        }

                        if (minimumDistantValueTo6 >= 0) {
                            if (abs(N - 60000) < abs(minimumDistantValueTo6 - 60000)) {
                                minimumDistantValueTo6 = N;
                            }
                        } else {
                            minimumDistantValueTo6 = N;
                        }

                    }
                }
            }
        }
    }
    std::cout << "output1 = " << minimumDistantValueTo4 << std::endl;
    std::cout << "output2 = " << minimumDistantValueTo6 << std::endl;
}