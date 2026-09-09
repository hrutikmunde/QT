#include "DatabaseManager.h"
#include "models/Player.h"
#include "models/Transaction.h"
#include "models/Asset.h"
#include "models/Liability.h"
#include "models/DailyExpense.h"
#include "models/Investment.h"
#include "models/FinancialGoal.h"
#include "models/GameState.h"

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QDebug>

DatabaseManager::DatabaseManager(QObject *parent)
    : QObject(parent)
    , m_connectionName("cashflow_db_connection")
    , m_initialized(false)
{
}

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager instance;
    return instance;
}

DatabaseManager::~DatabaseManager()
{
    close();
}

bool DatabaseManager::initialize()
{
    if (m_initialized) {
        return true;
    }

    // Remove existing connection if any
    if (QSqlDatabase::contains(m_connectionName)) {
        QSqlDatabase::removeDatabase(m_connectionName);
    }

    m_database = QSqlDatabase::addDatabase("QSQLITE", m_connectionName);
    m_database.setDatabaseName(getDatabasePath());

    if (!m_database.open()) {
        qWarning() << "Failed to open database:" << m_database.lastError().text();
        emit databaseError(m_database.lastError().text());
        return false;
    }

    // Initialize schema
    if (!initializeDatabase()) {
        qWarning() << "Failed to initialize database schema";
        return false;
    }

    m_initialized = true;
    return true;
}

