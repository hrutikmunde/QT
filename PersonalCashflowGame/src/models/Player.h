#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QDate>

class Player
{
public:
    Player();
    Player(int id, const QString &name, double monthlySalary);

    int getId() const { return m_id; }
    void setId(int id) { m_id = id; }

    QString getName() const { return m_name; }
    void setName(const QString &name) { m_name = name; }

    double getMonthlySalary() const { return m_monthlySalary; }
    void setMonthlySalary(double salary) { m_monthlySalary = salary; }

    int getCurrentMonth() const { return m_currentMonth; }
    void setCurrentMonth(int month) { m_currentMonth = month; }

    int getCurrentYear() const { return m_currentYear; }
    void setCurrentYear(int year) { m_currentYear = year; }

    QString getFormattedMonth() const;

private:
    int m_id;
    QString m_name;
    double m_monthlySalary;
    int m_currentMonth;
    int m_currentYear;
};

#endif // PLAYER_H
