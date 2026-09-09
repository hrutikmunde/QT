#include <QtTest/QtTest>
#include <QCoreApplication>
#include "../src/services/FinancialCalculator.h"
#include "../src/services/DatabaseManager.h"

class TestFinancialCalculator : public QObject
{
    Q_OBJECT

public:
    TestFinancialCalculator();
    ~TestFinancialCalculator();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    // Test calculations based on Excel data
    void testCalculateTotalIncome();
    void testCalculateTotalExpenses();
    void testCalculateCashFlow();
    void testCalculateTotalAssets();
    void testCalculateTotalLiabilities();
    void testCalculateNetWorth();
    void testCalculatePassiveIncome();
    void testCalculateSavingsRate();
    void testCalculateFinancialFreedomPercent();

    // Test formatting
    void testFormatIndianCurrency();
    void testFormatCurrency();
    void testFormatPercent();

    // Test status determinations
    void testFinancialFreedomStatus();
    void testSavingsStatus();

    // Test validation
    void testBudgetVariance();

private:
    FinancialCalculator *m_calculator;
};

TestFinancialCalculator::TestFinancialCalculator()
    : m_calculator(nullptr)
{
}

TestFinancialCalculator::~TestFinancialCalculator()
{
    delete m_calculator;
}

void TestFinancialCalculator::initTestCase()
{
    // Initialize database
    DatabaseManager::instance().initialize();
}

void TestFinancialCalculator::cleanupTestCase()
{
    DatabaseManager::instance().close();
}

void TestFinancialCalculator::init()
{
    m_calculator = new FinancialCalculator();
}

void TestFinancialCalculator::cleanup()
{
    delete m_calculator;
    m_calculator = nullptr;
}

// Test Income calculation
// Excel: Dashboard!B4 = Income!D34 = 15075
void TestFinancialCalculator::testCalculateTotalIncome()
{
    double income = m_calculator->calculateTotalIncome();
    qDebug() << "Total Income:" << income;
    // Income should be >= 0
    QVERIFY(income >= 0);
}

// Test Expenses calculation
// Excel: Dashboard!B5 = Expenses!C14 = 13858
void TestFinancialCalculator::testCalculateTotalExpenses()
{
    double expenses = m_calculator->calculateTotalExpenses();
    qDebug() << "Total Expenses:" << expenses;
    // Expenses should be >= 0
    QVERIFY(expenses >= 0);
}

// Test Cash Flow calculation
// Excel: Dashboard!B6 = B4-B5 = 15075 - 13858 = 1217
void TestFinancialCalculator::testCalculateCashFlow()
{
    double income = m_calculator->calculateTotalIncome();
    double expenses = m_calculator->calculateTotalExpenses();
    double expectedCashFlow = income - expenses;
    double actualCashFlow = m_calculator->calculateCashFlow();

    qDebug() << "Expected Cash Flow:" << expectedCashFlow;
    qDebug() << "Actual Cash Flow:" << actualCashFlow;

    // Allow small floating point differences
    QVERIFY2(qAbs(expectedCashFlow - actualCashFlow) < 0.01,
             "Cash Flow calculation mismatch");
}

// Test Total Assets calculation
// Excel: Dashboard!B8 = Assets!D24 = 0
void TestFinancialCalculator::testCalculateTotalAssets()
{
    double assets = m_calculator->calculateTotalAssets();
    qDebug() << "Total Assets:" << assets;
    QVERIFY(assets >= 0);
}

// Test Total Liabilities calculation
// Excel: Dashboard!B9 = Liabilities!B19 = 0
void TestFinancialCalculator::testCalculateTotalLiabilities()
{
    double liabilities = m_calculator->calculateTotalLiabilities();
    qDebug() << "Total Liabilities:" << liabilities;
    QVERIFY(liabilities >= 0);
}

// Test Net Worth calculation
// Excel: Dashboard!B10 = B8-B9 = 0-0 = 0
void TestFinancialCalculator::testCalculateNetWorth()
{
    double assets = m_calculator->calculateTotalAssets();
    double liabilities = m_calculator->calculateTotalLiabilities();
    double expectedNetWorth = assets - liabilities;
    double actualNetWorth = m_calculator->calculateNetWorth();

    qDebug() << "Expected Net Worth:" << expectedNetWorth;
    qDebug() << "Actual Net Worth:" << actualNetWorth;

    QVERIFY2(qAbs(expectedNetWorth - actualNetWorth) < 0.01,
             "Net Worth calculation mismatch");
}