bool DatabaseManager::initializeDatabase()
{
    QFile schemaFile(":/database/schema.sql");
    QString schema;

    // Try loading from resources first
    if (schemaFile.exists()) {
        if (schemaFile.open(QIODevice::ReadOnly)) {
            schema = schemaFile.readAll();
            schemaFile.close();
        }
    }

    // If not found in resources, use inline schema
    if (schema.isEmpty()) {
        schema = R"(
-- Player/Game State Table
CREATE TABLE IF NOT EXISTS game_state (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    player_name TEXT NOT NULL DEFAULT 'Player',
    monthly_salary REAL NOT NULL DEFAULT 20000.0,
    current_month INTEGER NOT NULL DEFAULT 1,
    current_year INTEGER NOT NULL DEFAULT 2026,
    created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
    updated_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
);

-- Income Table
CREATE TABLE IF NOT EXISTS income (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    date TEXT NOT NULL,
    source TEXT NOT NULL,
    category TEXT NOT NULL,
    amount REAL NOT NULL,
    is_recurring INTEGER NOT NULL DEFAULT 0,
    notes TEXT,
    created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
);

-- Expense Categories Table
CREATE TABLE IF NOT EXISTS expense_categories (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL UNIQUE,
    budget_amount REAL NOT NULL DEFAULT 0,
    is_active INTEGER NOT NULL DEFAULT 1
);

-- Expenses Table
CREATE TABLE IF NOT EXISTS expenses (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    category TEXT NOT NULL,
    budget_amount REAL NOT NULL DEFAULT 0,
    actual_amount REAL NOT NULL DEFAULT 0,
    created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
    updated_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
);

-- Daily Expenses Table
CREATE TABLE IF NOT EXISTS daily_expenses (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    date TEXT NOT NULL,
    day_of_week TEXT,
    food_amount REAL NOT NULL DEFAULT 0,
    other_amount REAL NOT NULL DEFAULT 0,
    description TEXT,
    created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
);

-- Assets Table
CREATE TABLE IF NOT EXISTS assets (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    investment_type TEXT NOT NULL,
    purchase_value REAL NOT NULL DEFAULT 0,
    current_value REAL NOT NULL DEFAULT 0,
    monthly_passive_income REAL NOT NULL DEFAULT 0,
    annual_return_percent REAL NOT NULL DEFAULT 0,
    created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
    updated_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
);

-- Liabilities Table
CREATE TABLE IF NOT EXISTS liabilities (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    outstanding_balance REAL NOT NULL DEFAULT 0,
    monthly_emi REAL NOT NULL DEFAULT 0,
    interest_rate REAL NOT NULL DEFAULT 0,
    due_date TEXT,
    created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
    updated_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
);

-- Investments Table
CREATE TABLE IF NOT EXISTS investments (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    investment_type TEXT NOT NULL,
    invested_amount REAL NOT NULL DEFAULT 0,
    current_value REAL NOT NULL DEFAULT 0,
    profit_loss REAL NOT NULL DEFAULT 0,
    profit_loss_percent REAL NOT NULL DEFAULT 0,
    created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
    updated_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
);

-- Emergency Fund Table
CREATE TABLE IF NOT EXISTS emergency_fund (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    monthly_expenses REAL NOT NULL DEFAULT 0,
    target_amount REAL NOT NULL DEFAULT 0,
    current_amount REAL NOT NULL DEFAULT 0,
    remaining_amount REAL NOT NULL DEFAULT 0,
    completion_percent REAL NOT NULL DEFAULT 0,
    status TEXT NOT NULL DEFAULT 'Keep Building',
    updated_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
);

-- Financial Goals Table
CREATE TABLE IF NOT EXISTS financial_goals (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    goal_name TEXT NOT NULL,
    target_amount REAL NOT NULL DEFAULT 0,
    current_amount REAL NOT NULL DEFAULT 0,
    remaining_amount REAL NOT NULL DEFAULT 0,
    target_date TEXT,
    progress_percent REAL NOT NULL DEFAULT 0,
    is_achieved INTEGER NOT NULL DEFAULT 0,
    created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
    updated_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
);

-- Monthly Summary Table
CREATE TABLE IF NOT EXISTS monthly_summary (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    month INTEGER NOT NULL,
    year INTEGER NOT NULL,
    total_income REAL NOT NULL DEFAULT 0,
    total_expenses REAL NOT NULL DEFAULT 0,
    cash_flow REAL NOT NULL DEFAULT 0,
    total_assets REAL NOT NULL DEFAULT 0,
    total_liabilities REAL NOT NULL DEFAULT 0,
    net_worth REAL NOT NULL DEFAULT 0,
    passive_income REAL NOT NULL DEFAULT 0,
    savings_rate REAL NOT NULL DEFAULT 0,
    financial_freedom_percent REAL NOT NULL DEFAULT 0,
    created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
    UNIQUE(month, year)
);

-- Financial Freedom Status Table
CREATE TABLE IF NOT EXISTS financial_freedom (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    passive_income REAL NOT NULL DEFAULT 0,
    financial_freedom_percent REAL NOT NULL DEFAULT 0,
    status TEXT NOT NULL DEFAULT 'Just Getting Started',
    updated_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
);

-- Insert default expense categories
INSERT OR IGNORE INTO expense_categories (name, budget_amount) VALUES
    ('Rent/Family Contribution', 6000),
    ('Food', 4500),
    ('Transport', 1200),
    ('Mobile & Internet', 300),
    ('Electricity', 0),
    ('Entertainment', 1000),
    ('Shopping', 500),
    ('Medical', 0),
    ('Insurance', 500),
    ('Miscellaneous', 0);

-- Insert initial game state
INSERT OR IGNORE INTO game_state (id, player_name, monthly_salary) VALUES (1, 'Player', 20000);

-- Insert initial emergency fund
INSERT OR IGNORE INTO emergency_fund (id, monthly_expenses, target_amount, current_amount, status)
VALUES (1, 0, 0, 0, 'Keep Building');

-- Insert initial financial freedom
INSERT OR IGNORE INTO financial_freedom (id, status) VALUES (1, 'Just Getting Started');

-- Insert default financial goals
INSERT OR IGNORE INTO financial_goals (id, goal_name, target_amount, target_date) VALUES
    (1, 'Emergency Fund', 30000, '2026-11-30'),
    (2, 'Buy Laptop', 45000, '2026-12-31'),
    (3, 'Buy Bike', 80000, '2027-06-30'),
    (4, 'House Down Payment', 500000, '2029-01-01'),
    (5, 'Vacation', 25000, '2027-03-01');
)";
    }

    QStringList statements = schema.split(';', Qt::SkipEmptyParts);

    for (const QString &statement : statements) {
        QString trimmed = statement.trimmed();
        if (trimmed.isEmpty()) continue;

        QSqlQuery query(m_database);
        if (!query.exec(trimmed)) {
            // Ignore duplicate key errors for INSERT OR IGNORE
            if (!query.lastError().text().contains("UNIQUE constraint failed")) {
                qWarning() << "SQL Error:" << query.lastError().text() << "Statement:" << trimmed;
            }
        }
    }

    return true;
}

