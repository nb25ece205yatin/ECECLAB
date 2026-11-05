#include <iostream>
#include <stdexcept>
#include <utility>

template <typename T>
void swapVals(T& first, T& second) {
    T temporary = std::move(first);
    first = std::move(second);
    second = std::move(temporary);
}

template <typename T>
const T& findMax(const T values[], int size) {
    if (size <= 0) {
        throw std::invalid_argument("findMax requires a non-empty array");
    }

    const T* maximum = &values[0];
    for (int i = 1; i < size; ++i) {
        if (values[i] > *maximum) {
            maximum = &values[i];
        }
    }
    return *maximum;
}

int main() {
    int firstInteger = 12;
    int secondInteger = 34;
    swapVals(firstInteger, secondInteger);
    std::cout << "Integers after swap: " << firstInteger << ' '
              << secondInteger << '\n';

    double firstDouble = 2.5;
    double secondDouble = 7.75;
    swapVals(firstDouble, secondDouble);
    std::cout << "Doubles after swap: " << firstDouble << ' ' << secondDouble
              << '\n';

    const int integers[] = {4, 17, -2, 9};
    const double doubles[] = {3.14, 8.25, 1.5, 6.0};
    std::cout << "Maximum integer: " << findMax(integers, 4) << '\n';
    std::cout << "Maximum double: " << findMax(doubles, 4) << '\n';
    return 0;
}
