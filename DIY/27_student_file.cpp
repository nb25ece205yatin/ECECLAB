#include <array>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

struct Student {
    std::string name;
    int marks;
};

int main() {
    const char* filename = "DIY/students.txt";
    const std::array<Student, 5> sampleStudents = {{
        {"Maya Patel", 88},
        {"Leo Chen", 95},
        {"Ava Johnson", 91},
        {"Noah Singh", 79},
        {"Zoe Martin", 95}
    }};

    {
        std::ofstream outputFile(filename);
        if (!outputFile) {
            std::cerr << "Could not create " << filename << ".\n";
            return 1;
        }
        for (const Student& student : sampleStudents) {
            outputFile << student.name << '|' << student.marks << '\n';
        }
        if (!outputFile) {
            std::cerr << "Could not write student records to " << filename
                      << ".\n";
            return 1;
        }
    }

    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Could not open " << filename << " for reading.\n";
        return 1;
    }

    std::array<Student, 5> students;
    std::size_t count = 0;
    std::string line;
    while (std::getline(inputFile, line)) {
        if (count == students.size()) {
            std::cerr << "The file contains more student records than the "
                         "array can hold.\n";
            return 1;
        }

        const std::size_t separator = line.rfind('|');
        if (separator == std::string::npos || separator == 0 ||
            separator + 1 >= line.size()) {
            std::cerr << "Invalid student record in " << filename << ".\n";
            return 1;
        }

        const std::string marksText = line.substr(separator + 1);
        std::size_t parsedCharacters = 0;
        int marks;
        try {
            marks = std::stoi(marksText, &parsedCharacters);
        } catch (const std::exception&) {
            std::cerr << "Invalid marks in " << filename << ".\n";
            return 1;
        }
        if (parsedCharacters != marksText.size() || marks < 0 || marks > 100) {
            std::cerr << "Marks must be a whole number from 0 to 100.\n";
            return 1;
        }

        students[count++] = {line.substr(0, separator), marks};
    }

    if (!inputFile.eof()) {
        std::cerr << "Could not read " << filename << " completely.\n";
        return 1;
    }
    if (count == 0) {
        std::cout << "No student records were found.\n";
        return 0;
    }

    std::size_t topperIndex = 0;
    std::cout << "Student records:\n";
    for (std::size_t i = 0; i < count; ++i) {
        std::cout << students[i].name << ": " << students[i].marks << '\n';
        if (students[i].marks > students[topperIndex].marks) {
            topperIndex = i;
        }
    }
    std::cout << "Topper: " << students[topperIndex].name << " with "
              << students[topperIndex].marks << " marks\n";
    return 0;
}
