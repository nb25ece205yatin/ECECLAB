#include <fstream>
#include <iostream>
#include <string>

int main() {
    const char* inputName = "DIY/in.txt";
    const char* outputName = "DIY/out.txt";

    {
        std::ofstream sampleFile(inputName);
        if (!sampleFile) {
            std::cerr << "Could not create " << inputName << ".\n";
            return 1;
        }
        sampleFile << "First sample line\n"
                   << "Second sample line\n"
                   << "A third line with spaces\n";
        if (!sampleFile) {
            std::cerr << "Could not write sample lines to " << inputName
                      << ".\n";
            return 1;
        }
    }

    std::ifstream inputFile(inputName);
    if (!inputFile) {
        std::cerr << "Could not open " << inputName << " for reading.\n";
        return 1;
    }
    std::ofstream outputFile(outputName);
    if (!outputFile) {
        std::cerr << "Could not create " << outputName << ".\n";
        return 1;
    }

    std::string line;
    std::size_t lineNumber = 0;
    while (std::getline(inputFile, line)) {
        outputFile << ++lineNumber << ". " << line << '\n';
        if (!outputFile) {
            std::cerr << "Could not write to " << outputName << ".\n";
            return 1;
        }
    }

    if (!inputFile.eof()) {
        std::cerr << "Could not read " << inputName << " completely.\n";
        return 1;
    }
    outputFile.close();
    if (!outputFile) {
        std::cerr << "Could not finish writing " << outputName << ".\n";
        return 1;
    }

    std::cout << "Numbered " << lineNumber << " lines from " << inputName
              << " into " << outputName << ".\n";
    return 0;
}
