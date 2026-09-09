#include "Player.h"

Player::Player()
    : m_id(1)
    , m_name("Player")
    , m_monthlySalary(20000.0)
    , m_currentMonth(1)
    , m_currentYear(2026)
{
}

Player::Player(int id, const QString &name, double monthlySalary)
    : m_id(id)
    , m_name(name)
    , m_monthlySalary(monthlySalary)
    , m_currentMonth(1)
    , m_currentYear(2026)
{
}

QString Player::getFormattedMonth() const
{
    QDate date(m_currentYear, m_currentMonth, 1);
    return date.toString("MMMM yyyy");
}
