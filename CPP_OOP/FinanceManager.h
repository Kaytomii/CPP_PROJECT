#pragma once
#include <vector>
#include <string>
#include<fstream>
#include "Wallet.h"
#include "Transaction.h"
#include "Category.h"
#include "ReportManager.h"

class FinanceManager {
private:
    std::vector<Wallet*> wallets;
    std::vector<Transaction> transactions;
    std::vector<Category> categories;
    ReportManager reportManager;
    int nextWalletId = 1; //Генератор ID для гаманців
public:
    void generateReports();// отдельный метод для Reports
    // Додаємо нові методи для ТОП-3 (Завдання 6 та 7)
    void showTopExpensesAndCategoriesMenu();
    void top3(bool isWeekly, bool isCategory);
    void displayWallets()const;
    void displayTransactions()const;
    // Додаємо методи збереження/завантаження (Завдання 8 та 9)
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);

    void addWallet(Wallet* wallet);
    void addTransaction(const Transaction& t);

    Wallet* findWalletById(int id)const;
    Wallet* findWalletByName(const std::string& name) const;
    Category* findOrCreateCategory(const std::string& name);

    const std::vector<Transaction>& getTransactions() const;
    const std::vector<Category>& getCategories() const;
    const std::vector<Wallet*>& getWallets() const;
};