void DatabaseManager::close()
{
    if (m_database.isOpen()) {
        m_database.close();
    }
    if (QSqlDatabase::contains(m_connectionName)) {
        QSqlDatabase::removeDatabase(m_connectionName);
    }
    m_initialized = false;
}

QString DatabaseManager::getDatabasePath() const
{
    QString appDataPath = QCoreApplication::applicationDirPath();
    QDir dir(appDataPath);
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    return appDataPath + "/cashflow_game.db";
}

bool DatabaseManager::executeQuery(QSqlQuery &query, const QString &sql, const QVariantList &bindings)
{
    query.prepare(sql);
    for (int i = 0; i < bindings.size(); ++i) {
        query.bindValue(i, bindings[i]);
    }
    if (!query.exec()) {
        qWarning() << "Query failed:" << query.lastError().text() << "SQL:" << sql;
        return false;
    }
    return true;
}

bool DatabaseManager::executeNonQuery(const QString &sql, const QVariantList &bindings)
{
    QSqlQuery query(m_database);
    return executeQuery(query, sql, bindings);
}

// Player operations
bool DatabaseManager::savePlayer(const Player &player)
{
    QVariantList bindings;
    bindings << player.getName() << player.getMonthlySalary()
             << player.getCurrentMonth() << player.getCurrentYear();
    return executeNonQuery(
        "UPDATE game_state SET player_name = ?, monthly_salary = ?, "
        "current_month = ?, current_year = ?, updated_at = CURRENT_TIMESTAMP WHERE id = 1",
        bindings);
}

Player* DatabaseManager::getPlayer() const
{
    Player *player = new Player();
    QSqlQuery query(m_database);
    if (query.exec("SELECT * FROM game_state WHERE id = 1") && query.next()) {
        player->setId(query.value("id").toInt());
        player->setName(query.value("player_name").toString());
        player->setMonthlySalary(query.value("monthly_salary").toDouble());
        player->setCurrentMonth(query.value("current_month").toInt());
        player->setCurrentYear(query.value("current_year").toInt());
    }
    return player;
}

bool DatabaseManager::updatePlayerName(const QString &name)
{
    return executeNonQuery("UPDATE game_state SET player_name = ?, updated_at = CURRENT_TIMESTAMP WHERE id = 1",
                          {name});
}

bool DatabaseManager::updateMonthlySalary(double salary)
{
    return executeNonQuery("UPDATE game_state SET monthly_salary = ?, updated_at = CURRENT_TIMESTAMP WHERE id = 1",
                          {salary});
}

bool DatabaseManager::advanceMonth()
{
    QSqlQuery query(m_database);
    if (query.exec("SELECT current_month, current_year FROM game_state WHERE id = 1") && query.next()) {
        int month = query.value("current_month").toInt();
        int year = query.value("current_year").toInt();
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
        return executeNonQuery(
            "UPDATE game_state SET current_month = ?, current_year = ?, updated_at = CURRENT_TIMESTAMP WHERE id = 1",
            {month, year});
    }
    return false;
}

