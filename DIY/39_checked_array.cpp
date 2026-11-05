#include <cstddef>
#include <iostream>
#include <memory>
#include <stdexcept>

class CheckedArray {
public:
    explicit CheckedArray(std::size_t size)
        : size_(size), values_(std::make_unique<int[]>(size)) {}

    std::size_t size() const {
        return size_;
    }

    int& operator[](std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("array index is outside the valid range");
        }
        return values_[index];
    }

    const int& operator[](std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("array index is outside the valid range");
        }
        return values_[index];
    }

private:
    std::size_t size_;
    std::unique_ptr<int[]> values_;
};

int main() {
    constexpr std::size_t capacity = 5;
    CheckedArray values(capacity);
    for (std::size_t index = 0; index < values.size(); ++index) {
        values[index] = static_cast<int>((index + 1) * 10);
    }

    std::cout << "Array values:";
    for (std::size_t index = 0; index < values.size(); ++index) {
        std::cout << ' ' << values[index];
    }
    std::cout << '\n';

    std::size_t index = 0;
    std::cout << "Enter an index from 0 to " << capacity - 1 << ": ";
    if (!(std::cin >> index)) {
        std::cerr << "Please enter a valid nonnegative index.\n";
        return 1;
    }
    try {
        std::cout << "Value: " << values[index] << '\n';
    } catch (const std::out_of_range& error) {
        std::cout << "Bounds exception: " << error.what() << '\n';
    }
    return 0;
}
