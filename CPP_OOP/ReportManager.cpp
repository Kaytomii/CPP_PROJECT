#include "ReportManager.h"
#include <iostream>
#include <numeric>
#include <algorithm>

void ReportManager::printReport(std::string title, int count, double income, double expense) const
{
    std::cout << "\n--- " << title << " ---\n";
    std::cout << "Transactions: " << count << "\n";
    std::cout << "Income: " << income << "\n";
    std::cout << "Expense: " << expense << "\n";
}

bool ReportManager::filterDaily(const Transaction& t, std::string date) const 
{
    return t.getDate() == date; // сравнивает дату транзакции с нужной датой
}

bool ReportManager::filterWeekly(const Transaction& t, std::string prefix, int endDay) const 
{
    if (t.getDate().substr(0, 8) != prefix) return false; // берем первые восемь символов даты
    int day = std::stoi(t.getDate().substr(8, 2)); // превращаем строку в число 
    return day >= endDay - 6 && day <= endDay; // если транзакция попадает в 7 дней то метод вернет true
}

bool ReportManager::filterMonthly(const Transaction& t, std::string monthPrefix) const 
{
    return t.getDate().substr(0, 7) == monthPrefix; // берем первые 7 символов даты и сравниваем с monthPrefix
}

void ReportManager::dailyReport(const std::vector<Transaction>& transactions, std::string date) 
{
    int count = std::count_if(transactions.begin(), transactions.end(),
        [this, date](const Transaction& t) { return filterDaily(t, date); }); // лямбда захватывает this, date и для каждой транзакции вызывает filterDaily

    double income = std::accumulate(transactions.begin(), transactions.end(), 0.0,
        [this, date](double sum, const Transaction& t) { return sum + (filterDaily(t, date) && t.isIncome() ? t.getAmount() : 0.0); }); 
    // std::accumulate суммирует значение, если транзакция подходит по дате и это доход, добавляем ее сумму в getAmount, в итоге получаем общую сумму дозодов

    double expense = std::accumulate(transactions.begin(), transactions.end(), 0.0,
        [this, date](double sum, const Transaction& t) { return sum + (filterDaily(t, date) && !t.isIncome() ? t.getAmount() : 0.0); });

    printReport("Daily Report: " + date, count, income, expense);
}

void ReportManager::weeklyReport(const std::vector<Transaction>& transactions, std::string endDate) 
{
    if (endDate.size() != 10) // проверка даты
    {
        std::cout << "Invalid date format.\n";
        return;
    }

    std::string prefix = endDate.substr(0, 8); // prefix = год и месяц
    int endDay = std::stoi(endDate.substr(8, 2)); // число дня

    int count = std::count_if(transactions.begin(), transactions.end(),
        [this, prefix, endDay](const Transaction& t) { return filterWeekly(t, prefix, endDay); });
    // считает количество транзакций за последние 7 дней

    double income = std::accumulate(transactions.begin(), transactions.end(), 0.0,
        [this, prefix, endDay](double sum, const Transaction& t) { return sum + (filterWeekly(t, prefix, endDay) && t.isIncome() ? t.getAmount() : 0.0); });
    // суммирует доходы

    double expense = std::accumulate(transactions.begin(), transactions.end(), 0.0,
        [this, prefix, endDay](double sum, const Transaction& t) { return sum + (filterWeekly(t, prefix, endDay) && !t.isIncome() ? t.getAmount() : 0.0); });
    // суммирует расходы

    printReport("Weekly Report (last 7 days ending " + endDate + ")", count, income, expense);
}

void ReportManager::monthlyReport(const std::vector<Transaction>& transactions, std::string monthPrefix) 
{
    int count = std::count_if(transactions.begin(), transactions.end(),
        [this, monthPrefix](const Transaction& t) { return filterMonthly(t, monthPrefix); });
    // считает количество транзакций за месяц

    double income = std::accumulate(transactions.begin(), transactions.end(), 0.0,
        [this, monthPrefix](double sum, const Transaction& t) { return sum + (filterMonthly(t, monthPrefix) && t.isIncome() ? t.getAmount() : 0.0); });
    // суммирует доходы

    double expense = std::accumulate(transactions.begin(), transactions.end(), 0.0,
        [this, monthPrefix](double sum, const Transaction& t) { return sum + (filterMonthly(t, monthPrefix) && !t.isIncome() ? t.getAmount() : 0.0); });
    //суммирует расходы

    printReport("Monthly Report: " + monthPrefix, count, income, expense);
}