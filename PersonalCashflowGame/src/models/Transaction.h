#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>
#include <QDate>

class Transaction
{
public:
    Transaction();
    Transaction(int id, const QString &date, const QString &source,
                const QString &category, double amount, bool recurring);

    int getId() const { return m_id; }
    void setId(int id) { m_id = id; }

    QString getDateStr() const { return m_date; }
    void setDate(const QString &date) { m_date = date; }

    QDate getDate() const { return QDate::fromString(m_date, Qt::ISODate); }

    QString getSource() const { return m_source; }
    void setSource(const QString &source) { m_source = source; }

    QString getCategory() const { return m_category; }
    void setCategory(const QString &category) { m_category = category; }

    double getAmount() const { return m_amount; }
    void setAmount(double amount) { m_amount = amount; }

    bool isRecurring() const { return m_isRecurring; }
    void setRecurring(bool recurring) { m_isRecurring = recurring; }

    QString getNotes() const { return m_notes; }
    void setNotes(const QString &notes) { m_notes = notes; }

private:
    int m_id;
    QString m_date;
    QString m_source;
    QString m_category;
    double m_amount;
    bool m_isRecurring;
    QString m_notes;
};

#endif // TRANSACTION_H
