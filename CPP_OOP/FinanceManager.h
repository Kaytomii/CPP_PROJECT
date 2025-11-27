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

public:
    void generateReports();// отдельный метод для Reports
    // Додаємо нові методи для ТОП-3 (Завдання 6 та 7)
    void showTopExpensesAndCategoriesMenu();
    void top3(bool isWeekly, bool isCategory);

    // Додаємо методи збереження/завантаження (Завдання 8 та 9)
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);

    void addWallet(Wallet* wallet);
    void addTransaction(const Transaction& t);

    Wallet* findWalletByName(const std::string& name);
    Category* findOrCreateCategory(const std::string& name);

    const std::vector<Transaction>& getTransactions() const;
    const std::vector<Category>& getCategories() const;
    const std::vector<Wallet*>& getWallets() const;
};

