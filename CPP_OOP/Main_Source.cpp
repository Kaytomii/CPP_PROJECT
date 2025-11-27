#include <iostream>
#include <string>
#include "FinanceManager.h"
#include "Wallet.h"
using namespace std;

void showMenu() {
    cout << "\n-------Finance Manager-------\n";
    cout << "1. Add wallet\n";
    cout << "2. Deposit money\n";
    cout << "3. Add transaction\n";
    cout << "4. Show wallets\n";
    cout << "5. Show transactions\n";
    cout << "6. Generate Reports (daily/weekly/monthly)\n";
    cout << "7. Show Top-3 rankings (expenses/categories)\n";
    cout << "8. Save data to file\n";
    cout << "9. Load data from file\n";
    cout << "0. Exit\n";
    cout << "Choose option: ";
}

int main() {
    FinanceManager manager;
    int choice = -1;

    // Автоматичне завантаження при запуску (опційно)
    manager.loadFromFile("finance_data.txt"); 

    while (choice != 0) {
        showMenu();
       
        if (!(cin >> choice)) { // Обробка помилок вводу
            cout << "Invalid input. Please enter a number.\n";
            cin.clear(); // Очищаємо прапор помилки
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Пропускаємо рядок з помилкою
            continue;
        }

        if (choice == 1) {
            system("cls");
            cout << "----- Add wallet -----\n";
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
            system("pause");
        }
        else if (choice == 2) {
            system("cls");
            cout << "----- Deposit money -----\n";
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
            system("pause");
        }
        else if (choice == 3) {
            system("cls");
            cout << "----- Add transaction -----\n";
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
            system("pause");
        }
        else if (choice == 4) {
            system("cls");
            cout << "\n--- Show Wallets ---\n";
            for (auto w : manager.getWallets()) {
                cout << w->getName() << " | " << w->getType()
                    << " | balance: " << w->getBalance() << "\n";
            }
        }
        else if (choice == 5) {
            system("cls");
            cout << "\n--- Show Transactions ---\n";
            for (auto& t : manager.getTransactions()) {
                cout << (t.isIncome() ? "[Income] " : "[Expense] ")
                    << t.getAmount() << " | category: " << t.getCategory()
                    << " | date: " << t.getDate()
                    << " | wallet: " << t.getWalletName() << "\n";
            }
        }

        else if (choice == 6) 
        {
            system("cls");
            manager.generateReports();
            system("pause");
        }

        else if (choice == 7) {
            system("cls");
            manager.showTopExpensesAndCategoriesMenu();
            system("pause");
        }
        else if (choice == 8) {
            system("cls");
            manager.saveToFile("finance_data.txt");
            system("pause");
        }
        else if (choice == 9) {
            system("cls");
            manager.loadFromFile("finance_data.txt");
            system("pause");
        }

        else if (choice != 0) {
            cout << "Invalid option.\n";
        }
        
            
    }

    // Автоматичне збереження при виході 
    manager.saveToFile("finance_data.txt");

    cout << "Exit.\n";
    return 0;
}