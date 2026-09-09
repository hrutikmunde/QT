#include "GameState.h"

GameState::GameState(QObject *parent)
    : QObject(parent)
    , m_currentMonth(1)
    , m_currentYear(2026)
    , m_totalIncome(0.0)
    , m_totalExpenses(0.0)
    , m_cashFlow(0.0)
    , m_totalAssets(0.0)
    , m_totalLiabilities(0.0)
    , m_netWorth(0.0)
    , m_passiveIncome(0.0)
    , m_savingsRate(0.0)
    , m_financialFreedomPercent(0.0)
    , m_status("Just Getting Started")
{
}

void GameState::recalculate(double income, double expenses, double assets, double liabilities, double passiveIncome)
{
    m_totalIncome = income;
    m_totalExpenses = expenses;
    m_totalAssets = assets;
    m_totalLiabilities = liabilities;
    m_passiveIncome = passiveIncome;

    // Cash Flow = Income - Expenses
    m_cashFlow = m_totalIncome - m_totalExpenses;

    // Net Worth = Total Assets - Total Liabilities
    m_netWorth = m_totalAssets - m_totalLiabilities;

    // Savings Rate = Cash Flow / Total Income * 100
    if (m_totalIncome > 0) {
        m_savingsRate = (m_cashFlow / m_totalIncome) * 100.0;
    } else {
        m_savingsRate = 0.0;
    }

    // Financial Freedom % = (Passive Income / Total Expenses) * 100
    if (m_totalExpenses > 0) {
        m_financialFreedomPercent = (m_passiveIncome / m_totalExpenses) * 100.0;
    } else {
        m_financialFreedomPercent = 0.0;
    }

    // Financial Freedom Status
    if (m_financialFreedomPercent >= 100.0) {
        m_status = "Financial Freedom Achieved!";
    } else if (m_financialFreedomPercent >= 75.0) {
        m_status = "Almost There";
    } else if (m_financialFreedomPercent >= 50.0) {
        m_status = "Halfway There";
    } else if (m_financialFreedomPercent >= 25.0) {
        m_status = "Building Momentum";
    } else {
        m_status = "Just Getting Started";
    }

    emit gameStateChanged();
}