// Income operations
bool DatabaseManager::addIncome(const QString &date, const QString &source,
                                const QString &category, double amount, bool recurring, const QString &notes)
{
    return executeNonQuery(
        "INSERT INTO income (date, source, category, amount, is_recurring, notes) VALUES (?, ?, ?, ?, ?, ?)",
        {date, source, category, amount, recurring ? 1 : 0, notes});
}

QVector<Transaction> DatabaseManager::getAllIncome() const
{
    QVector<Transaction> transactions;
    QSqlQuery query(m_database);
    if (query.exec("SELECT * FROM income ORDER BY date DESC")) {
        while (query.next()) {
            Transaction t;
            t.setId(query.value("id").toInt());
            t.setDate(query.value("date").toString());
            t.setSource(query.value("source").toString());
            t.setCategory(query.value("category").toString());
            t.setAmount(query.value("amount").toDouble());
            t.setRecurring(query.value("is_recurring").toBool());
            t.setNotes(query.value("notes").toString());
            transactions.append(t);
        }
    }
    return transactions;
}

double DatabaseManager::getTotalMonthlyIncome() const
{
    QSqlQuery query(m_database);
    if (query.exec("SELECT SUM(amount) as total FROM income")) {
        if (query.next()) {
            return query.value("total").toDouble();
        }
    }
    return 0.0;
}

bool DatabaseManager::deleteIncome(int id)
{
    return executeNonQuery("DELETE FROM income WHERE id = ?", {id});
}

// Expense operations
QVector<QPair<QString, double>> DatabaseManager::getExpenseCategories() const
{
    QVector<QPair<QString, double>> categories;
    QSqlQuery query(m_database);
    if (query.exec("SELECT name, budget_amount FROM expense_categories WHERE is_active = 1")) {
        while (query.next()) {
            categories.append(qMakePair(
                query.value("name").toString(),
                query.value("budget_amount").toDouble()));
        }
    }
    return categories;
}

QVector<QPair<QString, double>> DatabaseManager::getExpenseActuals() const
{
    QVector<QPair<QString, double>> actuals;
    QSqlQuery query(m_database);
    if (query.exec("SELECT category, actual_amount FROM expenses")) {
        while (query.next()) {
            actuals.append(qMakePair(
                query.value("category").toString(),
                query.value("actual_amount").toDouble()));
        }
    }
    return actuals;
}

bool DatabaseManager::updateExpenseCategory(const QString &category, double budget, double actual)
{
    // Check if expense exists
    QSqlQuery query(m_database);
    query.prepare("SELECT id FROM expenses WHERE category = ?");
    query.bindValue(0, category);
    query.exec();

    if (query.next()) {
        // Update existing
        return executeNonQuery(
            "UPDATE expenses SET budget_amount = ?, actual_amount = ?, "
            "updated_at = CURRENT_TIMESTAMP WHERE category = ?",
            {budget, actual, category});
    } else {
        // Insert new
        return executeNonQuery(
            "INSERT INTO expenses (category, budget_amount, actual_amount) VALUES (?, ?, ?)",
            {category, budget, actual});
    }
}

double DatabaseManager::getTotalExpenses() const
{
    // Sum of actual expenses from expenses table
    QSqlQuery query(m_database);
    if (query.exec("SELECT SUM(actual_amount) as total FROM expenses")) {
        if (query.next()) {
            return query.value("total").toDouble();
        }
    }
    return 0.0;
}

double DatabaseManager::getTotalExpenseBudget() const
{
    QSqlQuery query(m_database);
    if (query.exec("SELECT SUM(budget_amount) as total FROM expenses")) {
        if (query.next()) {
            return query.value("total").toDouble();
        }
    }
    return 0.0;
}

// Daily Expense operations
bool DatabaseManager::addDailyExpense(const QString &date, const QString &dayOfWeek,
                                     double food, double other, const QString &description)
{
    return executeNonQuery(
        "INSERT INTO daily_expenses (date, day_of_week, food_amount, other_amount, description) VALUES (?, ?, ?, ?, ?)",
        {date, dayOfWeek, food, other, description});
}

