#include "Category.h"

Category::Category(const std::string& name)
    : name(name), totalSpent(0.0) {
}

void Category::addExpense(double amount) {
    totalSpent += amount;
}

double Category::getTotal() const {
    return totalSpent;
}

std::string Category::getName() const {
    return name;
}