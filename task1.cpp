#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class Student {
private:
    string name;
    string usn;
    float* marks;
    int numSubjects;
    float averageMarks;
    static int studentCount;

    void calculateAverage() {
        if (numSubjects <= 0 || marks == nullptr) {
            averageMarks = 0.0f;
            return;
        }
        float sum = 0.0f;
        for (int i = 0; i < numSubjects; ++i) {
            sum += marks[i];
        }
        averageMarks = sum / numSubjects;
    }

public:
    Student() : name("Unknown"), usn("N/A"), marks(nullptr), numSubjects(0), averageMarks(0.0f) {
        ++studentCount;
    }

    Student(const string& studentName, const string& studentUsn, const float subjectMarks[], int count)
        : name(studentName), usn(studentUsn), numSubjects(count), averageMarks(0.0f) {
        if (numSubjects > 0 && subjectMarks != nullptr) {
            marks = new float[numSubjects];
            for (int i = 0; i < numSubjects; ++i) {
                marks[i] = subjectMarks[i];
            }
        } else {
            numSubjects = 0;
            marks = nullptr;
        }
        calculateAverage();
        ++studentCount;
    }

    Student(const Student& other)
        : name(other.name), usn(other.usn), numSubjects(other.numSubjects), averageMarks(other.averageMarks) {
        if (numSubjects > 0 && other.marks != nullptr) {
            marks = new float[numSubjects];
            for (int i = 0; i < numSubjects; ++i) {
                marks[i] = other.marks[i];
            }
        } else {
            marks = nullptr;
        }
        ++studentCount;
    }

    Student& operator=(const Student& other) {
        if (this != &other) {
            delete[] marks;
            name = other.name;
            usn = other.usn;
            numSubjects = other.numSubjects;
            averageMarks = other.averageMarks;
            if (numSubjects > 0 && other.marks != nullptr) {
                marks = new float[numSubjects];
                for (int i = 0; i < numSubjects; ++i) {
                    marks[i] = other.marks[i];
                }
            } else {
                marks = nullptr;
            }
        }
        return *this;
    }

    ~Student() {
        delete[] marks;
        marks = nullptr;
    }

    string getName() const { return name; }
    string getUsn() const { return usn; }
    float getAverageMarks() const { return averageMarks; }
    void setName(const string& newName) { name = newName; }

    void displayDetails() const {
        cout << fixed << setprecision(2);
        cout << "Name: " << name << " | USN: " << usn << "\n";
        cout << "Marks: ";
        for (int i = 0; i < numSubjects; ++i) {
            cout << marks[i] << (i + 1 < numSubjects ? ", " : "");
        }
        cout << "\nAverage Marks: " << averageMarks << "\n";
    }

    void displayDetails(bool showSummaryOnly) const {
        cout << fixed << setprecision(2);
        if (showSummaryOnly) {
            cout << "[" << usn << "] " << name << " -> Average Marks: " << averageMarks << "\n";
        } else {
            displayDetails();
        }
    }

    static int getStudentCount() {
        return studentCount;
    }

    bool operator>(const Student& other) const {
        return this->averageMarks > other.averageMarks;
    }

    friend void printComparisonReport(const Student& s1, const Student& s2);
};

int Student::studentCount = 0;

void printComparisonReport(const Student& s1, const Student& s2) {
    cout << fixed << setprecision(2);
    cout << "\n--- Student Marks Comparison Report ---\n";
    cout << s1.name << " (" << s1.usn << ") - Average: " << s1.averageMarks << "\n";
    cout << s2.name << " (" << s2.usn << ") - Average: " << s2.averageMarks << "\n";
    if (s1 > s2) {
        cout << "Result: " << s1.name << " scored higher average marks than " << s2.name << ".\n";
    } else if (s2 > s1) {
        cout << "Result: " << s2.name << " scored higher average marks than " << s1.name << ".\n";
    } else {
        cout << "Result: Both " << s1.name << " and " << s2.name << " have equal average marks.\n";
    }
}

int main() {
    float marks1[] = {88.5f, 92.0f, 85.5f};
    float marks2[] = {79.0f, 84.5f, 81.0f};

    Student s1("Aarav Sharma", "1NT25EC001", marks1, 3);
    Student s2("Diya Nair", "1NT25EC014", marks2, 3);

    cout << "Total Student Objects Created: " << Student::getStudentCount() << "\n\n";

    s1.displayDetails();
    cout << "\n";
    s2.displayDetails(true);

    printComparisonReport(s1, s2);

    return 0;
}