QVector<DailyExpense> DatabaseManager::getDailyExpenses(int month, int year) const
{
    QVector<DailyExpense> expenses;

    QString sql = "SELECT * FROM daily_expenses";
    QVariantList bindings;

    if (month > 0 && year > 0) {
        QString datePattern = QString("%1-%2-%").arg(year).arg(month, 2, 10, QChar('0'));
        sql += " WHERE date LIKE ?";
        bindings.append(datePattern + "%");
    }
    sql += " ORDER BY date DESC";

    QSqlQuery query(m_database);
    query.prepare(sql);
    for (int i = 0; i < bindings.size(); ++i) {
        query.bindValue(i, bindings[i]);
    }

    if (query.exec()) {
        while (query.next()) {
            DailyExpense e;
            e.setId(query.value("id").toInt());
            e.setDate(query.value("date").toString());
            e.setDayOfWeek(query.value("day_of_week").toString());
            e.setFoodAmount(query.value("food_amount").toDouble());
            e.setOtherAmount(query.value("other_amount").toDouble());
            e.setDescription(query.value("description").toString());
            expenses.append(e);
        }
    }
    return expenses;
}

double DatabaseManager::getTotalFoodExpenses(int month, int year) const
{
    QString sql = "SELECT SUM(food_amount) as total FROM daily_expenses";
    QVariantList bindings;

    if (month > 0 && year > 0) {
        QString datePattern = QString("%1-%2-%").arg(year).arg(month, 2, 10, QChar('0'));
        sql += " WHERE date LIKE ?";
        bindings.append(datePattern + "%");
    }

    QSqlQuery query(m_database);
    query.prepare(sql);
    for (int i = 0; i < bindings.size(); ++i) {
        query.bindValue(i, bindings[i]);
    }

    if (query.exec() && query.next()) {
        return query.value("total").toDouble();
    }
    return 0.0;
}

double DatabaseManager::getTotalOtherExpenses(int month, int year) const
{
    QString sql = "SELECT SUM(other_amount) as total FROM daily_expenses";
    QVariantList bindings;

    if (month > 0 && year > 0) {
        QString datePattern = QString("%1-%2-%").arg(year).arg(month, 2, 10, QChar('0'));
        sql += " WHERE date LIKE ?";
        bindings.append(datePattern + "%");
    }

    QSqlQuery query(m_database);
    query.prepare(sql);
    for (int i = 0; i < bindings.size(); ++i) {
        query.bindValue(i, bindings[i]);
    }

    if (query.exec() && query.next()) {
        return query.value("total").toDouble();
    }
    return 0.0;
}

// Asset operations
bool DatabaseManager::addAsset(const QString &name, const QString &type, double purchaseValue,
                              double currentValue, double monthlyPassiveIncome, double annualReturn)
{
    return executeNonQuery(
        "INSERT INTO assets (name, investment_type, purchase_value, current_value, "
        "monthly_passive_income, annual_return_percent) VALUES (?, ?, ?, ?, ?, ?)",
        {name, type, purchaseValue, currentValue, monthlyPassiveIncome, annualReturn});
}

QVector<Asset> DatabaseManager::getAllAssets() const
{
    QVector<Asset> assets;
    QSqlQuery query(m_database);
    if (query.exec("SELECT * FROM assets ORDER BY current_value DESC")) {
        while (query.next()) {
            Asset a;
            a.setId(query.value("id").toInt());
            a.setName(query.value("name").toString());
            a.setInvestmentType(query.value("investment_type").toString());
            a.setPurchaseValue(query.value("purchase_value").toDouble());
            a.setCurrentValue(query.value("current_value").toDouble());
            a.setMonthlyPassiveIncome(query.value("monthly_passive_income").toDouble());
            a.setAnnualReturnPercent(query.value("annual_return_percent").toDouble());
            assets.append(a);
        }
    }
    return assets;
}

