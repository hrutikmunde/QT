#ifndef LIABILITY_H
#define LIABILITY_H

#include <QString>

class Liability
{
public:
    Liability();
    Liability(int id, const QString &name, double outstandingBalance,
             double monthlyEmi, double interestRate, const QString &dueDate);

    int getId() const { return m_id; }
    void setId(int id) { m_id = id; }

    QString getName() const { return m_name; }
    void setName(const QString &name) { m_name = name; }

    double getOutstandingBalance() const { return m_outstandingBalance; }
    void setOutstandingBalance(double balance) { m_outstandingBalance = balance; }

    double getMonthlyEmi() const { return m_monthlyEmi; }
    void setMonthlyEmi(double emi) { m_monthlyEmi = emi; }

    double getInterestRate() const { return m_interestRate; }
    void setInterestRate(double rate) { m_interestRate = rate; }

    QString getDueDate() const { return m_dueDate; }
    void setDueDate(const QString &date) { m_dueDate = date; }

private:
    int m_id;
    QString m_name;
    double m_outstandingBalance;
    double m_monthlyEmi;
    double m_interestRate;
    QString m_dueDate;
};

#endif // LIABILITY_H
