#include "FinanceManager.h"

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