#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<unsigned> pool{0, 1, 3, 5};
    while (next_permutation(pool.begin(), pool.end())) {
        if (pool[0] == 0) {
            continue;
        }
        if (pool[0] * 10 + pool[1] == 2 * (pool[2] * 10 + pool[3])) {
            std::cout << "rabbit foot: " << pool[0] << pool[1] << "4" << std::endl << "chicken foot: " << pool[2]
                      << pool[3] << "2" << std::endl <<
                      "count of each: " << (pool[0] * 100 + pool[1] * 10 + 4) / 4 << std::endl;
        }
    }
    return 0;
}