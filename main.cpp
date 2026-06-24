#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

class BankAccount {
private:
    int accountNumber;
    std::string accountHolderName;
    double balance;

public:
    // constructor
    BankAccount(int accNum, std::string name, double initialBalance) {
        accountNumber = accNum;
        accountHolderName = name;
        balance = initialBalance;
    }

    // getters
    int getAccountNumber() const { return accountNumber; }
    std::string getAccountHolderName() const { return accountHolderName; }
    double getBalance() const { return balance; }

    // deposit money
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "\n Success: $" << amount << " deposited successfully!\n";
        } else {
            std::cout << "\n Error: Invalid deposit amount.\n";
        }
    }

    // withdraw money
    bool withdraw(double amount) {
        if (amount > balance) {
            std::cout << "\n Error: Insufficient balance!\n";
            return false;
        } else if (amount <= 0) {
            std::cout << "\n Error: Invalid withdrawal amount.\n";
            return false;
        } else {
            balance -= amount;
            std::cout << "\n Success: $" << amount << " withdrawn successfully!\n";
            return true;
        }
    }

    // Display Account Details
    void displayAccount() const {
        std::cout << "\n-----------------------------------";
        std::cout << "\n Account Number : " << accountNumber;
        std::cout << "\n Account Holder : " << accountHolderName;
        std::cout << "\n Current Balance: $" << std::fixed << std::setprecision(2) << balance;
        std::cout << "\n-----------------------------------\n";
    }
};

// Helper function to find an account by its number
BankAccount* findAccount(std::vector<BankAccount>& accounts, int accNum) {
    for (auto& acc : accounts) {
        if (acc.getAccountNumber() == accNum) {
            return &acc;
        }
    }
    return nullptr;
}

int main() {
    std::vector<BankAccount> accounts;
    int choice;

    // Dummy data to start with
    accounts.push_back(BankAccount(1001, "Alice Smith", 500.0));
    accounts.push_back(BankAccount(1002, "Bob Jones", 1200.50));

    do {
        std::cout << "\n===== BANK MANAGEMENT SYSTEM =====";
        std::cout << "\n 1. Create New Account";
        std::cout << "\n 2. Deposit Money";
        std::cout << "\n 3. Withdraw Money";
        std::cout << "\n 4. Check Balance / Account Info";
        std::cout << "\n 5. Display All Accounts";
        std::cout << "\n 6. Exit";
        std::cout << "\n==================================";
        std::cout << "\n Enter your choice (1-6): ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int accNum;
                std::string name;
                double initialDeposit;

                std::cout << "\nEnter unique Account Number: ";
                std::cin >> accNum;

                // Check if account number already exists
                if (findAccount(accounts, accNum) != nullptr) {
                    std::cout << "\n Error: Account number already exists!\n";
                    break;
                }

                std::cout << "Enter Account Holder Name: ";
                std::cin.ignore(); // Clear input buffer
                std::getline(std::cin, name);
                std::cout << "Enter Initial Deposit: $";
                std::cin >> initialDeposit;

                accounts.push_back(BankAccount(accNum, name, initialDeposit));
                std::cout << "\n Success: Account created successfully!\n";
                break;
            }
            case 2: {
                int accNum;
                double amount;
                std::cout << "\nEnter Account Number: ";
                std::cin >> accNum;

                BankAccount* acc = findAccount(accounts, accNum);
                if (acc != nullptr) {
                    std::cout << "Enter amount to deposit: $";
                    std::cin >> amount;
                    acc->deposit(amount);
                } else {
                    std::cout << "\n Error: Account not found.\n";
                }
                break;
            }
            case 3: {
                int accNum;
                double amount;
                std::cout << "\nEnter Account Number: ";
                std::cin >> accNum;

                BankAccount* acc = findAccount(accounts, accNum);
                if (acc != nullptr) {
                    std::cout << "Enter amount to withdraw: $";
                    std::cin >> amount;
                    acc->withdraw(amount);
                } else {
                    std::cout << "\n Error: Account not found.\n";
                }
                break;
            }
            case 4: {
                int accNum;
                std::cout << "\nEnter Account Number: ";
                std::cin >> accNum;

                BankAccount* acc = findAccount(accounts, accNum);
                if (acc != nullptr) {
                    acc->displayAccount();
                } else {
                    std::cout << "\n Error: Account not found.\n";
                }
                break;
            }
            case 5: {
                if (accounts.empty()) {
                    std::cout << "\n No accounts registered yet.\n";
                } else {
                    std::cout << "\n======= ALL REGISTERED ACCOUNTS =======";
                    for (const auto& acc : accounts) {
                        acc.displayAccount();
                    }
                }
                break;
            }
            case 6:
                std::cout << "\n Thank you for using our Banking System. Goodbye!\n";
                break;
            default:
                std::cout << "\n Invalid choice! Please enter a number between 1 and 6.\n";
        }
    } while (choice != 6);

    return 0;
}
