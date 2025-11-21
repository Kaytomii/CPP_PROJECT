#pragma once
#include <string>

class Transaction {
private:
    double amount;
    std::string category;
    std::string date;
    std::string walletName;
    bool income;

public:
    Transaction(double amount, const std::string& category, const std::string& date,
        const std::string& walletName, bool income);

    double getAmount() const;
    std::string getCategory() const;
    std::string getDate() const;
    std::string getWalletName() const;
    bool isIncome() const;
};
