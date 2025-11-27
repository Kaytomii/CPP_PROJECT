#include "Wallet.h"
#include<iostream>
Wallet::Wallet(const std::string& name, const std::string& type, double balance, int id)
    : name(name), type(type), balance(balance),id(id) {
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

std::ostream& operator<<(std::ostream& os, const Wallet& w) {
    os << w.id << " " << w.name << " " << w.type << " " << w.balance;
    return os;
}

std::istream& operator>>(std::istream& is, Wallet& w) {
    is >>w.id >> w.name >> w.type >> w.balance;
    return is;
}