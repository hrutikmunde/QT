#include "FinancialCalculator.h"
#include "DatabaseManager.h"

#include <QLocale>
#include <QDebug>

FinancialCalculator::FinancialCalculator(QObject *parent)
    : QObject(parent)
    , m_db(DatabaseManager::instance())
{
}

double FinancialCalculator::calculateTotalIncome() const
{
    return m_db.getTotalMonthlyIncome();
}

double FinancialCalculator::calculateTotalExpenses() const
{
    // Get actual expenses from expenses table
    double expenses = m_db.getTotalExpenses();

    // Also add daily expenses for food
    double foodExpenses = m_db.getTotalFoodExpenses();
    double otherExpenses = m_db.getTotalOtherExpenses();

    // If daily expenses exist, use them instead
    if (foodExpenses > 0 || otherExpenses > 0) {
        return foodExpenses + otherExpenses;
    }

    return expenses;
}

double FinancialCalculator::calculateCashFlow() const
{
    // Excel formula: B4 - B5 (Income - Expenses)
    double income = calculateTotalIncome();
    double expenses = calculateTotalExpenses();
    return income - expenses;
}

double FinancialCalculator::calculateTotalAssets() const
{
    return m_db.getTotalAssetValue();
}

double FinancialCalculator::calculateTotalLiabilities() const
{
    return m_db.getTotalLiabilities();
}

double FinancialCalculator::calculateNetWorth() const
{
    // Excel formula: B8 - B9 (Assets - Liabilities)
    double assets = calculateTotalAssets();
    double liabilities = calculateTotalLiabilities();
    return assets - liabilities;
}

double FinancialCalculator::calculatePassiveIncome() const
{
    return m_db.getTotalPassiveIncome();
}

double FinancialCalculator::calculateSavingsRate() const
{
    // Excel formula: IFERROR(B6/B4, 0) = CashFlow / Income
    double income = calculateTotalIncome();
    if (income > 0) {
        double cashFlow = calculateCashFlow();
        return (cashFlow / income) * 100.0;
    }
    return 0.0;
}

double FinancialCalculator::calculateFinancialFreedomPercent() const
{
    // Excel formula: IFERROR(B4/B5, 0) = Passive Income / Expenses
    double expenses = calculateTotalExpenses();
    if (expenses > 0) {
        double passiveIncome = calculatePassiveIncome();
        return (passiveIncome / expenses) * 100.0;
    }
    return 0.0;
}

double FinancialCalculator::calculateEmergencyFundPercent() const
{
    // Excel formula: IFERROR(B6/B5, 0) = Current / Target
    QMap<QString, double> fund = m_db.getEmergencyFundData();
    double target = fund.value("targetAmount", 0.0);
    if (target > 0) {
        double current = fund.value("currentAmount", 0.0);
        return (current / target) * 100.0;
    }
    return 0.0;
}

double FinancialCalculator::calculateTotalFoodExpenses(int month, int year) const
{
    return m_db.getTotalFoodExpenses(month, year);
}

double FinancialCalculator::calculateTotalOtherExpenses(int month, int year) const
{
    return m_db.getTotalOtherExpenses(month, year);
}

double FinancialCalculator::calculateExpenseVariance() const
{
    double budget = m_db.getTotalExpenseBudget();
    double actual = m_db.getTotalExpenses();
    return actual - budget;
}

double FinancialCalculator::calculateInvestmentReturns() const
{
    double totalInvested = 0.0;
    double totalCurrentValue = 0.0;

    QVector<Investment> investments = m_db.getAllInvestments();
    for (const Investment &inv : investments) {
        totalInvested += inv.getInvestedAmount();
        totalCurrentValue += inv.getCurrentValue();
    }

    if (totalInvested > 0) {
        return ((totalCurrentValue - totalInvested) / totalInvested) * 100.0;
    }
    return 0.0;
}

QString FinancialCalculator::formatCurrency(double amount) const
{
    return QString("₹%1").arg(formatIndianCurrency(amount));
}

