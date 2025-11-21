#include "Wallet.h"

Wallet::Wallet(const std::string& name, const std::string& type, double balance)
    : name(name), type(type), balance(balance) {
}

void Wallet::addMoney(double sum) {
    balance += sum;
}

bool Wallet::spendMoney(double sum) {
    if (balance < sum) return false;
    balance -= sum;
    return true;
}

double Wallet::getBalance() const {
    return balance;
}

std::string Wallet::getName() const {
    return name;
}

std::string Wallet::getType() const {
    return type;
}