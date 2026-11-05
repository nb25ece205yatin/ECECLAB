#include <iostream>
#include <string>
#include <utility>

class Person {
public:
    explicit Person(std::string name) : name_(std::move(name)) {
        std::cout << "Person constructed: " << name_ << '\n';
    }

protected:
    std::string name_;
};

class Student : virtual public Person {
public:
    Student(std::string name, std::string studentId)
        : Person(std::move(name)), studentId_(std::move(studentId)) {
        std::cout << "Student constructed\n";
    }

protected:
    std::string studentId_;
};

class Employee : virtual public Person {
public:
    Employee(std::string name, std::string department)
        : Person(std::move(name)), department_(std::move(department)) {
        std::cout << "Employee constructed\n";
    }

protected:
    std::string department_;
};

class TeachingAssistant : public Student, public Employee {
public:
    TeachingAssistant(std::string name, std::string studentId, std::string department)
        : Person(name),
          Student(name, std::move(studentId)),
          Employee(std::move(name), std::move(department)) {
        std::cout << "TeachingAssistant constructed\n";
    }

    void display() const {
        std::cout << name_ << " is student " << studentId_
                  << " and works in " << department_ << ".\n";
    }
};

int main() {
    TeachingAssistant assistant("Taylor", "S-104", "Computer Science");
    assistant.display();
    return 0;
}
