#pragma once
#include <string>

class Category {
private:
    std::string name;
    double totalSpent;

public:
    Category(const std::string& name);

    void addExpense(double amount);

    double getTotal() const;
    std::string getName() const;
};

