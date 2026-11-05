#include <exception>
#include <iostream>
#include <limits>
#include <string>

class InsufficientFunds : public std::exception {
public:
    const char* what() const noexcept override {
        return "withdrawal exceeds the available balance";
    }
};

class BankAccount {
public:
    explicit BankAccount(double initialBalance) : balance_(initialBalance) {}

    void withdraw(double amount) {
        if (amount > balance_) {
            throw InsufficientFunds();
        }
        balance_ -= amount;
    }

    double balance() const {
        return balance_;
    }

private:
    double balance_;
};

bool readNonnegativeAmount(const std::string& prompt, double& amount) {
    std::cout << prompt;
    if (!(std::cin >> amount) || amount < 0.0) {
        return false;
    }
    return true;
}

int main() {
    double initialBalance = 0.0;
    double withdrawal = 0.0;
    if (!readNonnegativeAmount("Enter the initial balance: ", initialBalance) ||
        !readNonnegativeAmount("Enter the withdrawal amount: ", withdrawal)) {
        std::cerr << "Please enter valid nonnegative amounts.\n";
        return 1;
    }

    BankAccount account(initialBalance);
    try {
        account.withdraw(withdrawal);
        std::cout << "Withdrawal successful. Remaining balance: "
                  << account.balance() << '\n';
    } catch (const InsufficientFunds& error) {
        std::cout << "Transaction declined: " << error.what() << ". Balance: "
                  << account.balance() << '\n';
    }
    return 0;
}
