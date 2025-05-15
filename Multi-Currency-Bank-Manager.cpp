#include <iostream>
#include <string>
using namespace std;

// Store transaction details
struct Transaction {
    string type;
    string currency;
    double foreignAmount;
    double inrAmount;
};

// Handle currency conversion (INR base)
class Currency {
public:
    double convertToINR(string currency, double amount) {
        if (currency == "INR") return amount;
        else if (currency == "USD") return amount * 85.63;
        else if (currency == "EUR") return amount * 95.93;
        else if (currency == "GBP") return amount * 113.74;
        else if (currency == "JPY") return amount * 0.59;
        else return -1;
    }

    bool isSupported(string currency) {
        return currency == "INR" || currency == "USD" || currency == "EUR" || currency == "GBP" || currency == "JPY";
    }

    void showSupported() {
        cout << "Supported currencies: INR, USD, EUR, GBP, JPY\n";
    }
};

// Represents a single bank account
class Account {
    string name, accNumber;
    double balance;
    Transaction history[100];
    int historyCount = 0;

public:
    Account(string n, string acc, double b) {
        name = n;
        accNumber = acc;
        balance = b;
    }

    void deposit(double inrAmount, string currency, double foreignAmount) {
        balance += inrAmount;
        history[historyCount++] = {"Deposit", currency, foreignAmount, inrAmount};
        cout << "Deposited ₹" << inrAmount << " INR\n";
    }

    void withdraw(double inrAmount, string currency, double foreignAmount) {
        if (inrAmount > balance) {
            cout << "Insufficient balance.\n";
            return;
        }
        balance -= inrAmount;
        history[historyCount++] = {"Withdraw", currency, foreignAmount, inrAmount};
        cout << "Withdrawn " << inrAmount << " INR\n";
    }

    void showBalance() {
        cout << "\nName: " << name << "\nAccount: " << accNumber << "\nBalance: ₹" << balance << " INR\n";
    }

    void showHistory() {
        if (historyCount == 0) {
            cout << "No transactions yet.\n";
            return;
        }

        cout << "\n--- Transaction History ---\n";
        for (int i = 0; i < historyCount; i++) {
            cout << i+1 << ". " << history[i].type << " " << history[i].foreignAmount << " "
                 << history[i].currency << " => ₹" << history[i].inrAmount << " INR\n";
        }
    }
};

// Main banking system
int main() {
    string name, acc;
    double initialBalance;
    Currency currencyConverter;

    cout << "Enter your name: ";
    cin.ignore(); getline(cin, name);
    cout << "Enter account number: ";
    getline(cin, acc);
    cout << "Enter initial balance (INR): ";
    cin >> initialBalance;

    Account acc1(name, acc, initialBalance);

    int choice;
    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Show Balance\n2. Deposit\n3. Withdraw\n4. Transaction History\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            acc1.showBalance();
        } else if (choice == 2 || choice == 3) {
            string code;
            double amount;
            currencyConverter.showSupported();
            cout << "Enter currency code: ";
            cin >> code;
            for (char &c : code) c = toupper(c);

            if (!currencyConverter.isSupported(code)) {
                cout << "Unsupported currency.\n";
                continue;
            }

            cout << "Enter amount in " << code << ": ";
            cin >> amount;
            double inrAmt = currencyConverter.convertToINR(code, amount);

            if (inrAmt < 0) {
                cout << "Conversion error.\n";
                continue;
            }

            if (choice == 2)
                acc1.deposit(inrAmt, code, amount);
            else
                acc1.withdraw(inrAmt, code, amount);
        } else if (choice == 4) {
            acc1.showHistory();
        } else if (choice == 5) {
            cout << "Goodbye!\n";
        } else {
            cout << "Invalid option.\n";
        }

    } while (choice != 5);

    return 0;
}