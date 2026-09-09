#include "Asset.h"

Asset::Asset()
    : m_id(0)
    , m_purchaseValue(0.0)
    , m_currentValue(0.0)
    , m_monthlyPassiveIncome(0.0)
    , m_annualReturnPercent(0.0)
{
}

Asset::Asset(int id, const QString &name, const QString &type,
             double purchaseValue, double currentValue,
             double monthlyPassiveIncome, double annualReturnPercent)
    : m_id(id)
    , m_name(name)
    , m_investmentType(type)
    , m_purchaseValue(purchaseValue)
    , m_currentValue(currentValue)
    , m_monthlyPassiveIncome(monthlyPassiveIncome)
    , m_annualReturnPercent(annualReturnPercent)
{
}
