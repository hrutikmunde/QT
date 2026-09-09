#ifndef ASSET_H
#define ASSET_H

#include <QString>

class Asset
{
public:
    Asset();
    Asset(int id, const QString &name, const QString &type,
          double purchaseValue, double currentValue,
          double monthlyPassiveIncome, double annualReturnPercent);

    int getId() const { return m_id; }
    void setId(int id) { m_id = id; }

    QString getName() const { return m_name; }
    void setName(const QString &name) { m_name = name; }

    QString getInvestmentType() const { return m_investmentType; }
    void setInvestmentType(const QString &type) { m_investmentType = type; }

    double getPurchaseValue() const { return m_purchaseValue; }
    void setPurchaseValue(double value) { m_purchaseValue = value; }

    double getCurrentValue() const { return m_currentValue; }
    void setCurrentValue(double value) { m_currentValue = value; }

    double getMonthlyPassiveIncome() const { return m_monthlyPassiveIncome; }
    void setMonthlyPassiveIncome(double income) { m_monthlyPassiveIncome = income; }

    double getAnnualReturnPercent() const { return m_annualReturnPercent; }
    void setAnnualReturnPercent(double percent) { m_annualReturnPercent = percent; }

private:
    int m_id;
    QString m_name;
    QString m_investmentType;
    double m_purchaseValue;
    double m_currentValue;
    double m_monthlyPassiveIncome;
    double m_annualReturnPercent;
};

#endif // ASSET_H
