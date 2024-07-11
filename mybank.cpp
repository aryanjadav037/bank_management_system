#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

// Account
class Account
{
private:
    string accountNumber;
    string pin;
    double balance;
    string holderName;
    string holderAddress;
    string holderPhone;
    string holderEmail;
    vector<string> transactionHistory;

    string generatePin()
    {
        return to_string(1000 + rand() % 9000); // Generate a 4-digit PIN
    }

public:
    Account(const string &accNum, const string &name, const string &address,
            const string &phone, const string &email)
        : accountNumber(accNum), holderName(name), holderAddress(address),
          holderPhone(phone), holderEmail(email), balance(0.0)
    {
        pin = generatePin();
    }

    string getAccountNumber() const { return accountNumber; }
    string getPin() const { return pin; }
    double getBalance() const { return balance; }
    string getHolderName() const { return holderName; }

    void deposit(double amount)
    {
        balance += amount;
        transactionHistory.push_back("Deposit: " + to_string(amount));
        cout << "Deposit successful. New balance: " << fixed << setprecision(2) << balance << "\n";
    }

    bool withdraw(double amount)
    {
        if (amount <= balance)
        {
            balance -= amount;
            transactionHistory.push_back("Withdraw: " + to_string(amount));
            cout << "Withdrawal successful. New balance: " << fixed << setprecision(2) << balance << "\n";
            return true;
        }
        cout << "Insufficient balance.\n";
        return false;
    }

    void showTransactionHistory() const
    {
        cout << "Transaction History for Account " << accountNumber << ":\n";
        for (const auto &transaction : transactionHistory)
        {
            cout << transaction << "\n";
        }
    }
};

// Bank
class Bank
{
private:
    unordered_map<string, Account *> accounts;

    string generateAccountNumber()
    {
        return to_string(rand() % 1000000); 
    }

public:
    Bank()
    {
        srand(static_cast<unsigned int>(time(0))); // Seed for randomness
    }

    ~Bank()
    {
        for (auto &pair : accounts)
        {
            delete pair.second;
        }
    }

    string openAccount(const string &name, const string &address,
                       const string &phone, const string &email)
    {
        string accNum = generateAccountNumber();
        Account *newAccount = new Account(accNum, name, address, phone, email);
        accounts[accNum] = newAccount;
        cout << "Account created. Account Number: " << accNum << ", PIN: " << newAccount->getPin() << "\n";
        return accNum;
    }

    void closeAccount(const string &accNum)
    {
        auto it = accounts.find(accNum);
        if (it != accounts.end())
        {
            delete it->second;
            accounts.erase(it);
            cout << "Account closed successfully.\n";
        }
        else
        {
            cout << "Account not found.\n";
        }
    }

    void deposit(const string &accNum, double amount)
    {
        auto it = accounts.find(accNum);
        if (it != accounts.end())
        {
            it->second->deposit(amount);
        }
        else
        {
            cout << "Account not found.\n";
        }
    }

    void withdraw(const string &accNum, double amount)
    {
        auto it = accounts.find(accNum);
        if (it != accounts.end())
        {
            it->second->withdraw(amount);
        }
        else
        {
            cout << "Account not found.\n";
        }
    }

    void transfer(const string &fromAcc, const string &toAcc, double amount)
    {
        auto fromIt = accounts.find(fromAcc);
        auto toIt = accounts.find(toAcc);
        if (fromIt != accounts.end() && toIt != accounts.end())
        {
            if (fromIt->second->withdraw(amount))
            {
                toIt->second->deposit(amount);
                cout << "Transfer successful.\n";
            }
            else
            {
                cout << "Insufficient balance in source account.\n";
            }
        }
        else
        {
            cout << "One or both accounts not found.\n";
        }
    }

    void showTransactionHistory(const string &accNum) const
    {
        auto it = accounts.find(accNum);
        if (it != accounts.end())
        {
            it->second->showTransactionHistory();
        }
        else
        {
            cout << "Account not found.\n";
        }
    }

    void findAccountByName(const string &name) const
    {
        for (const auto &pair : accounts)
        {
            if (pair.second->getHolderName() == name)
            {
                cout << "Account Number: " << pair.first << ", Balance: " << pair.second->getBalance() << "\n";
            }
        }
    }
};

// Main
int main() {
    Bank myBank;
    int choice;
    string name, address, phone, email, accNum1, accNum2;
    double amount;

    do {
        cout << "\n=======================================\n";
        cout << "          BANK MANAGEMENT SYSTEM       \n";
        cout << "=======================================\n";
        cout << "1. Open Account\n";
        cout << "2. Close Account\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. Transfer\n";
        cout << "6. Show Transaction History\n";
        cout << "7. Find Account by Name\n";
        cout << "8. Exit\n";
        cout << "---------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cout << "---------------------------------------\n";

        switch (choice) {
        case 1:
            cout << "Enter account holder's name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter address: ";
            getline(cin, address);
            cout << "Enter phone number: ";
            getline(cin, phone);
            cout << "Enter email: ";
            getline(cin, email);
            myBank.openAccount(name, address, phone, email);
            break;
        case 2:
            cout << "Enter account number to close: ";
            cin >> accNum1;
            myBank.closeAccount(accNum1);
            break;
        case 3:
            cout << "Enter account number to deposit: ";
            cin >> accNum1;
            cout << "Enter amount to deposit: ";
            cin >> amount;
            myBank.deposit(accNum1, amount);
            break;
        case 4:
            cout << "Enter account number to withdraw from: ";
            cin >> accNum1;
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            myBank.withdraw(accNum1, amount);
            break;
        case 5:
            cout << "Enter source account number: ";
            cin >> accNum1;
            cout << "Enter destination account number: ";
            cin >> accNum2;
            cout << "Enter amount to transfer: ";
            cin >> amount;
            myBank.transfer(accNum1, accNum2, amount);
            break;
        case 6:
            cout << "Enter account number to view transaction history: ";
            cin >> accNum1;
            myBank.showTransactionHistory(accNum1);
            break;
        case 7:
            cout << "Enter account holder's name to search: ";
            cin.ignore();
            getline(cin, name);
            myBank.findAccountByName(name);
            break;
        case 8:
            cout << "Thank you for using the Bank Management System. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }

        if (choice != 8) {
            cout << "Press Enter to continue...";
            cin.ignore();
            cin.get();
        }

    } while (choice != 8);

    return 0;
}
