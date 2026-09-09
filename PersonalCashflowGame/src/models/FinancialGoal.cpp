#include "FinancialGoal.h"
#include <cmath>

FinancialGoal::FinancialGoal()
    : m_id(0)
    , m_targetAmount(0.0)
    , m_currentAmount(0.0)
    , m_remainingAmount(0.0)
    , m_progressPercent(0.0)
    , m_isAchieved(false)
{
}

FinancialGoal::FinancialGoal(int id, const QString &name, double targetAmount,
                            double currentAmount, const QString &targetDate)
    : m_id(id)
    , m_goalName(name)
    , m_targetAmount(targetAmount)
    , m_currentAmount(currentAmount)
    , m_targetDate(targetDate)
{
    calculateProgress();
}

void FinancialGoal::calculateProgress()
{
    m_remainingAmount = std::max(0.0, m_targetAmount - m_currentAmount);

    if (m_targetAmount > 0) {
        m_progressPercent = std::min(100.0, (m_currentAmount / m_targetAmount) * 100.0);
    } else {
        m_progressPercent = 0.0;
    }

    m_isAchieved = m_currentAmount >= m_targetAmount;
}
