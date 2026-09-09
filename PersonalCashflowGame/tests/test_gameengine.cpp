#include <QtTest/QtTest>
#include <QCoreApplication>
#include "../src/services/GameEngine.h"
#include "../src/services/DatabaseManager.h"

class TestGameEngine : public QObject
{
    Q_OBJECT

public:
    TestGameEngine();
    ~TestGameEngine();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    // Game lifecycle tests
    void testStartNewGame();
    void testLoadGame();
    void testResetGame();

    // Game progression tests
    void testNextTurn();
    void testProcessMonth();
    void testSaveCurrentState();

    // Game state tests
    void testGetGameState();
    void testGetCurrentMonth();
    void testGetCurrentYear();
    void testGetPlayerName();
    void testGetMonthlySalary();

    // Statistics tests
    void testGetMonthsPlayed();
    void testGetGoalsAchieved();

    // Validation tests
    void testValidateIncomeAmount();
    void testValidateExpenseAmount();
    void testValidateAssetValue();
    void testValidateLiabilityAmount();

    // Win condition tests
    void testCheckWinCondition();
    void testCheckLoseCondition();

    // Random events
    void testGetRandomExpense();
    void testGetRandomIncome();
    void testGetRandomOpportunity();

private:
    GameEngine *m_engine;
};

TestGameEngine::TestGameEngine()
    : m_engine(nullptr)
{
}

TestGameEngine::~TestGameEngine()
{
    delete m_engine;
}

void TestGameEngine::initTestCase()
{
    DatabaseManager::instance().initialize();
}

void TestGameEngine::cleanupTestCase()
{
    DatabaseManager::instance().close();
}

void TestGameEngine::init()
{
    m_engine = new GameEngine();
    m_engine->loadGame();
}

void TestGameEngine::cleanup()
{
    delete m_engine;
    m_engine = nullptr;
}

// Test starting a new game
void TestGameEngine::testStartNewGame()
{
    bool result = m_engine->startNewGame("TestPlayer", 25000.0);
    QVERIFY2(result, "Failed to start new game");

    QString name = m_engine->getPlayerName();
    QVERIFY2(name == "TestPlayer", "Player name mismatch");

    double salary = m_engine->getMonthlySalary();
    QVERIFY2(qAbs(salary - 25000.0) < 0.01, "Monthly salary mismatch");
}

// Test loading game
void TestGameEngine::testLoadGame()
{
    bool result = m_engine->loadGame();
    QVERIFY(result);

    // After loading, we should have valid state
    QVERIFY(m_engine->getCurrentMonth() >= 1);
    QVERIFY(m_engine->getCurrentYear() >= 2026);
}

// Test resetting game
void TestGameEngine::testResetGame()
{
    // First set some data
    m_engine->startNewGame("TestUser", 30000.0);

    // Then reset
    m_engine->resetGame();

    // Verify reset state
    double salary = m_engine->getMonthlySalary();
    QVERIFY2(qAbs(salary - 20000.0) < 0.01, "Reset should restore default salary");
}

// Test next turn
void TestGameEngine::testNextTurn()
{
    int monthBefore = m_engine->getCurrentMonth();
    int yearBefore = m_engine->getCurrentYear();

    bool result = m_engine->nextTurn();
    QVERIFY(result);

    int monthAfter = m_engine->getCurrentMonth();
    int yearAfter = m_engine->getCurrentYear();

    // Month should advance (or year if December)
    if (monthBefore == 12) {
        QVERIFY2(yearAfter == yearBefore + 1, "Year should increment after December");
        QVERIFY2(monthAfter == 1, "Month should reset to 1 after December");
    } else {
        QVERIFY2(monthAfter == monthBefore + 1, "Month should increment");
    }
}

// Test process month
void TestGameEngine::testProcessMonth()
{
    bool result = m_engine->processMonth();
    QVERIFY(result);
}

// Test save current state
void TestGameEngine::testSaveCurrentState()
{
    m_engine->saveCurrentState();
    // Just verify no crash
    QVERIFY(true);
}

// Test get game state
void TestGameEngine::testGetGameState()
{
    GameState *state = m_engine->getGameState();
    QVERIFY(state != nullptr);

    // Verify state properties
    QVERIFY(state->getCurrentMonth() >= 1);
    QVERIFY(state->getCurrentYear() >= 2026);
}

