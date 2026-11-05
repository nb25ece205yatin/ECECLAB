#include <exception>
#include <iostream>

class StackOverflow : public std::exception {
public:
    const char* what() const noexcept override {
        return "stack is full";
    }
};

class StackUnderflow : public std::exception {
public:
    const char* what() const noexcept override {
        return "stack is empty";
    }
};

class IntStack {
public:
    static constexpr int capacity = 3;

    void push(int value) {
        if (size_ == capacity) {
            throw StackOverflow();
        }
        values_[size_++] = value;
    }

    int pop() {
        if (size_ == 0) {
            throw StackUnderflow();
        }
        return values_[--size_];
    }

private:
    int values_[capacity]{};
    int size_ = 0;
};

int main() {
    IntStack stack;
    try {
        stack.push(10);
        stack.push(20);
        stack.push(30);
        stack.push(40);
    } catch (const StackOverflow& error) {
        std::cout << "Push handled in main: " << error.what() << '\n';
    }

    try {
        while (true) {
            std::cout << "Popped " << stack.pop() << '\n';
        }
    } catch (const StackUnderflow& error) {
        std::cout << "Pop handled in main: " << error.what() << '\n';
    }
    return 0;
}
