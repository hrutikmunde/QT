#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <QObject>
#include <QString>

class GameState : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int currentMonth READ getCurrentMonth WRITE setCurrentMonth)
    Q_PROPERTY(int currentYear READ getCurrentYear WRITE setCurrentYear)
    Q_PROPERTY(double totalIncome READ getTotalIncome WRITE setTotalIncome)
    Q_PROPERTY(double totalExpenses READ getTotalExpenses WRITE setTotalExpenses)
    Q_PROPERTY(double cashFlow READ getCashFlow WRITE setCashFlow)
    Q_PROPERTY(double totalAssets READ getTotalAssets WRITE setTotalAssets)
    Q_PROPERTY(double totalLiabilities READ getTotalLiabilities WRITE setTotalLiabilities)
    Q_PROPERTY(double netWorth READ getNetWorth WRITE setNetWorth)
    Q_PROPERTY(double passiveIncome READ getPassiveIncome WRITE setPassiveIncome)
    Q_PROPERTY(double savingsRate READ getSavingsRate WRITE setSavingsRate)
    Q_PROPERTY(double financialFreedomPercent READ getFinancialFreedomPercent WRITE setFinancialFreedomPercent)
    Q_PROPERTY(QString status READ getStatus WRITE setStatus)

public:
    explicit GameState(QObject *parent = nullptr);

    int getCurrentMonth() const { return m_currentMonth; }
    void setCurrentMonth(int month) { m_currentMonth = month; emit gameStateChanged(); }

    int getCurrentYear() const { return m_currentYear; }
    void setCurrentYear(int year) { m_currentYear = year; emit gameStateChanged(); }

    double getTotalIncome() const { return m_totalIncome; }
    void setTotalIncome(double income) { m_totalIncome = income; emit gameStateChanged(); }

    double getTotalExpenses() const { return m_totalExpenses; }
    void setTotalExpenses(double expenses) { m_totalExpenses = expenses; emit gameStateChanged(); }

    double getCashFlow() const { return m_cashFlow; }
    void setCashFlow(double flow) { m_cashFlow = flow; emit gameStateChanged(); }

    double getTotalAssets() const { return m_totalAssets; }
    void setTotalAssets(double assets) { m_totalAssets = assets; emit gameStateChanged(); }

    double getTotalLiabilities() const { return m_totalLiabilities; }
    void setTotalLiabilities(double liabilities) { m_totalLiabilities = liabilities; emit gameStateChanged(); }

    double getNetWorth() const { return m_netWorth; }
    void setNetWorth(double worth) { m_netWorth = worth; emit gameStateChanged(); }

    double getPassiveIncome() const { return m_passiveIncome; }
    void setPassiveIncome(double income) { m_passiveIncome = income; emit gameStateChanged(); }

    double getSavingsRate() const { return m_savingsRate; }
    void setSavingsRate(double rate) { m_savingsRate = rate; emit gameStateChanged(); }

    double getFinancialFreedomPercent() const { return m_financialFreedomPercent; }
    void setFinancialFreedomPercent(double percent) { m_financialFreedomPercent = percent; emit gameStateChanged(); }

    QString getStatus() const { return m_status; }
    void setStatus(const QString &status) { m_status = status; emit gameStateChanged(); }

    void recalculate(double income, double expenses, double assets, double liabilities, double passiveIncome);

signals:
    void gameStateChanged();

private:
    int m_currentMonth;
    int m_currentYear;
    double m_totalIncome;
    double m_totalExpenses;
    double m_cashFlow;
    double m_totalAssets;
    double m_totalLiabilities;
    double m_netWorth;
    double m_passiveIncome;
    double m_savingsRate;
    double m_financialFreedomPercent;
    QString m_status;
};

#endif // GAMESTATE_H
