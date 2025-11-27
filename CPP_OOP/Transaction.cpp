#include "Transaction.h"
#include<iostream>
Transaction::Transaction(double amount, const std::string& category, const std::string& date,
    int walletId, bool income)
    : amount(amount), category(category), date(date), walletId(walletId), income(income) {
}

double Transaction::getAmount() const { return amount; }
std::string Transaction::getCategory() const { return category; }
std::string Transaction::getDate() const { return date; }
int Transaction::getWalletId() const { return walletId; }
bool Transaction::isIncome() const { return income; }

std::ostream& operator<<(std::ostream& os, const Transaction& t) {
    os << t.amount << " " << t.category << " " << t.date << " " << t.walletId << " " << t.income;
    return os;
}

std::istream& operator>>(std::istream& is, Transaction& t) {
    is >> t.amount >> t.category >> t.date >> t.walletId >> t.income;
    return is;
}