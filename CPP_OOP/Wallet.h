#pragma once
#include <string>

class Wallet {
private:
    std::string name;
    std::string type;
    double balance;
    int id; // Добавляем ID
public:
    Wallet(const std::string& name, const std::string& type, double balance,int id);

    void addMoney(double sum);
    bool spendMoney(double sum);

    double getBalance() const;
    std::string getName() const;
    std::string getType() const;
    int getId() const { return id; } // Геттер для ID
    friend std::ostream& operator<<(std::ostream& os, const Wallet& w);
    friend std::istream& operator>>(std::istream& is, Wallet& w);
};

std::ostream& operator<<(std::ostream& os, const Wallet& w);
std::istream& operator>>(std::istream& is, Wallet& w);