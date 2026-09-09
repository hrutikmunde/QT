#ifndef FINANCIALCALCULATOR_H
#define FINANCIALCALCULATOR_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QMap>

class DatabaseManager;

class FinancialCalculator : public QObject
{
    Q_OBJECT

public:
    explicit FinancialCalculator(QObject *parent = nullptr);

    // Core calculations based on Excel formulas
    double calculateTotalIncome() const;
    double calculateTotalExpenses() const;
    double calculateCashFlow() const;
    double calculateTotalAssets() const;
    double calculateTotalLiabilities() const;
    double calculateNetWorth() const;
    double calculatePassiveIncome() const;
    double calculateSavingsRate() const;
    double calculateFinancialFreedomPercent() const;
    double calculateEmergencyFundPercent() const;

    // Detailed calculations
    double calculateTotalFoodExpenses(int month = -1, int year = -1) const;
    double calculateTotalOtherExpenses(int month = -1, int year = -1) const;
    double calculateExpenseVariance() const;
    double calculateInvestmentReturns() const;

    // Formatted values
    QString formatCurrency(double amount) const;
    QString formatPercent(double percent) const;
    QString formatIndianCurrency(double amount) const;

    // Status determinations
    QString getFinancialFreedomStatus() const;
    QString getSavingsStatus() const;
    QString getEmergencyFundStatus() const;

    // Budget analysis
    bool isOverBudget(const QString &category) const;
    double getBudgetVariance(const QString &category) const;

    // Summary data for charts
    QMap<QString, double> getIncomeBreakdown() const;
    QMap<QString, double> getExpenseBreakdown() const;
    QMap<QString, double> getAssetBreakdown() const;

signals:
    void calculationsUpdated();

private:
    DatabaseManager &m_db;
};

#endif // FINANCIALCALCULATOR_H