double DatabaseManager::getTotalAssetValue() const
{
    QSqlQuery query(m_database);
    if (query.exec("SELECT SUM(current_value) as total FROM assets")) {
        if (query.next()) {
            return query.value("total").toDouble();
        }
    }
    return 0.0;
}

double DatabaseManager::getTotalPassiveIncome() const
{
    QSqlQuery query(m_database);
    if (query.exec("SELECT SUM(monthly_passive_income) as total FROM assets")) {
        if (query.next()) {
            return query.value("total").toDouble();
        }
    }
    return 0.0;
}

bool DatabaseManager::updateAsset(int id, const QString &name, const QString &type,
                                double purchaseValue, double currentValue,
                                double monthlyPassiveIncome, double annualReturn)
{
    return executeNonQuery(
        "UPDATE assets SET name = ?, investment_type = ?, purchase_value = ?, current_value = ?, "
        "monthly_passive_income = ?, annual_return_percent = ?, "
        "updated_at = CURRENT_TIMESTAMP WHERE id = ?",
        {name, type, purchaseValue, currentValue, monthlyPassiveIncome, annualReturn, id});
}

bool DatabaseManager::deleteAsset(int id)
{
    return executeNonQuery("DELETE FROM assets WHERE id = ?", {id});
}

// Liability operations
bool DatabaseManager::addLiability(const QString &name, double outstandingBalance,
                                   double monthlyEmi, double interestRate, const QString &dueDate)
{
    return executeNonQuery(
        "INSERT INTO liabilities (name, outstanding_balance, monthly_emi, interest_rate, due_date) VALUES (?, ?, ?, ?, ?)",
        {name, outstandingBalance, monthlyEmi, interestRate, dueDate});
}

QVector<Liability> DatabaseManager::getAllLiabilities() const
{
    QVector<Liability> liabilities;
    QSqlQuery query(m_database);
    if (query.exec("SELECT * FROM liabilities ORDER BY outstanding_balance DESC")) {
        while (query.next()) {
            Liability l;
            l.setId(query.value("id").toInt());
            l.setName(query.value("name").toString());
            l.setOutstandingBalance(query.value("outstanding_balance").toDouble());
            l.setMonthlyEmi(query.value("monthly_emi").toDouble());
            l.setInterestRate(query.value("interest_rate").toDouble());
            l.setDueDate(query.value("due_date").toString());
            liabilities.append(l);
        }
    }
    return liabilities;
}

double DatabaseManager::getTotalLiabilities() const
{
    QSqlQuery query(m_database);
    if (query.exec("SELECT SUM(outstanding_balance) as total FROM liabilities")) {
        if (query.next()) {
            return query.value("total").toDouble();
        }
    }
    return 0.0;
}

bool DatabaseManager::updateLiability(int id, const QString &name, double outstandingBalance,
                                     double monthlyEmi, double interestRate, const QString &dueDate)
{
    return executeNonQuery(
        "UPDATE liabilities SET name = ?, outstanding_balance = ?, monthly_emi = ?, "
        "interest_rate = ?, due_date = ?, updated_at = CURRENT_TIMESTAMP WHERE id = ?",
        {name, outstandingBalance, monthlyEmi, interestRate, dueDate, id});
}

bool DatabaseManager::deleteLiability(int id)
{
    return executeNonQuery("DELETE FROM liabilities WHERE id = ?", {id});
}

// Investment operations
bool DatabaseManager::addInvestment(const QString &name, const QString &type,
                                    double investedAmount, double currentValue)
{
    double profitLoss = currentValue - investedAmount;
    double profitLossPercent = (investedAmount > 0) ? (profitLoss / investedAmount) * 100.0 : 0.0;

    return executeNonQuery(
        "INSERT INTO investments (name, investment_type, invested_amount, current_value, "
        "profit_loss, profit_loss_percent) VALUES (?, ?, ?, ?, ?, ?)",
        {name, type, investedAmount, currentValue, profitLoss, profitLossPercent});
}

