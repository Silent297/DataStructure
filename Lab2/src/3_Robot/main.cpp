#include <iostream>
#include <vector>

#include "walk.h"

int main() {
    int steps, n;
    while (std::cin >> steps >> n) {
        if (steps < 0 || n < 0 || n > 500)
            return 1;

        std::vector<int> gold(2 * n);
        std::vector<int> value(n);
        for (int i = 0; i < n; ++i) {
            if (!(std::cin >> gold[2 * i] >> gold[2 * i + 1] >> value[i]))
                return 1;
        }

        DATA_STRUCTURE::walk problem(steps, n, gold.data(), value.data());
        std::cout << problem.get_value() << std::endl;
    }
    return 0;
}
