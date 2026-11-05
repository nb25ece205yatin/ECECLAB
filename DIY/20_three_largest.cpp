#include <iostream>
#include <queue>

int main() {
    int count;
    std::cout << "Enter the number of integers: ";
    if (!(std::cin >> count) || count < 0) {
        std::cerr << "Invalid number of integers.\n";
        return 1;
    }

    std::priority_queue<int> largest;
    for (int i = 0; i < count; ++i) {
        int value;
        std::cout << "Enter integer " << i + 1 << ": ";
        if (!(std::cin >> value)) {
            std::cerr << "Invalid integer input.\n";
            return 1;
        }
        largest.push(value);
    }

    if (count < 3) {
        std::cout << "Fewer than three integers were entered; the available "
                     "largest values are:\n";
    } else {
        std::cout << "The three largest values are:\n";
    }

    const int resultCount = count < 3 ? count : 3;
    for (int i = 0; i < resultCount; ++i) {
        std::cout << largest.top() << '\n';
        largest.pop();
    }
    return 0;
}
