#include <iostream>
#include <numeric>
#include <vector>

int main() {
    int count;
    std::cout << "Enter the number of integers: ";
    if (!(std::cin >> count) || count < 0) {
        std::cerr << "Invalid number of integers.\n";
        return 1;
    }

    std::vector<int> values;
    values.reserve(static_cast<std::size_t>(count));
    for (int i = 0; i < count; ++i) {
        int value;
        std::cout << "Enter integer " << i + 1 << ": ";
        if (!(std::cin >> value)) {
            std::cerr << "Invalid integer input.\n";
            return 1;
        }
        values.push_back(value);
    }

    const long long evenSum = std::accumulate(
        values.begin(), values.end(), 0LL,
        [](long long sum, int value) {
            return value % 2 == 0 ? sum + value : sum;
        });

    std::cout << "Sum of even integers: " << evenSum << '\n';
    return 0;
}
