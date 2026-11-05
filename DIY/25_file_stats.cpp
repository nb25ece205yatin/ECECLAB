#include <fstream>
#include <iostream>
#include <limits>

int main() {
    const char* filename = "DIY/nums.txt";
    {
        std::ofstream sampleFile(filename);
        if (!sampleFile) {
            std::cerr << "Could not create " << filename << ".\n";
            return 1;
        }
        sampleFile << "12 -4 0 27 -9 12\n";
        if (!sampleFile) {
            std::cerr << "Could not write sample integers to " << filename
                      << ".\n";
            return 1;
        }
    }

    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Could not open " << filename << " for reading.\n";
        return 1;
    }

    long long value;
    long long sum = 0;
    long long minimum = std::numeric_limits<long long>::max();
    long long maximum = std::numeric_limits<long long>::min();
    std::size_t count = 0;

    while (inputFile >> value) {
        ++count;
        sum += value;
        if (value < minimum) {
            minimum = value;
        }
        if (value > maximum) {
            maximum = value;
        }
    }

    if (!inputFile.eof()) {
        std::cerr << "Invalid integer data in " << filename << ".\n";
        return 1;
    }
    if (count == 0) {
        std::cout << "No integers were found in " << filename << ".\n";
        return 0;
    }

    std::cout << "File: " << filename << '\n'
              << "Count: " << count << '\n'
              << "Sum: " << sum << '\n'
              << "Minimum: " << minimum << '\n'
              << "Maximum: " << maximum << '\n';
    return 0;
}
