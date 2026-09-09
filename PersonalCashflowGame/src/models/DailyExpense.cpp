#include "DailyExpense.h"

DailyExpense::DailyExpense()
    : m_id(0)
    , m_foodAmount(0.0)
    , m_otherAmount(0.0)
{
}

DailyExpense::DailyExpense(int id, const QString &date, const QString &dayOfWeek,
                         double foodAmount, double otherAmount, const QString &description)
    : m_id(id)
    , m_date(date)
    , m_dayOfWeek(dayOfWeek)
    , m_foodAmount(foodAmount)
    , m_otherAmount(otherAmount)
    , m_description(description)
{
}
