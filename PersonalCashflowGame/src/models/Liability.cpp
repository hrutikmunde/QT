#include "Liability.h"

Liability::Liability()
    : m_id(0)
    , m_outstandingBalance(0.0)
    , m_monthlyEmi(0.0)
    , m_interestRate(0.0)
{
}

Liability::Liability(int id, const QString &name, double outstandingBalance,
                    double monthlyEmi, double interestRate, const QString &dueDate)
    : m_id(id)
    , m_name(name)
    , m_outstandingBalance(outstandingBalance)
    , m_monthlyEmi(monthlyEmi)
    , m_interestRate(interestRate)
    , m_dueDate(dueDate)
{
}
