#pragma once
#include <vector>
#include <string>
#include "Transaction.h"

class ReportManager
{
private:
    void printReport(std::string title, int count, double income, double expense) const;

    bool filterDaily(const Transaction& t, std::string date) const;
    bool filterWeekly(const Transaction& t, std::string prefix, int endDay) const;
    bool filterMonthly(const Transaction& t, std::string monthPrefix) const;

public:
    void dailyReport(const std::vector<Transaction>& transactions, std::string date);
    void weeklyReport(const std::vector<Transaction>& transactions, std::string endDate);
    void monthlyReport(const std::vector<Transaction>& transactions, std::string monthPrefix);

};