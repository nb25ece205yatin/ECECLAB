#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

using namespace std;

class InvalidMarksException : public invalid_argument {
public:
    explicit InvalidMarksException(const string& msg) : invalid_argument(msg) {}
};

class Student {
protected:
    string name;
    string usn;

public:
    Student() : name("Unknown"), usn("N/A") {}
    Student(const string& studentName, const string& studentUsn) : name(studentName), usn(studentUsn) {}
    virtual ~Student() = default;

    string getName() const { return name; }
    string getUsn() const { return usn; }

    virtual void displayDetails() const {
        cout << "Name: " << name << " | USN: " << usn << "\n";
    }
};

class Result : public Student {
private:
    vector<float> marks;
    float totalMarks;
    float percentage;
    string grade;

    void validateMarks() {
        if (marks.empty()) {
            throw InvalidMarksException("Marks list cannot be empty.");
        }
        for (float m : marks) {
            if (m < 0.0f || m > 100.0f) {
                throw InvalidMarksException("Invalid mark (" + to_string(m) + "). Marks must be between 0 and 100.");
            }
        }
    }

    void computeResult() {
        validateMarks();
        totalMarks = 0.0f;
        for (float m : marks) {
            totalMarks += m;
        }
        percentage = totalMarks / static_cast<float>(marks.size());
        if (percentage >= 85.0f) {
            grade = "Distinction";
        } else if (percentage >= 60.0f) {
            grade = "First Class";
        } else if (percentage >= 40.0f) {
            grade = "Pass";
        } else {
            grade = "Fail";
        }
    }

public:
    Result() : Student(), totalMarks(0.0f), percentage(0.0f), grade("N/A") {}

    Result(const string& studentName, const string& studentUsn, const vector<float>& subjectMarks)
        : Student(studentName, studentUsn), marks(subjectMarks), totalMarks(0.0f), percentage(0.0f), grade("N/A") {
        computeResult();
    }

    float getTotalMarks() const { return totalMarks; }
    float getPercentage() const { return percentage; }
    string getGrade() const { return grade; }
    const vector<float>& getMarks() const { return marks; }

    void displayDetails() const override {
        cout << fixed << setprecision(2);
        cout << "USN: " << usn << " | Name: " << name << "\n";
        cout << "Marks: ";
        for (size_t i = 0; i < marks.size(); ++i) {
            cout << marks[i] << (i + 1 < marks.size() ? ", " : "");
        }
        cout << "\nTotal Marks: " << totalMarks << " / " << (marks.size() * 100.0f)
             << " | Percentage: " << percentage << "% | Result: " << grade << "\n";
    }

    string toFileRecord() const {
        ostringstream oss;
        oss << name << "|" << usn << "|" << marks.size();
        for (float m : marks) {
            oss << "|" << m;
        }
        return oss.str();
    }

    static Result fromFileRecord(const string& line) {
        stringstream ss(line);
        string sName, sUsn, token;
        if (!getline(ss, sName, '|') || !getline(ss, sUsn, '|') || !getline(ss, token, '|')) {
            throw runtime_error("Malformed record in file: " + line);
        }
        int count = stoi(token);
        vector<float> loadedMarks;
        for (int i = 0; i < count; ++i) {
            if (!getline(ss, token, '|')) {
                throw runtime_error("Incomplete marks in record: " + line);
            }
            loadedMarks.push_back(stof(token));
        }
        return Result(sName, sUsn, loadedMarks);
    }
};

void saveRecordsToFile(const string& filename, const vector<Result>& records) {
    ofstream outFile(filename);
    if (!outFile) {
        throw runtime_error("Unable to open file for writing: " + filename);
    }
    for (const auto& r : records) {
        outFile << r.toFileRecord() << "\n";
    }
    outFile.close();
}

vector<Result> loadRecordsFromFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        throw runtime_error("Unable to open file for reading: " + filename);
    }
    vector<Result> loaded;
    string line;
    while (getline(inFile, line)) {
        if (!line.empty()) {
            loaded.push_back(Result::fromFileRecord(line));
        }
    }
    inFile.close();
    return loaded;
}

int main() {
    vector<Result> records;
    const string filename = "student_results.txt";

    vector<pair<string, vector<pair<string, vector<float>>>>> testCases = {
        {"Aarav Sharma", {{"1NT25EC001", {88.0f, 91.5f, 86.5f}}}},
        {"Diya Nair", {{"1NT25EC014", {76.0f, 82.0f, 79.0f}}}},
        {"Rohan Kulkarni", {{"1NT25EC028", {94.0f, 89.0f, 92.5f}}}}
    };

    for (const auto& entry : testCases) {
        try {
            records.emplace_back(entry.first, entry.second[0].first, entry.second[0].second);
        } catch (const InvalidMarksException& e) {
            cout << "Validation Error for " << entry.first << ": " << e.what() << "\n";
        }
    }

    try {
        Result invalidStudent("Invalid Entry", "1NT25EC099", {85.0f, 105.0f, 70.0f});
        records.push_back(invalidStudent);
    } catch (const InvalidMarksException& e) {
        cout << "\nException Caught: " << e.what() << "\n";
    }

    try {
        saveRecordsToFile(filename, records);
        cout << "\nSaved " << records.size() << " student records to '" << filename << "'.\n";
    } catch (const exception& e) {
        cout << "File Write Error: " << e.what() << "\n";
    }

    vector<Result> retrievedRecords;
    try {
        retrievedRecords = loadRecordsFromFile(filename);
        cout << "Retrieved " << retrievedRecords.size() << " records from '" << filename << "'.\n\n";
    } catch (const exception& e) {
        cout << "File Read Error: " << e.what() << "\n";
    }

    cout << "=== All Student Results (Polymorphic Display) ===\n";
    for (const auto& rec : retrievedRecords) {
        const Student* basePtr = &rec;
        basePtr->displayDetails();
        cout << "----------------------------------------\n";
    }

    float cutoffMarks = 255.0f;
    int aboveCutoffCount = count_if(
        retrievedRecords.begin(),
        retrievedRecords.end(),
        [cutoffMarks](const Result& r) { return r.getTotalMarks() > cutoffMarks; }
    );

    cout << "\nStudents scoring above " << fixed << setprecision(2) << cutoffMarks
         << " total marks (" << aboveCutoffCount << " found):\n";
    for_each(
        retrievedRecords.begin(),
        retrievedRecords.end(),
        [cutoffMarks](const Result& r) {
            if (r.getTotalMarks() > cutoffMarks) {
                cout << " - " << r.getName() << " (" << r.getUsn() << ") | Total: "
                     << r.getTotalMarks() << " | Grade: " << r.getGrade() << "\n";
            }
        }
    );

    return 0;
}
