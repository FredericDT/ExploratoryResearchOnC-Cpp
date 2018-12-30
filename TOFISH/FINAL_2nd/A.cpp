#include <iostream>
#include <vector>
#include <cmath>

int main() {
    int i;
    std::vector<unsigned> v;
    while (!std::cin.eof()) {
        std::cin >> i;
        if (i == -1) {
            break;
        }
        v.emplace_back(i);
    }
    int diff;
    std::cin >> diff;

    if (diff < 0) {
        std::reverse(v.begin(), v.end());
    }

    std::sort(v.begin(), v.end());
    unsigned ia = 0;
    unsigned ib = 0;

    bool f = false;

    while(ia < v.size() && ib < v.size()) {
        int c_diff = v[ib] - v[ia];
        if (c_diff == diff) {
            f = true;
            std::cout << v[ib] << "-" << v[ia] << "=" << diff << std::endl;
            ++ia;
        } else if (c_diff < diff) {
            ++ib;
        } else {
            ++ia;
        }
    }

    if (!f) {
        std::cout << std::boolalpha << f << std::endl;
    }

    return 0;
}
