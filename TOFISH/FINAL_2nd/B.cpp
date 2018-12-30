#include <iostream>
#include <vector>

int n;
int *a;

std::vector<int> sa{};
std::vector<int> sb{};

bool r(int diff, int i) {

    if (i >= n) {
        return diff == 0;
    }

    int ci = i++;
    bool p = r(diff + a[ci], i);

    if (p) {
        sa.emplace_back(a[ci]);
        return true;
    }

    bool m = r(diff - a[ci], i);

    if (m) {
        sb.emplace_back(a[ci]);
        return true;
    }

    return false;
}

int main() {
    std::cin >> n;
    int arr[n];

    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    a = arr;
    if (!r(0, 0)) {
        std::cout << std::boolalpha << false << std::endl;
        return 0;
    }

    std::cout << std::boolalpha << true << std::endl;
    for (auto &i : sa) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    for (auto &i : sb) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}