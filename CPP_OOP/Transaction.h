#pragma once
#include <string>

class Transaction {
private:
    double amount;
    std::string category;
    std::string date;
    int walletId;
    bool income;

public:
    Transaction(double amount, const std::string& category, const std::string& date,
        int walletId, bool income);

    double getAmount() const;
    std::string getCategory() const;
    std::string getDate() const;
    int getWalletId() const; // Геттер для ID
    bool isIncome() const;
    friend std::ostream& operator<<(std::ostream& os, const Transaction& t);
    friend std::istream& operator>>(std::istream& is, Transaction& t);
};
std::ostream& operator<<(std::ostream& os, const Transaction& t);
std::istream& operator>>(std::istream& is, Transaction& t);