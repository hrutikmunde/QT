#ifndef FINANCIALGOAL_H
#define FINANCIALGOAL_H

#include <QString>
#include <cmath>

class FinancialGoal
{
public:
    FinancialGoal();
    FinancialGoal(int id, const QString &name, double targetAmount,
                 double currentAmount, const QString &targetDate);

    int getId() const { return m_id; }
    void setId(int id) { m_id = id; }

    QString getGoalName() const { return m_goalName; }
    void setGoalName(const QString &name) { m_goalName = name; }

    double getTargetAmount() const { return m_targetAmount; }
    void setTargetAmount(double amount) { m_targetAmount = amount; }

    double getCurrentAmount() const { return m_currentAmount; }
    void setCurrentAmount(double amount) { m_currentAmount = amount; }

    double getRemainingAmount() const { return m_remainingAmount; }
    void setRemainingAmount(double amount) { m_remainingAmount = amount; }

    QString getTargetDate() const { return m_targetDate; }
    void setTargetDate(const QString &date) { m_targetDate = date; }

    double getProgressPercent() const { return m_progressPercent; }
    void setProgressPercent(double percent) { m_progressPercent = percent; }

    bool isAchieved() const { return m_isAchieved; }
    void setAchieved(bool achieved) { m_isAchieved = achieved; }

    void calculateProgress();

private:
    int m_id;
    QString m_goalName;
    double m_targetAmount;
    double m_currentAmount;
    double m_remainingAmount;
    QString m_targetDate;
    double m_progressPercent;
    bool m_isAchieved;
};

#endif // FINANCIALGOAL_H