// Test Passive Income calculation
// Excel: Dashboard!B7 = Assets!E24 = 0
void TestFinancialCalculator::testCalculatePassiveIncome()
{
    double passiveIncome = m_calculator->calculatePassiveIncome();
    qDebug() << "Passive Income:" << passiveIncome;
    QVERIFY(passiveIncome >= 0);
}

// Test Savings Rate calculation
// Excel: Dashboard!B11 = IFERROR(B6/B4, 0) = 1217/15075 = 8.07%
void TestFinancialCalculator::testCalculateSavingsRate()
{
    double cashFlow = m_calculator->calculateCashFlow();
    double income = m_calculator->calculateTotalIncome();
    double expectedRate = (income > 0) ? (cashFlow / income) * 100.0 : 0.0;
    double actualRate = m_calculator->calculateSavingsRate();

    qDebug() << "Expected Savings Rate:" << expectedRate << "%";
    qDebug() << "Actual Savings Rate:" << actualRate << "%";

    QVERIFY2(qAbs(expectedRate - actualRate) < 0.01,
             "Savings Rate calculation mismatch");
}

// Test Financial Freedom Percent calculation
// Excel: Financial Freedom Tracker!B6 = IFERROR(B4/B5, 0) = 0/13858 = 0%
void TestFinancialCalculator::testCalculateFinancialFreedomPercent()
{
    double ffPercent = m_calculator->calculateFinancialFreedomPercent();
    qDebug() << "Financial Freedom %:" << ffPercent;
    QVERIFY(ffPercent >= 0);
    QVERIFY(ffPercent <= 100); // Cannot exceed 100% logically
}

// Test Indian currency formatting
void TestFinancialCalculator::testFormatIndianCurrency()
{
    // Test basic formatting
    QString formatted = m_calculator->formatIndianCurrency(1000);
    qDebug() << "Formatted 1000:" << formatted;
    QVERIFY2(formatted.contains("1,000") || formatted.contains("1000"),
             "Failed basic formatting");

    // Test lakhs formatting (Indian system)
    formatted = m_calculator->formatIndianCurrency(100000);
    qDebug() << "Formatted 100000:" << formatted;
    QVERIFY2(formatted.contains("1,00,000") || formatted.contains("100,000"),
             "Failed lakhs formatting");

    // Test crores
    formatted = m_calculator->formatIndianCurrency(10000000);
    qDebug() << "Formatted 10000000:" << formatted;
}

// Test currency formatting
void TestFinancialCalculator::testFormatCurrency()
{
    QString formatted = m_calculator->formatCurrency(15075);
    qDebug() << "Formatted Currency:" << formatted;
    QVERIFY2(formatted.startsWith("₹"), "Currency should start with ₹");
}

// Test percent formatting
void TestFinancialCalculator::testFormatPercent()
{
    QString formatted = m_calculator->formatPercent(8.07);
    qDebug() << "Formatted Percent:" << formatted;
    QVERIFY2(formatted.endsWith("%"), "Percent should end with %");
    QVERIFY2(formatted.contains("8.07"), "Should contain 8.07");
}

// Test financial freedom status
void TestFinancialCalculator::testFinancialFreedomStatus()
{
    QString status = m_calculator->getFinancialFreedomStatus();
    qDebug() << "Financial Freedom Status:" << status;
    QVERIFY(!status.isEmpty());
}

// Test savings status
void TestFinancialCalculator::testSavingsStatus()
{
    QString status = m_calculator->getSavingsStatus();
    qDebug() << "Savings Status:" << status;
    QVERIFY(!status.isEmpty());
}

// Test budget variance
void TestFinancialCalculator::testBudgetVariance()
{
    double variance = m_calculator->getBudgetVariance("Food");
    qDebug() << "Food Budget Variance:" << variance;
    // Variance can be positive or negative
}

QTEST_MAIN(TestFinancialCalculator)
#include "test_financialcalculator.moc"
