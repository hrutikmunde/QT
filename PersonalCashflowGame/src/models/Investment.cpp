#include "Investment.h"
#include <cmath>

Investment::Investment()
    : m_id(0)
    , m_investedAmount(0.0)
    , m_currentValue(0.0)
    , m_profitLoss(0.0)
    , m_profitLossPercent(0.0)
{
}

Investment::Investment(int id, const QString &name, const QString &type,
                      double investedAmount, double currentValue)
    : m_id(id)
    , m_name(name)
    , m_investmentType(type)
    , m_investedAmount(investedAmount)
    , m_currentValue(currentValue)
{
    calculateProfitLoss();
}

void Investment::calculateProfitLoss()
{
    m_profitLoss = m_currentValue - m_investedAmount;
    if (m_investedAmount > 0) {
        m_profitLossPercent = (m_profitLoss / m_investedAmount) * 100.0;
    } else {
        m_profitLossPercent = 0.0;
    }
}
