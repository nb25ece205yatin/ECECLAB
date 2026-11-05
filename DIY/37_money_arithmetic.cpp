#include <cstdint>
#include <iostream>
#include <iomanip>

class Money {
public:
    Money(std::int64_t rupees, int paise)
        : totalPaise_(rupees * 100 + paise) {}

    Money operator+(const Money& other) const {
        return fromTotalPaise(totalPaise_ + other.totalPaise_);
    }

    Money operator-(const Money& other) const {
        return fromTotalPaise(totalPaise_ - other.totalPaise_);
    }

    void print() const {
        const bool negative = totalPaise_ < 0;
        const std::uint64_t magnitude = negative
            ? static_cast<std::uint64_t>(-(totalPaise_ + 1)) + 1
            : static_cast<std::uint64_t>(totalPaise_);
        if (negative) {
            std::cout << '-';
        }
        std::cout << "Rs. " << magnitude / 100 << '.'
                  << std::setw(2) << std::setfill('0') << magnitude % 100
                  << std::setfill(' ') << '\n';
    }

private:
    explicit Money(std::int64_t totalPaise) : totalPaise_(totalPaise) {}

    static Money fromTotalPaise(std::int64_t totalPaise) {
        return Money(totalPaise);
    }

    std::int64_t totalPaise_;
};

bool readMoney(const char* label, Money& money) {
    std::int64_t rupees = 0;
    int paise = 0;
    std::cout << "Enter " << label << " rupees and paise: ";
    if (!(std::cin >> rupees >> paise) || rupees < 0 ||
        rupees > 1000000000 || paise < 0 || paise >= 100) {
        return false;
    }
    money = Money(rupees, paise);
    return true;
}

int main() {
    Money first(0, 0);
    Money second(0, 0);
    if (!readMoney("first amount", first) || !readMoney("second amount", second)) {
        std::cerr << "Enter rupees from 0 to 1000000000 and paise from 0 to 99.\n";
        return 1;
    }

    std::cout << "Sum: ";
    (first + second).print();
    std::cout << "Difference (first minus second): ";
    (first - second).print();
    return 0;
}