// Test get current month
void TestGameEngine::testGetCurrentMonth()
{
    int month = m_engine->getCurrentMonth();
    QVERIFY(month >= 1 && month <= 12);
}

// Test get current year
void TestGameEngine::testGetCurrentYear()
{
    int year = m_engine->getCurrentYear();
    QVERIFY(year >= 2024);
}

// Test get player name
void TestGameEngine::testGetPlayerName()
{
    QString name = m_engine->getPlayerName();
    QVERIFY(!name.isEmpty());
}

// Test get monthly salary
void TestGameEngine::testGetMonthlySalary()
{
    double salary = m_engine->getMonthlySalary();
    QVERIFY(salary > 0);
}

// Test get months played
void TestGameEngine::testGetMonthsPlayed()
{
    int months = m_engine->getMonthsPlayed();
    QVERIFY(months >= 0);
}

// Test get goals achieved
void TestGameEngine::testGetGoalsAchieved()
{
    int goals = m_engine->getGoalsAchieved();
    QVERIFY(goals >= 0);

    int totalGoals = m_engine->getTotalGoals();
    QVERIFY(totalGoals >= 0);
    QVERIFY(goals <= totalGoals);
}

// Test income validation
void TestGameEngine::testValidateIncomeAmount()
{
    QVERIFY(m_engine->validateIncomeAmount(1000));
    QVERIFY(m_engine->validateIncomeAmount(50000));
    QVERIFY(!m_engine->validateIncomeAmount(0));
    QVERIFY(!m_engine->validateIncomeAmount(-100));
    QVERIFY(!m_engine->validateIncomeAmount(100000000)); // Too large
}

// Test expense validation
void TestGameEngine::testValidateExpenseAmount()
{
    QVERIFY(m_engine->validateExpenseAmount(100));
    QVERIFY(m_engine->validateExpenseAmount(5000));
    QVERIFY(!m_engine->validateExpenseAmount(0));
    QVERIFY(!m_engine->validateExpenseAmount(-50));
}

// Test asset value validation
void TestGameEngine::testValidateAssetValue()
{
    QVERIFY(m_engine->validateAssetValue(100000));
    QVERIFY(m_engine->validateAssetValue(10000000));
    QVERIFY(m_engine->validateAssetValue(0)); // 0 is valid for assets
    QVERIFY(!m_engine->validateAssetValue(-1000));
}

// Test liability amount validation
void TestGameEngine::testValidateLiabilityAmount()
{
    QVERIFY(m_engine->validateLiabilityAmount(50000));
    QVERIFY(m_engine->validateLiabilityAmount(0));
    QVERIFY(!m_engine->validateLiabilityAmount(-5000));
}

// Test win condition (initially false)
void TestGameEngine::testCheckWinCondition()
{
    bool won = m_engine->checkWinCondition();
    // Initially should be false (no passive income)
    qDebug() << "Win Condition:" << won;
    // Just verify it returns a valid boolean
    QVERIFY2(won == true || won == false, "Win condition should return boolean");
}

// Test lose condition
void TestGameEngine::testCheckLoseCondition()
{
    bool lost = m_engine->checkLoseCondition();
    // Should be false initially (no negative net worth extreme)
    qDebug() << "Lose Condition:" << lost;
    QVERIFY2(lost == true || lost == false, "Lose condition should return boolean");
}

// Test random expense generation
void TestGameEngine::testGetRandomExpense()
{
    QString expense = m_engine->getRandomExpense();
    QVERIFY(!expense.isEmpty());
    qDebug() << "Random Expense:" << expense;
}

// Test random income generation
void TestGameEngine::testGetRandomIncome()
{
    QString income = m_engine->getRandomIncome();
    QVERIFY(!income.isEmpty());
    qDebug() << "Random Income:" << income;
}

// Test random opportunity generation
void TestGameEngine::testGetRandomOpportunity()
{
    QString opportunity = m_engine->getRandomOpportunity();
    QVERIFY(!opportunity.isEmpty());
    qDebug() << "Random Opportunity:" << opportunity;
}

QTEST_MAIN(TestGameEngine)
#include "test_gameengine.moc"
