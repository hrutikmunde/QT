#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariantList>
#include <QVector>
#include <QString>
#include <QMap>
#include <memory>

class Player;
class Transaction;
class Asset;
class Liability;
class DailyExpense;
class Investment;
class FinancialGoal;
class GameState;

class DatabaseManager : public QObject
{
    Q_OBJECT

public:
    static DatabaseManager& instance();

    bool initialize();
    bool initializeDatabase();
    void close();

    // Player operations
    bool savePlayer(const Player &player);
    Player* getPlayer() const;
    bool updatePlayerName(const QString &name);
    bool updateMonthlySalary(double salary);
    bool advanceMonth();

    // Income operations
    bool addIncome(const QString &date, const QString &source,
                  const QString &category, double amount, bool recurring, const QString &notes);
    QVector<Transaction> getAllIncome() const;
    double getTotalMonthlyIncome() const;
    bool deleteIncome(int id);

    // Expense operations
    QVector<QPair<QString, double>> getExpenseCategories() const;
    QVector<QPair<QString, double>> getExpenseActuals() const;
    bool updateExpenseCategory(const QString &category, double budget, double actual);
    double getTotalExpenses() const;
    double getTotalExpenseBudget() const;

    // Daily Expense operations
    bool addDailyExpense(const QString &date, const QString &dayOfWeek,
                        double food, double other, const QString &description);
    QVector<DailyExpense> getDailyExpenses(int month = -1, int year = -1) const;
    double getTotalFoodExpenses(int month = -1, int year = -1) const;
    double getTotalOtherExpenses(int month = -1, int year = -1) const;

    // Asset operations
    bool addAsset(const QString &name, const QString &type, double purchaseValue,
                 double currentValue, double monthlyPassiveIncome, double annualReturn);
    QVector<Asset> getAllAssets() const;
    double getTotalAssetValue() const;
    double getTotalPassiveIncome() const;
    bool updateAsset(int id, const QString &name, const QString &type,
                    double purchaseValue, double currentValue,
                    double monthlyPassiveIncome, double annualReturn);
    bool deleteAsset(int id);

    // Liability operations
    bool addLiability(const QString &name, double outstandingBalance,
                     double monthlyEmi, double interestRate, const QString &dueDate);
    QVector<Liability> getAllLiabilities() const;
    double getTotalLiabilities() const;
    bool updateLiability(int id, const QString &name, double outstandingBalance,
                        double monthlyEmi, double interestRate, const QString &dueDate);
    bool deleteLiability(int id);

    // Investment operations
    bool addInvestment(const QString &name, const QString &type,
                     double investedAmount, double currentValue);
    QVector<Investment> getAllInvestments() const;
    bool updateInvestment(int id, const QString &name, const QString &type,
                          double investedAmount, double currentValue);
    bool deleteInvestment(int id);

    // Emergency Fund operations
    bool updateEmergencyFund(double monthlyExpenses, double currentAmount);
    QMap<QString, double> getEmergencyFundData() const;

    // Financial Freedom operations
    QMap<QString, double> getFinancialFreedomData() const;

    // Financial Goal operations
    bool addFinancialGoal(const QString &name, double targetAmount, const QString &targetDate);
    QVector<FinancialGoal> getAllFinancialGoals() const;
    bool updateFinancialGoal(int id, double currentAmount);
    bool deleteFinancialGoal(int id);

    // Monthly Summary operations
    bool saveMonthlySummary(int month, int year, const GameState &state);
    QVector<QMap<QString, QVariant>> getMonthlySummaries() const;

    // Utility
    bool executeNonQuery(const QString &sql, const QVariantList &bindings = QVariantList());

signals:
    void databaseError(const QString &error);
    void dataChanged();

private:
    DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager();
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    bool executeQuery(QSqlQuery &query, const QString &sql, const QVariantList &bindings = QVariantList());
    QString getDatabasePath() const;

    QSqlDatabase m_database;
    QString m_connectionName;
    bool m_initialized;
};

#endif // DATABASEMANAGER_H
