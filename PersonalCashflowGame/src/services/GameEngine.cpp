#include "GameEngine.h"
#include "DatabaseManager.h"
#include "FinancialCalculator.h"
#include "models/GameState.h"
#include "models/Player.h"
#include "models/FinancialGoal.h"

#include <QRandomGenerator>
#include <QDebug>

GameEngine::GameEngine(QObject *parent)
    : QObject(parent)
    , m_db(DatabaseManager::instance())
    , m_calculator(nullptr)
    , m_gameState(nullptr)
    , m_initialMonth(1)
    , m_initialYear(2026)
{
    m_calculator = new FinancialCalculator(this);
    m_gameState = new GameState(this);
    initializeGameState();
}

void GameEngine::initializeGameState()
{
    Player *player = m_db.getPlayer();
    if (player) {
        m_gameState->setCurrentMonth(player->getCurrentMonth());
        m_gameState->setCurrentYear(player->getCurrentYear());
        delete player;
    }
}

bool GameEngine::startNewGame(const QString &playerName, double monthlySalary)
{
    if (playerName.isEmpty()) {
        emit errorOccurred("Player name cannot be empty");
        return false;
    }

    if (monthlySalary <= 0) {
        emit errorOccurred("Monthly salary must be greater than 0");
        return false;
    }

    m_db.updatePlayerName(playerName);
    m_db.updateMonthlySalary(monthlySalary);

    m_initialMonth = 1;
    m_initialYear = 2026;
    m_gameState->setCurrentMonth(1);
    m_gameState->setCurrentYear(2026);

    emit gameStateChanged();
    return true;
}

void GameEngine::resetGame()
{
    m_db.updatePlayerName("Player");
    m_db.updateMonthlySalary(20000.0);

    // Reset game progress
    m_db.executeNonQuery("DELETE FROM monthly_summary");
    m_db.executeNonQuery("DELETE FROM financial_goals WHERE id > 5");
    m_db.executeNonQuery("DELETE FROM assets");
    m_db.executeNonQuery("DELETE FROM liabilities");
    m_db.executeNonQuery("DELETE FROM income WHERE source != 'Monthly Salary'");
    m_db.executeNonQuery("DELETE FROM investments");

    m_initialMonth = 1;
    m_initialYear = 2026;
    m_gameState->setCurrentMonth(1);
    m_gameState->setCurrentYear(2026);

    emit gameStateChanged();
}

bool GameEngine::loadGame()
{
    initializeGameState();
    emit gameStateChanged();
    return true;
}

bool GameEngine::nextTurn()
{
    return processMonth();
}

bool GameEngine::processMonth()
{
    int currentMonth = m_gameState->getCurrentMonth();
    int currentYear = m_gameState->getCurrentYear();

    // Get all financial data
    double income = m_calculator->calculateTotalIncome();
    double expenses = m_calculator->calculateTotalExpenses();
    double assets = m_calculator->calculateTotalAssets();
    double liabilities = m_calculator->calculateTotalLiabilities();
    double passiveIncome = m_calculator->calculatePassiveIncome();

    // Recalculate game state
    m_gameState->recalculate(income, expenses, assets, liabilities, passiveIncome);

    // Save monthly summary
    m_db.saveMonthlySummary(currentMonth, currentYear, *m_gameState);

    // Update emergency fund
    m_db.updateEmergencyFund(expenses, 0); // Just recalc the target

    // Update financial freedom data
    double ffPercent = m_gameState->getFinancialFreedomPercent();
    QString ffStatus = m_gameState->getStatus();
    m_db.executeNonQuery("UPDATE financial_freedom SET passive_income = ?, financial_freedom_percent = ? WHERE id = 1",
                         {passiveIncome, ffPercent});

    // Advance to next month
    m_db.advanceMonth();
    currentMonth++;
    if (currentMonth > 12) {
        currentMonth = 1;
        currentYear++;
    }
    m_gameState->setCurrentMonth(currentMonth);
    m_gameState->setCurrentYear(currentYear);

    // Check win/lose conditions
    checkAndEmitEvents();

    emit turnChanged();
    emit gameStateChanged();

    return true;
}

void GameEngine::saveCurrentState()
{
    int currentMonth = m_gameState->getCurrentMonth();
    int currentYear = m_gameState->getCurrentYear();

    double income = m_calculator->calculateTotalIncome();
    double expenses = m_calculator->calculateTotalExpenses();
    double assets = m_calculator->calculateTotalAssets();
    double liabilities = m_calculator->calculateTotalLiabilities();
    double passiveIncome = m_calculator->calculatePassiveIncome();

    m_gameState->recalculate(income, expenses, assets, liabilities, passiveIncome);
    m_db.saveMonthlySummary(currentMonth, currentYear, *m_gameState);

    emit gameStateChanged();
}

void GameEngine::processTransactionEvent(const QString &type, double amount, const QString &description)
{
    if (amount <= 0) {
        emit errorOccurred("Transaction amount must be greater than 0");
        return;
    }

    if (type == "income") {
        QDate currentDate = QDate::currentDate();
        m_db.addIncome(currentDate.toString(Qt::ISODate), description, "Other", amount, false, "");
        emit eventOccurred("Income added: " + description, amount, true);
    } else if (type == "expense") {
        // Get current month/year
        int month = m_gameState->getCurrentMonth();
        int year = m_gameState->getCurrentYear();
        QDate currentDate = QDate::currentDate();

        m_db.addDailyExpense(currentDate.toString(Qt::ISODate), currentDate.toString("dddd"),
                            amount, 0, description);
        emit eventOccurred("Expense added: " + description, amount, false);
    }

    saveCurrentState();
}

