#include <iostream>
#include <string>
#include <utility>

class Employee {
public:
    Employee(std::string name, int id) : name_(std::move(name)), id_(id) {}
    virtual ~Employee() = default;

    virtual void display() const {
        std::cout << "Employee: " << name_ << ", ID: " << id_ << '\n';
    }

protected:
    std::string name_;
    int id_;
};

class Manager : public Employee {
public:
    Manager(std::string name, int id, int teamSize)
        : Employee(std::move(name), id), teamSize_(teamSize) {}

    void display() const override {
        std::cout << "Manager: " << name_ << ", ID: " << id_
                  << ", team size: " << teamSize_ << '\n';
    }

private:
    int teamSize_;
};

class Engineer : public Employee {
public:
    Engineer(std::string name, int id, std::string skill)
        : Employee(std::move(name), id), skill_(std::move(skill)) {}

    void display() const override {
        std::cout << "Engineer: " << name_ << ", ID: " << id_
                  << ", skill: " << skill_ << '\n';
    }

private:
    std::string skill_;
};

int main() {
    Manager manager("Avery", 101, 6);
    Engineer engineer("Morgan", 202, "embedded systems");
    Employee* employees[] = {&manager, &engineer};
    for (const Employee* employee : employees) {
        employee->display();
    }
    return 0;
}
