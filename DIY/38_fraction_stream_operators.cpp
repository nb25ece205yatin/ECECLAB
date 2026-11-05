#include <iostream>
#include <numeric>

class Fraction {
public:
    Fraction() = default;

    friend std::istream& operator>>(std::istream& input, Fraction& fraction) {
        long long numerator = 0;
        long long denominator = 0;
        if (!(input >> numerator >> denominator)) {
            return input;
        }
        if (denominator == 0 || numerator < -1000000000LL ||
            numerator > 1000000000LL || denominator < -1000000000LL ||
            denominator > 1000000000LL) {
            input.setstate(std::ios::failbit);
            return input;
        }
        fraction.set(numerator, denominator);
        return input;
    }

    friend std::ostream& operator<<(std::ostream& output, const Fraction& fraction) {
        return output << fraction.numerator_ << '/' << fraction.denominator_;
    }

private:
    void set(long long numerator, long long denominator) {
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
        const long long divisor = std::gcd(numerator, denominator);
        numerator_ = numerator / divisor;
        denominator_ = denominator / divisor;
    }

    long long numerator_ = 0;
    long long denominator_ = 1;
};

int main() {
    Fraction fraction;
    std::cout << "Enter a numerator and denominator separated by a space: ";
    if (!(std::cin >> fraction)) {
        std::cerr << "Enter integers in range +/-1000000000 and a nonzero denominator.\n";
        return 1;
    }
    std::cout << "Simplified fraction: " << fraction << '\n';
    return 0;
}
