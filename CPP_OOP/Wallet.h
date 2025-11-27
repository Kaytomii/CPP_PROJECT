#pragma once
#include <string>

class Wallet {
private:
    std::string name;
    std::string type;
    double balance;

public:
    Wallet(const std::string& name, const std::string& type, double balance = 0.0);

    void addMoney(double sum);
    bool spendMoney(double sum);

    double getBalance() const;
    std::string getName() const;
    std::string getType() const;
    friend std::ostream& operator<<(std::ostream& os, const Wallet& w);
    friend std::istream& operator>>(std::istream& is, Wallet& w);
};

std::ostream& operator<<(std::ostream& os, const Wallet& w);
std::istream& operator>>(std::istream& is, Wallet& w);