#ifndef DAILYEXPENSE_H
#define DAILYEXPENSE_H

#include <QString>
#include <QDate>

class DailyExpense
{
public:
    DailyExpense();
    DailyExpense(int id, const QString &date, const QString &dayOfWeek,
                double foodAmount, double otherAmount, const QString &description);

    int getId() const { return m_id; }
    void setId(int id) { m_id = id; }

    QString getDateStr() const { return m_date; }
    void setDate(const QString &date) { m_date = date; }

    QDate getDate() const { return QDate::fromString(m_date, Qt::ISODate); }

    QString getDayOfWeek() const { return m_dayOfWeek; }
    void setDayOfWeek(const QString &day) { m_dayOfWeek = day; }

    double getFoodAmount() const { return m_foodAmount; }
    void setFoodAmount(double amount) { m_foodAmount = amount; }

    double getOtherAmount() const { return m_otherAmount; }
    void setOtherAmount(double amount) { m_otherAmount = amount; }

    double getTotalAmount() const { return m_foodAmount + m_otherAmount; }

    QString getDescription() const { return m_description; }
    void setDescription(const QString &desc) { m_description = desc; }

private:
    int m_id;
    QString m_date;
    QString m_dayOfWeek;
    double m_foodAmount;
    double m_otherAmount;
    QString m_description;
};

#endif // DAILYEXPENSE_H