QVector<Investment> DatabaseManager::getAllInvestments() const
{
    QVector<Investment> investments;
    QSqlQuery query(m_database);
    if (query.exec("SELECT * FROM investments ORDER BY invested_amount DESC")) {
        while (query.next()) {
            Investment i;
            i.setId(query.value("id").toInt());
            i.setName(query.value("name").toString());
            i.setInvestmentType(query.value("investment_type").toString());
            i.setInvestedAmount(query.value("invested_amount").toDouble());
            i.setCurrentValue(query.value("current_value").toDouble());
            i.setProfitLoss(query.value("profit_loss").toDouble());
            i.setProfitLossPercent(query.value("profit_loss_percent").toDouble());
            investments.append(i);
        }
    }
    return investments;
}

bool DatabaseManager::updateInvestment(int id, const QString &name, const QString &type,
                                      double investedAmount, double currentValue)
{
    double profitLoss = currentValue - investedAmount;
    double profitLossPercent = (investedAmount > 0) ? (profitLoss / investedAmount) * 100.0 : 0.0;

    return executeNonQuery(
        "UPDATE investments SET name = ?, investment_type = ?, invested_amount = ?, "
        "current_value = ?, profit_loss = ?, profit_loss_percent = ?, "
        "updated_at = CURRENT_TIMESTAMP WHERE id = ?",
        {name, type, investedAmount, currentValue, profitLoss, profitLossPercent, id});
}

bool DatabaseManager::deleteInvestment(int id)
{
    return executeNonQuery("DELETE FROM investments WHERE id = ?", {id});
}

// Emergency Fund operations
bool DatabaseManager::updateEmergencyFund(double monthlyExpenses, double currentAmount)
{
    double targetAmount = monthlyExpenses * 6;
    double remainingAmount = qMax(0.0, targetAmount - currentAmount);
    double completionPercent = (targetAmount > 0) ? qMin(100.0, (currentAmount / targetAmount) * 100.0) : 0.0;
    QString status = (completionPercent >= 100.0) ? "Fully Funded!" :
                     (completionPercent >= 50.0) ? "Halfway There" : "Keep Building";

    return executeNonQuery(
        "UPDATE emergency_fund SET monthly_expenses = ?, target_amount = ?, "
        "current_amount = ?, remaining_amount = ?, completion_percent = ?, status = ?, "
        "updated_at = CURRENT_TIMESTAMP WHERE id = 1",
        {monthlyExpenses, targetAmount, currentAmount, remainingAmount, completionPercent, status});
}

QMap<QString, double> DatabaseManager::getEmergencyFundData() const
{
    QMap<QString, double> data;
    QSqlQuery query(m_database);
    if (query.exec("SELECT * FROM emergency_fund WHERE id = 1") && query.next()) {
        data["monthlyExpenses"] = query.value("monthly_expenses").toDouble();
        data["targetAmount"] = query.value("target_amount").toDouble();
        data["currentAmount"] = query.value("current_amount").toDouble();
        data["remainingAmount"] = query.value("remaining_amount").toDouble();
        data["completionPercent"] = query.value("completion_percent").toDouble();
    }
    return data;
}

// Financial Freedom operations
QMap<QString, double> DatabaseManager::getFinancialFreedomData() const
{
    QMap<QString, double> data;
    QSqlQuery query(m_database);
    if (query.exec("SELECT * FROM financial_freedom WHERE id = 1") && query.next()) {
        data["passiveIncome"] = query.value("passive_income").toDouble();
        data["financialFreedomPercent"] = query.value("financial_freedom_percent").toDouble();
    }
    return data;
}

// Financial Goal operations
bool DatabaseManager::addFinancialGoal(const QString &name, double targetAmount, const QString &targetDate)
{
    return executeNonQuery(
        "INSERT INTO financial_goals (goal_name, target_amount, target_date) VALUES (?, ?, ?)",
        {name, targetAmount, targetDate});
}

