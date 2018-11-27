#include<iostream>

int josephus_r(int n, int t) {
    if (n == 1) {
        return 0;
    }
    return (josephus_r(n - 1, t) + t) % n;
}

int josephus(int n, int t) {
    int i = 0;
    for (int j = 2; j <= n; ++j) {
        i = (i + t) % j;
    }
    return i;
}

int main() {
    std::cout << josephus(40,3) << std::endl << josephus_r(40, 3) << std::endl;
}