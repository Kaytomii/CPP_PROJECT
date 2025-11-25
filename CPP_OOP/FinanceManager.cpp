#include "FinanceManager.h"
#include <iostream>

void FinanceManager::generateReports()
{
    int choice;
    std::cout << "\nSelect report:\n";
    std::cout << "1. Daily\n";
    std::cout << "2. Weekly\n";
    std::cout << "3. Monthly\n";
    std::cout << "Your choice: ";
    std::cin >> choice;

    if (choice == 1)
    {
        std::string date;
        std::cout << "Enter date (YYYY-MM-DD): ";
        std::cin >> date;
        reportManager.dailyReport(transactions, date);
    }

    else if (choice == 2)
    {
        std::string endDate;
        std::cout << "Enter end date (YYYY-MM-DD): ";
        std::cin >> endDate;
        reportManager.weeklyReport(transactions, endDate);
    }

    else if (choice == 3)
    {
        std::string monthPrefix;
        std::cout << "Enter month (YYYY-MM): ";
        std::cin >> monthPrefix;
        reportManager.monthlyReport(transactions, monthPrefix);
    }

    else
    {
        std::cout << "Invalid choice.\n";
    }
}


void FinanceManager::addWallet(Wallet* wallet) {
    wallets.push_back(wallet);
}

void FinanceManager::addTransaction(const Transaction& t) {

    transactions.push_back(t);
}

Wallet* FinanceManager::findWalletByName(const std::string& name) 
{
    for (auto* w : wallets)
        if (w->getName() == name)
            return w;
    return nullptr;
}

Category* FinanceManager::findOrCreateCategory(const std::string& name) {
    for (auto& c : categories)
        if (c.getName() == name)
            return &c;

    categories.emplace_back(name);
    return &categories.back();
}

const std::vector<Transaction>& FinanceManager::getTransactions() const {
    return transactions;
}

const std::vector<Category>& FinanceManager::getCategories() const {
    return categories;
}

const std::vector<Wallet*>& FinanceManager::getWallets() const {
    return wallets;
}