void GameEngine::processAssetChange(const QString &assetName, double valueChange, bool isGain)
{
    emit eventOccurred(
        isGain ? "Asset gained value: " + assetName : "Asset lost value: " + assetName,
        valueChange, isGain);
    saveCurrentState();
}

void GameEngine::processLiabilityPayoff(double amount, const QString &liabilityName)
{
    emit eventOccurred("Liability paid off: " + liabilityName, amount, true);
    saveCurrentState();
}

bool GameEngine::checkWinCondition() const
{
    // Win when financial freedom is achieved (100%)
    return m_gameState->getFinancialFreedomPercent() >= 100.0;
}

bool GameEngine::checkLoseCondition() const
{
    // No hard lose condition - this is a personal finance tracker
    // But we can return true if net worth goes very negative
    return m_gameState->getNetWorth() < -1000000.0; // ₹10 lakh debt
}

QString GameEngine::getGameStatus() const
{
    return m_gameState->getStatus();
}

GameState* GameEngine::getGameState() const
{
    return m_gameState;
}

int GameEngine::getCurrentMonth() const
{
    return m_gameState->getCurrentMonth();
}

int GameEngine::getCurrentYear() const
{
    return m_gameState->getCurrentYear();
}

QString GameEngine::getPlayerName() const
{
    Player *player = m_db.getPlayer();
    QString name = player ? player->getName() : QString("Player");
    delete player;
    return name;
}

double GameEngine::getMonthlySalary() const
{
    Player *player = m_db.getPlayer();
    double salary = player ? player->getMonthlySalary() : 20000.0;
    delete player;
    return salary;
}

int GameEngine::getMonthsPlayed() const
{
    int currentMonth = m_gameState->getCurrentMonth();
    int currentYear = m_gameState->getCurrentYear();
    return (currentYear - m_initialYear) * 12 + (currentMonth - m_initialMonth);
}

double GameEngine::getTotalEarnings() const
{
    return m_calculator->calculateTotalIncome() * getMonthsPlayed();
}

double GameEngine::getTotalSpending() const
{
    return m_calculator->calculateTotalExpenses() * getMonthsPlayed();
}

int GameEngine::getGoalsAchieved() const
{
    QVector<FinancialGoal> goals = m_db.getAllFinancialGoals();
    int count = 0;
    for (const FinancialGoal &g : goals) {
        if (g.isAchieved()) {
            count++;
        }
    }
    return count;
}

int GameEngine::getTotalGoals() const
{
    return m_db.getAllFinancialGoals().size();
}

bool GameEngine::validateIncomeAmount(double amount) const
{
    return amount > 0 && amount < 10000000.0; // Up to 1 crore
}

bool GameEngine::validateExpenseAmount(double amount) const
{
    return amount > 0 && amount < 10000000.0;
}

bool GameEngine::validateAssetValue(double value) const
{
    return value >= 0 && value < 1000000000.0; // Up to 100 crore
}

bool GameEngine::validateLiabilityAmount(double amount) const
{
    return amount >= 0 && amount < 1000000000.0;
}

QString GameEngine::getRandomExpense() const
{
    QStringList expenses = {
        "Electricity Bill",
        "Mobile Recharge",
        "Groceries",
        "Dining Out",
        "Movie Ticket",
        "Medical Checkup",
        "Clothing",
        "Book Purchase",
        "Transportation",
        "Festival Celebration",
        "Friend's Birthday Gift"
    };

    int index = QRandomGenerator::global()->bounded(expenses.size());
    return expenses[index];
}

QString GameEngine::getRandomIncome() const
{
    QStringList incomeTypes = {
        "Freelance Project",
        "Dividend Payment",
        "Interest from FD",
        "Bonus",
        "Tutoring",
        "Online Sale",
        "Refund",
        "Cashback"
    };

    int index = QRandomGenerator::global()->bounded(incomeTypes.size());
    return incomeTypes[index];
}

QString GameEngine::getRandomOpportunity() const
{
    QStringList opportunities = {
        "SIP opportunity: ₹5,000/month in Index Fund",
        "FD offer: 7.5% interest for 1 year",
        "Stock idea: Blue chip at 52-week low",
        "Real Estate: Plot available in outskirts",
        "PPF: Long-term tax-saving investment",
        "Mutual Fund: Mid-cap with good returns",
        "Gold: Sovereign Gold Bonds available",
        "NPS: Additional tax benefit"
    };

    int index = QRandomGenerator::global()->bounded(opportunities.size());
    return opportunities[index];
}

void GameEngine::checkAndEmitEvents()
{
    if (checkWinCondition()) {
        emit gameFinished(true);
    } else if (checkLoseCondition()) {
        emit gameFinished(false);
    }
}

QString GameEngine::getFinancialStatusText() const
{
    QString status = m_gameState->getStatus();
    double ffPercent = m_gameState->getFinancialFreedomPercent();

    if (ffPercent >= 100.0) {
        return "🎉 Congratulations! You've achieved Financial Freedom!";
    } else if (ffPercent >= 75.0) {
        return QString("💪 You're almost there! %1% to Financial Freedom").arg(ffPercent, 0, 'f', 1);
    } else if (ffPercent >= 50.0) {
        return QString("🎯 Halfway there! Keep building your passive income. Currently at %1%").arg(ffPercent, 0, 'f', 1);
    } else if (ffPercent >= 25.0) {
        return QString("📈 Building momentum! You're at %1% of Financial Freedom").arg(ffPercent, 0, 'f', 1);
    } else {
        return QString("🌱 Just getting started. Focus on increasing passive income. Currently at %1%").arg(ffPercent, 0, 'f', 1);
    }
}
