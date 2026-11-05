#include <exception>
#include <iostream>

class MathError : public std::exception {
public:
    const char* what() const noexcept override {
        return "general math error";
    }
};

class DivideByZero : public MathError {
public:
    const char* what() const noexcept override {
        return "division by zero";
    }
};

void triggerDivisionByZero() {
    throw DivideByZero();
}

int main() {
    std::cout << "Base catch first (it also catches the derived exception):\n";
    try {
        triggerDivisionByZero();
    } catch (const MathError& error) {
        std::cout << "Caught MathError: " << error.what() << '\n';
    } catch (const DivideByZero& error) {
        std::cout << "Caught DivideByZero: " << error.what() << '\n';
    }

    std::cout << "Derived catch first (specific exception is handled):\n";
    try {
        triggerDivisionByZero();
    } catch (const DivideByZero& error) {
        std::cout << "Caught DivideByZero: " << error.what() << '\n';
    } catch (const MathError& error) {
        std::cout << "Caught MathError: " << error.what() << '\n';
    }
    return 0;
}
