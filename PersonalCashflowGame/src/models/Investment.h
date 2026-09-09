#ifndef INVESTMENT_H
#define INVESTMENT_H

#include <QString>
#include <cmath>

class Investment
{
public:
    Investment();
    Investment(int id, const QString &name, const QString &type,
              double investedAmount, double currentValue);

    int getId() const { return m_id; }
    void setId(int id) { m_id = id; }

    QString getName() const { return m_name; }
    void setName(const QString &name) { m_name = name; }

    QString getInvestmentType() const { return m_investmentType; }
    void setInvestmentType(const QString &type) { m_investmentType = type; }

    double getInvestedAmount() const { return m_investedAmount; }
    void setInvestedAmount(double amount) { m_investedAmount = amount; }

    double getCurrentValue() const { return m_currentValue; }
    void setCurrentValue(double value) { m_currentValue = value; }

    double getProfitLoss() const { return m_profitLoss; }
    void setProfitLoss(double loss) { m_profitLoss = loss; }

    double getProfitLossPercent() const { return m_profitLossPercent; }
    void setProfitLossPercent(double percent) { m_profitLossPercent = percent; }

    void calculateProfitLoss();

private:
    int m_id;
    QString m_name;
    QString m_investmentType;
    double m_investedAmount;
    double m_currentValue;
    double m_profitLoss;
    double m_profitLossPercent;
};

#endif // INVESTMENT_H
