#include <iostream>

class Account {
public:
    explicit Account(double balance) : balance_(balance) {}
    virtual ~Account() = default;
    virtual double calculateInterest() const = 0;

protected:
    double balance_;
};

class SavingsAccount : public Account {
public:
    using Account::Account;

    double calculateInterest() const override {
        return balance_ * 0.04;
    }
};

class CurrentAccount : public Account {
public:
    using Account::Account;

    double calculateInterest() const override {
        return balance_ * 0.02;
    }
};

int main() {
    double savingsBalance = 0.0;
    double currentBalance = 0.0;
    std::cout << "Enter savings and current account balances: ";
    if (!(std::cin >> savingsBalance >> currentBalance) ||
        savingsBalance < 0.0 || currentBalance < 0.0) {
        std::cerr << "Please enter valid nonnegative balances.\n";
        return 1;
    }

    SavingsAccount savings(savingsBalance);
    CurrentAccount current(currentBalance);
    Account* accounts[] = {&savings, &current};
    const char* names[] = {"Savings", "Current"};
    for (int i = 0; i < 2; ++i) {
        std::cout << names[i] << " account interest: "
                  << accounts[i]->calculateInterest() << '\n';
    }
    return 0;
}
