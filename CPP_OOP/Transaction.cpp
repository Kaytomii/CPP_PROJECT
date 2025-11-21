#include "Transaction.h"

Transaction::Transaction(double amount, const std::string& category, const std::string& date,
    const std::string& walletName, bool income)
    : amount(amount), category(category), date(date), walletName(walletName), income(income) {
}

double Transaction::getAmount() const { return amount; }
std::string Transaction::getCategory() const { return category; }
std::string Transaction::getDate() const { return date; }
std::string Transaction::getWalletName() const { return walletName; }
bool Transaction::isIncome() const { return income; }
