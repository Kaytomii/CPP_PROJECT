#pragma once
#include <vector>
#include <string>
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

    void addWallet(Wallet* wallet);
    void addTransaction(const Transaction& t);

    Wallet* findWalletByName(const std::string& name);
    Category* findOrCreateCategory(const std::string& name);

    const std::vector<Transaction>& getTransactions() const;
    const std::vector<Category>& getCategories() const;
    const std::vector<Wallet*>& getWallets() const;
};

