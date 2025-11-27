#include "FinanceManager.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <numeric> 
#include <iomanip> 
void FinanceManager::generateReports()
{
    int choice;
    std::cout << "\nSelect report:\n";
    std::cout << "1. Daily\n";
    std::cout << "2. Weekly\n";
    std::cout << "3. Monthly\n";
    std::cout << "Your choice: ";
    std::cin >> choice;

    if (choice == 1)
    {
        std::string date;
        std::cout << "Enter date (YYYY-MM-DD): ";
        std::cin >> date;
        reportManager.dailyReport(transactions, date);
    }

    else if (choice == 2)
    {
        std::string endDate;
        std::cout << "Enter end date (YYYY-MM-DD): ";
        std::cin >> endDate;
        reportManager.weeklyReport(transactions, endDate);
    }

    else if (choice == 3)
    {
        std::string monthPrefix;
        std::cout << "Enter month (YYYY-MM): ";
        std::cin >> monthPrefix;
        reportManager.monthlyReport(transactions, monthPrefix);
    }

    else
    {
        std::cout << "Invalid choice.\n";
    }
}


void FinanceManager::addWallet(Wallet* wallet) {
    wallets.push_back(wallet);
}

void FinanceManager::addTransaction(const Transaction& t) {

    transactions.push_back(t);
}

Wallet* FinanceManager::findWalletByName(const std::string& name) 
{
    for (auto* w : wallets)
        if (w->getName() == name)
            return w;
    return nullptr;
}

Category* FinanceManager::findOrCreateCategory(const std::string& name) {
    for (auto& c : categories)
        if (c.getName() == name)
            return &c;

    categories.emplace_back(name);
    return &categories.back();
}

const std::vector<Transaction>& FinanceManager::getTransactions() const {
    return transactions;
}

const std::vector<Category>& FinanceManager::getCategories() const {
    return categories;
}

const std::vector<Wallet*>& FinanceManager::getWallets() const {
    return wallets;
}

// Допоміжна функція для фільтрації за місяцем 
bool isTransactionInMonthHelper(const Transaction& t, const std::string& monthPrefix) {
    return !t.isIncome() && t.getDate().rfind(monthPrefix, 0) == 0;
}

// Допоміжна функція для фільтрації за тижнем 
bool isTransactionInWeekHelper(const Transaction& t, const std::string& endDate) {
    if (endDate.size() != 10) return false;
    std::string prefix = endDate.substr(0, 8);
    int endDay = std::stoi(endDate.substr(8, 2));
    if (t.getDate().substr(0, 8) != prefix) return false;
    int day = std::stoi(t.getDate().substr(8, 2));
    return day >= endDay - 6 && day <= endDay;
}


void FinanceManager::showTopExpensesAndCategoriesMenu() {
    int choice;
    std::cout << "\nSelect Top-3 report:\n";
    std::cout << "1. Top-3 Expenses: Week\n";
    std::cout << "2. Top-3 Expenses: Month\n";
    std::cout << "3. Top-3 Categories: Week\n";
    std::cout << "4. Top-3 Categories: Month\n";
    std::cout << "Your choice: ";
    std::cin >> choice;

    if (choice == 1) top3(true, false);
    else if (choice == 2) top3(false, false);
    else if (choice == 3) top3(true, true);
    else if (choice == 4) top3(false, true);
    else std::cout << "Invalid choice.\n";
}


void FinanceManager::top3(bool isWeekly, bool isCategory) {
    std::string periodKey;
    if (isWeekly) {
        std::cout << "Enter end date (YYYY-MM-DD) for the week: ";
        std::cin >> periodKey;
    }
    else {
        std::cout << "Enter month (YYYY-MM): ";
        std::cin >> periodKey;
    }

    // 1. Фільтрація транзакцій за період та типом
    std::vector<Transaction> filteredTxs;
    for (const auto& t : transactions) {
        bool inPeriod = isWeekly ? isTransactionInWeekHelper(t, periodKey) : isTransactionInMonthHelper(t, periodKey);
        if (inPeriod && !t.isIncome()) {
            filteredTxs.push_back(t);
        }
    }

    if (filteredTxs.empty()) {
        std::cout << "No expenses found for this period.\n";
        return;
    }

    if (!isCategory) {
        // 2a. Топ-3 витрати (сортуємо транзакції за сумою)
        std::sort(filteredTxs.begin(), filteredTxs.end(), [](const Transaction& a, const Transaction& b) {
            return a.getAmount() > b.getAmount();
            });

        std::cout << "\nTop 3 expenses:\n";
        for (size_t i = 0; i < std::min((size_t)3, filteredTxs.size()); ++i) {
            const auto& t = filteredTxs[i];
            std::cout << i + 1 << ". " << t.getAmount() << " UAH | " << t.getCategory() << " | " << t.getDate() << "\n";
        }
    }
    else {
        // 2b. Топ-3 категорії (агрегуємо суми)
        std::map<std::string, double> categoryTotals;
        for (const auto& t : filteredTxs) {
            categoryTotals[t.getCategory()] += t.getAmount();
        }

        std::vector<std::pair<std::string, double>> sortedCategories;
        for (const auto& pair : categoryTotals) {
            sortedCategories.push_back(pair);
        }

        std::sort(sortedCategories.begin(), sortedCategories.end(), [](const auto& a, const auto& b) {
            return a.second > b.second;
            });

        std::cout << "\nTop 3 categories by expense:\n";
        for (size_t i = 0; i < std::min((size_t)3, sortedCategories.size()); ++i) {
            std::cout << i + 1 << ". " << sortedCategories[i].first << ": " << sortedCategories[i].second << " UAH\n";
        }
    }
}


void FinanceManager::saveToFile(const std::string& filename) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing.\n";
        return;
    }

    // Зберігаємо гаманці (спочатку кількість, потім дані)
    outFile << wallets.size() << "\n";
    for (const auto* w : wallets) {
        outFile << *w << "\n";
    }

    // Зберігаємо транзакції (спочатку кількість, потім дані)
    outFile << transactions.size() << "\n";
    for (const auto& t : transactions) {
        outFile << t << "\n";
    }

    // Примітка: Категорії можна відновити з транзакцій при завантаженні, 
    // тому окремо їх зберігати не обов'язково.

    outFile.close();
    std::cout << "Data successfully saved to " << filename << ".\n";
}


void FinanceManager::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for reading.\n";
        return;
    }

    // Очищаємо поточні дані перед завантаженням
    for (auto* w : wallets) { delete w; } // Очищаємо пам'ять
    wallets.clear();
    transactions.clear();
    categories.clear();

    size_t count;

    // Зчитуємо гаманці
    inFile >> count;
    for (size_t i = 0; i < count; ++i) {
        Wallet* w = new Wallet("", "", 0.0); // Створюємо тимчасовий об'єкт
        inFile >> *w; // Використовуємо оператор >>
        wallets.push_back(w);
    }

    // Зчитуємо транзакції
    inFile >> count;
    for (size_t i = 0; i < count; ++i) {
        Transaction t(0.0, "", "", "", false); // Створюємо тимчасовий об'єкт
        inFile >> t; // Використовуємо оператор >>
        transactions.push_back(t);
        // Відновлюємо категорії
        findOrCreateCategory(t.getCategory())->addExpense(t.isIncome() ? 0 : t.getAmount());
    }

    inFile.close();
    std::cout << "Data successfully loaded from " << filename << ".\n";
}

