#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

class Logger {
public:
    virtual ~Logger() = default;
    virtual void write(const std::string& message) = 0;
};

class ConsoleLogger : public Logger {
public:
    void write(const std::string& message) override {
        std::cout << "Log: " << message << '\n';
    }
};

class FileLogger : public Logger {
public:
    explicit FileLogger(const std::string& path) : output_(path) {}

    bool isOpen() const {
        return output_.is_open();
    }

    void write(const std::string& message) override {
        output_ << "Log: " << message << '\n';
    }

private:
    std::ofstream output_;
};

int main() {
    int choice = 0;
    std::cout << "Choose logger (1 = console, 2 = file): ";
    if (!(std::cin >> choice) || (choice != 1 && choice != 2)) {
        std::cerr << "Please choose 1 or 2.\n";
        return 1;
    }

    std::cin.ignore(10000, '\n');
    std::string message;
    std::cout << "Enter a log message: ";
    if (!std::getline(std::cin, message) || message.empty()) {
        std::cerr << "The log message cannot be empty.\n";
        return 1;
    }

    std::unique_ptr<Logger> logger;
    if (choice == 1) {
        logger = std::make_unique<ConsoleLogger>();
    } else {
        const std::string path = "DIY/logger_output.txt";
        auto fileLogger = std::make_unique<FileLogger>(path);
        if (!fileLogger->isOpen()) {
            std::cerr << "Could not open " << path << ". Run from the project root.\n";
            return 1;
        }
        logger = std::move(fileLogger);
        std::cout << "Writing to " << path << '\n';
    }

    logger->write(message);
    return 0;
}
