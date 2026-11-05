#include <deque>
#include <iostream>
#include <stdexcept>
#include <string>

template <typename T>
class Queue {
public:
    void enqueue(const T& value) {
        values_.push_back(value);
    }

    T dequeue() {
        if (values_.empty()) {
            throw std::out_of_range("cannot dequeue from an empty queue");
        }
        T value = values_.front();
        values_.pop_front();
        return value;
    }

    T& front() {
        if (values_.empty()) {
            throw std::out_of_range("cannot access the front of an empty queue");
        }
        return values_.front();
    }

    const T& front() const {
        if (values_.empty()) {
            throw std::out_of_range("cannot access the front of an empty queue");
        }
        return values_.front();
    }

    bool empty() const {
        return values_.empty();
    }

private:
    std::deque<T> values_;
};

int main() {
    Queue<std::string> names;
    names.enqueue("Ava");
    names.enqueue("Noah");

    std::cout << "Queue front: " << names.front() << '\n';
    std::cout << "Dequeued: " << names.dequeue() << '\n';
    std::cout << "Queue front after dequeue: " << names.front() << '\n';
    std::cout << "Dequeued: " << names.dequeue() << '\n';

    try {
        std::cout << names.front() << '\n';
    } catch (const std::out_of_range& error) {
        std::cout << "Front operation: " << error.what() << '\n';
    }

    try {
        names.dequeue();
    } catch (const std::out_of_range& error) {
        std::cout << "Dequeue operation: " << error.what() << '\n';
    }
    return 0;
}