QVector<FinancialGoal> DatabaseManager::getAllFinancialGoals() const
{
    QVector<FinancialGoal> goals;
    QSqlQuery query(m_database);
    if (query.exec("SELECT * FROM financial_goals ORDER BY target_date ASC")) {
        while (query.next()) {
            FinancialGoal g;
            g.setId(query.value("id").toInt());
            g.setGoalName(query.value("goal_name").toString());
            g.setTargetAmount(query.value("target_amount").toDouble());
            g.setCurrentAmount(query.value("current_amount").toDouble());
            g.setRemainingAmount(query.value("remaining_amount").toDouble());
            g.setTargetDate(query.value("target_date").toString());
            g.setProgressPercent(query.value("progress_percent").toDouble());
            g.setAchieved(query.value("is_achieved").toBool());
            goals.append(g);
        }
    }
    return goals;
}

bool DatabaseManager::updateFinancialGoal(int id, double currentAmount)
{
    // Get target amount first
    QSqlQuery query(m_database);
    query.prepare("SELECT target_amount FROM financial_goals WHERE id = ?");
    query.bindValue(0, id);
    double targetAmount = 0.0;

    if (query.exec() && query.next()) {
        targetAmount = query.value("target_amount").toDouble();
    }

    double remainingAmount = qMax(0.0, targetAmount - currentAmount);
    double progressPercent = (targetAmount > 0) ? qMin(100.0, (currentAmount / targetAmount) * 100.0) : 0.0;
    bool achieved = (currentAmount >= targetAmount);

    return executeNonQuery(
        "UPDATE financial_goals SET current_amount = ?, remaining_amount = ?, "
        "progress_percent = ?, is_achieved = ?, updated_at = CURRENT_TIMESTAMP WHERE id = ?",
        {currentAmount, remainingAmount, progressPercent, achieved ? 1 : 0, id});
}

bool DatabaseManager::deleteFinancialGoal(int id)
{
    return executeNonQuery("DELETE FROM financial_goals WHERE id = ?", {id});
}

// Monthly Summary operations
bool DatabaseManager::saveMonthlySummary(int month, int year, const GameState &state)
{
    return executeNonQuery(
        "INSERT OR REPLACE INTO monthly_summary "
        "(month, year, total_income, total_expenses, cash_flow, total_assets, "
        "total_liabilities, net_worth, passive_income, savings_rate, financial_freedom_percent) "
        "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",
        {month, year, state.getTotalIncome(), state.getTotalExpenses(), state.getCashFlow(),
         state.getTotalAssets(), state.getTotalLiabilities(), state.getNetWorth(),
         state.getPassiveIncome(), state.getSavingsRate(), state.getFinancialFreedomPercent()});
}

QVector<QMap<QString, QVariant>> DatabaseManager::getMonthlySummaries() const
{
    QVector<QMap<QString, QVariant>> summaries;
    QSqlQuery query(m_database);
    if (query.exec("SELECT * FROM monthly_summary ORDER BY year DESC, month DESC LIMIT 12")) {
        while (query.next()) {
            QMap<QString, QVariant> row;
            row["month"] = query.value("month").toInt();
            row["year"] = query.value("year").toInt();
            row["totalIncome"] = query.value("total_income").toDouble();
            row["totalExpenses"] = query.value("total_expenses").toDouble();
            row["cashFlow"] = query.value("cash_flow").toDouble();
            row["totalAssets"] = query.value("total_assets").toDouble();
            row["totalLiabilities"] = query.value("total_liabilities").toDouble();
            row["netWorth"] = query.value("net_worth").toDouble();
            row["passiveIncome"] = query.value("passive_income").toDouble();
            row["savingsRate"] = query.value("savings_rate").toDouble();
            row["financialFreedomPercent"] = query.value("financial_freedom_percent").toDouble();
            summaries.append(row);
        }
    }
    return summaries;
}
