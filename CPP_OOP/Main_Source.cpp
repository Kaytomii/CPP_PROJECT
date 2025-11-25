#include <iostream>
#include <string>
#include "FinanceManager.h"

using namespace std;

void showMenu() {
    cout << "\n-------Finance Manager-------\n";
    cout << "1. Add wallet\n";
    cout << "2. Deposit money\n";
    cout << "3. Add transaction\n";
    cout << "4. Show wallets\n";
    cout << "5. Show transactions\n";
    cout << "6. Generate Reports\n";
    cout << "0. Exit\n";
    cout << "Choose option: ";
}

int main() {
    FinanceManager manager;
    int choice = -1;

    while (choice != 0) {
        showMenu();
        cin >> choice;

        if (choice == 1) {
            string name, type;
            double balance;

            cout << "Wallet name: ";
            cin >> name;

            cout << "Wallet type (cash / debit / credit): ";
            cin >> type;

            cout << "Initial balance: ";
            cin >> balance;

            manager.addWallet(new Wallet(name, type, balance));
            cout << "Wallet added.\n";
        }
        else if (choice == 2) {
            string name;
            double sum;

            cout << "Wallet name: ";
            cin >> name;

            Wallet* w = manager.findWalletByName(name);
            if (!w) {
                cout << "Wallet not found.\n";
                continue;
            }

            cout << "Deposit amount: ";
            cin >> sum;

            w->addMoney(sum);
            cout << "Money deposited.\n";
        }
        else if (choice == 3) {
            string walletName, category, date;
            double amount;
            int type;

            cout << "Wallet name: ";
            cin >> walletName;

            Wallet* w = manager.findWalletByName(walletName);
            if (!w) {
                cout << "Wallet not found.\n";
                continue;
            }

            cout << "Category: ";
            cin >> category;

            cout << "Date (YYYY-MM-DD): ";
            cin >> date;

            cout << "Amount: ";
            cin >> amount;

            cout << "Type (1 - income, 0 - expense): ";
            cin >> type;

            bool income = (type == 1);

            if (!income && !w->spendMoney(amount)) {
                cout << "Not enough balance.\n";
                continue;
            }
            if (income) w->addMoney(amount);

            manager.addTransaction(Transaction(amount, category, date, walletName, income));
            manager.findOrCreateCategory(category)->addExpense(income ? 0 : amount);

            cout << "Transaction added.\n";
        }
        else if (choice == 4) {
            cout << "\n--- Wallets ---\n";
            for (auto w : manager.getWallets()) {
                cout << w->getName() << " | " << w->getType()
                    << " | balance: " << w->getBalance() << "\n";
            }
        }
        else if (choice == 5) {
            cout << "\n--- Transactions ---\n";
            for (auto& t : manager.getTransactions()) {
                cout << (t.isIncome() ? "[Income] " : "[Expense] ")
                    << t.getAmount() << " | category: " << t.getCategory()
                    << " | date: " << t.getDate()
                    << " | wallet: " << t.getWalletName() << "\n";
            }
        }

        else if (choice == 6) 
        {
            manager.generateReports();
        }

        else if (choice != 0) {
            cout << "Invalid option.\n";
        }
    }

    cout << "Exit.\n";
    return 0;
}