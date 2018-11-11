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
    int minimumDistanceTo4 = -1;
    int minimumDistanceTo6 = -1;
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

                        if (minimumDistanceTo4 >= 0) {
                            if (abs(N - 40000) < abs(minimumDistanceTo4 - 40000)) {
                                minimumDistanceTo4 = N;
                            }
                        } else {
                            minimumDistanceTo4 = N;
                        }

                        if (minimumDistanceTo6 >= 0) {
                            if (abs(N - 60000) < abs(minimumDistanceTo6 - 60000)) {
                                minimumDistanceTo6 = N;
                            }
                        } else {
                            minimumDistanceTo6 = N;
                        }

                    }
                }
            }
        }
    }
    std::cout << "output1 = " << minimumDistanceTo4 << std::endl;
    std::cout << "output2 = " << minimumDistanceTo6 << std::endl;
}