QString FinancialCalculator::formatIndianCurrency(double amount) const
{
    // Indian number formatting: 1,00,000 instead of 100,000
    QString numStr = QString::number(qRound(amount));

    if (amount < 0) {
        return "-" + formatIndianCurrency(-amount);
    }

    if (amount < 1000) {
        return numStr;
    }

    // Format with Indian grouping
    QString result;
    int len = numStr.length();

    if (len <= 3) {
        return numStr;
    }

    // Handle first group (1-2 digits)
    int firstGroupLen = len % 3;
    if (firstGroupLen == 0) {
        firstGroupLen = 3;
    }

    result = numStr.left(firstGroupLen);
    numStr = numStr.mid(firstGroupLen);

    // Add remaining groups with comma
    while (!numStr.isEmpty()) {
        result += "," + numStr.left(2);
        numStr = numStr.mid(2);
    }

    return result;
}

QString FinancialCalculator::formatPercent(double percent) const
{
    return QString::number(percent, 'f', 2) + "%";
}

QString FinancialCalculator::getFinancialFreedomStatus() const
{
    double percent = calculateFinancialFreedomPercent();

    if (percent >= 100.0) {
        return "Financial Freedom Achieved!";
    } else if (percent >= 75.0) {
        return "Almost There";
    } else if (percent >= 50.0) {
        return "Halfway There";
    } else if (percent >= 25.0) {
        return "Building Momentum";
    } else {
        return "Just Getting Started";
    }
}

QString FinancialCalculator::getSavingsStatus() const
{
    double rate = calculateSavingsRate();

    if (rate >= 20.0) {
        return "Excellent";
    } else if (rate >= 10.0) {
        return "Good";
    } else if (rate >= 5.0) {
        return "Fair";
    } else {
        return "Needs Improvement";
    }
}

QString FinancialCalculator::getEmergencyFundStatus() const
{
    double percent = calculateEmergencyFundPercent();

    if (percent >= 100.0) {
        return "Fully Funded!";
    } else if (percent >= 50.0) {
        return "Halfway There";
    } else {
        return "Keep Building";
    }
}

bool FinancialCalculator::isOverBudget(const QString &category) const
{
    QSqlQuery query(DatabaseManager::instance().m_database);
    query.prepare("SELECT budget_amount, actual_amount FROM expenses WHERE category = ?");
    query.bindValue(0, category);

    if (query.exec() && query.next()) {
        double budget = query.value("budget_amount").toDouble();
        double actual = query.value("actual_amount").toDouble();
        return actual > budget && budget > 0;
    }
    return false;
}

double FinancialCalculator::getBudgetVariance(const QString &category) const
{
    QSqlQuery query(DatabaseManager::instance().m_database);
    query.prepare("SELECT budget_amount, actual_amount FROM expenses WHERE category = ?");
    query.bindValue(0, category);

    if (query.exec() && query.next()) {
        double budget = query.value("budget_amount").toDouble();
        double actual = query.value("actual_amount").toDouble();
        return actual - budget;
    }
    return 0.0;
}

QMap<QString, double> FinancialCalculator::getIncomeBreakdown() const
{
    QMap<QString, double> breakdown;
    QSqlQuery query(DatabaseManager::instance().m_database);

    if (query.exec("SELECT category, SUM(amount) as total FROM income GROUP BY category")) {
        while (query.next()) {
            QString category = query.value("category").toString();
            double total = query.value("total").toDouble();
            breakdown[category] = total;
        }
    }

    return breakdown;
}

QMap<QString, double> FinancialCalculator::getExpenseBreakdown() const
{
    QMap<QString, double> breakdown;
    QSqlQuery query(DatabaseManager::instance().m_database);

    if (query.exec("SELECT category, actual_amount FROM expenses")) {
        while (query.next()) {
            QString category = query.value("category").toString();
            double amount = query.value("actual_amount").toDouble();
            breakdown[category] = amount;
        }
    }

    return breakdown;
}

QMap<QString, double> FinancialCalculator::getAssetBreakdown() const
{
    QMap<QString, double> breakdown;
    QSqlQuery query(DatabaseManager::instance().m_database);

    if (query.exec("SELECT investment_type, SUM(current_value) as total FROM assets GROUP BY investment_type")) {
        while (query.next()) {
            QString type = query.value("investment_type").toString();
            double total = query.value("total").toDouble();
            breakdown[type] = total;
        }
    }

    return breakdown;
}
