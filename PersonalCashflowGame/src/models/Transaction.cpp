#include "Transaction.h"

Transaction::Transaction()
    : m_id(0)
    , m_amount(0.0)
    , m_isRecurring(false)
{
}

Transaction::Transaction(int id, const QString &date, const QString &source,
                       const QString &category, double amount, bool recurring)
    : m_id(id)
    , m_date(date)
    , m_source(source)
    , m_category(category)
    , m_amount(amount)
    , m_isRecurring(recurring)
{
}
