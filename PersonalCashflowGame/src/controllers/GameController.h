#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QString>
#include <QVariantList>
#include <QVariantMap>
#include <QAbstractListModel>

class DatabaseManager;
class FinancialCalculator;
class GameEngine;
class GameState;
class Player;
class Transaction;
class Asset;
class Liability;
class Investment;
class FinancialGoal;
class DailyExpense;

class IncomeModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        DateRole,
        SourceRole,
        CategoryRole,
        AmountRole,
        RecurringRole,
        NotesRole
    };

    explicit IncomeModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void setTransactions(const QVector<Transaction> &transactions);
    void clear();

signals:
    void countChanged();

private:
    QVector<Transaction> m_transactions;
};

class AssetModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        TypeRole,
        PurchaseValueRole,
        CurrentValueRole,
        MonthlyPassiveIncomeRole,
        AnnualReturnRole
    };

    explicit AssetModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void setAssets(const QVector<Asset> &assets);
    void clear();

signals:
    void countChanged();

private:
    QVector<Asset> m_assets;
};

class LiabilityModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        BalanceRole,
        MonthlyEmiRole,
        InterestRateRole,
        DueDateRole
    };

    explicit LiabilityModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void setLiabilities(const QVector<Liability> &liabilities);
    void clear();

signals:
    void countChanged();

private:
    QVector<Liability> m_liabilities;
};

class InvestmentModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        TypeRole,
        InvestedAmountRole,
        CurrentValueRole,
        ProfitLossRole,
        ProfitLossPercentRole
    };

    explicit InvestmentModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void setInvestments(const QVector<Investment> &investments);
    void clear();

signals:
    void countChanged();

private:
    QVector<Investment> m_investments;
};

class GoalModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        TargetAmountRole,
        CurrentAmountRole,
        RemainingAmountRole,
        TargetDateRole,
        ProgressPercentRole,
        IsAchievedRole
    };

    explicit GoalModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void setGoals(const QVector<FinancialGoal> &goals);
    void clear();

signals:
    void countChanged();

private:
    QVector<FinancialGoal> m_goals;
};

class DailyExpenseModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ rowCount NOTIFY countChanged)
public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        DateRole,
        DayOfWeekRole,
        FoodAmountRole,
        OtherAmountRole,
        DescriptionRole
    };

    explicit DailyExpenseModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    void setExpenses(const QVector<DailyExpense> &expenses);
    void clear();

signals:
    void countChanged();

private:
    QVector<DailyExpense> m_expenses;
};

class GameController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString playerName READ getPlayerName NOTIFY gameStateChanged)
    Q_PROPERTY(int currentMonth READ getCurrentMonth NOTIFY gameStateChanged)
    Q_PROPERTY(int currentYear READ getCurrentYear NOTIFY gameStateChanged)
    Q_PROPERTY(QString currentMonthName READ getCurrentMonthName NOTIFY gameStateChanged)
    Q_PROPERTY(double totalIncome READ getTotalIncome NOTIFY gameStateChanged)
    Q_PROPERTY(double totalExpenses READ getTotalExpenses NOTIFY gameStateChanged)
    Q_PROPERTY(double cashFlow READ getCashFlow NOTIFY gameStateChanged)
    Q_PROPERTY(double totalAssets READ getTotalAssets NOTIFY gameStateChanged)
    Q_PROPERTY(double totalLiabilities READ getTotalLiabilities NOTIFY gameStateChanged)
    Q_PROPERTY(double netWorth READ getNetWorth NOTIFY gameStateChanged)
    Q_PROPERTY(double passiveIncome READ getPassiveIncome NOTIFY gameStateChanged)
    Q_PROPERTY(double savingsRate READ getSavingsRate NOTIFY gameStateChanged)
    Q_PROPERTY(double financialFreedomPercent READ getFinancialFreedomPercent NOTIFY gameStateChanged)
    Q_PROPERTY(QString financialStatus READ getFinancialStatus NOTIFY gameStateChanged)
    Q_PROPERTY(double monthlySalary READ getMonthlySalary NOTIFY gameStateChanged)
    Q_PROPERTY(double emergencyFundTarget READ getEmergencyFundTarget NOTIFY gameStateChanged)
    Q_PROPERTY(double emergencyFundCurrent READ getEmergencyFundCurrent NOTIFY gameStateChanged)
    Q_PROPERTY(double emergencyFundPercent READ getEmergencyFundPercent NOTIFY gameStateChanged)
    Q_PROPERTY(QString emergencyFundStatus READ getEmergencyFundStatus NOTIFY gameStateChanged)
    Q_PROPERTY(int monthsPlayed READ getMonthsPlayed NOTIFY gameStateChanged)
    Q_PROPERTY(int goalsAchieved READ getGoalsAchieved NOTIFY gameStateChanged)
    Q_PROPERTY(int totalGoals READ getTotalGoals NOTIFY gameStateChanged)

    Q_PROPERTY(IncomeModel* incomeModel READ getIncomeModel CONSTANT)
    Q_PROPERTY(AssetModel* assetModel READ getAssetModel CONSTANT)
    Q_PROPERTY(LiabilityModel* liabilityModel READ getLiabilityModel CONSTANT)
    Q_PROPERTY(InvestmentModel* investmentModel READ getInvestmentModel CONSTANT)
    Q_PROPERTY(GoalModel* goalModel READ getGoalModel CONSTANT)
    Q_PROPERTY(DailyExpenseModel* dailyExpenseModel READ getDailyExpenseModel CONSTANT)

public:
    explicit GameController(QObject *parent = nullptr);
    ~GameController() override;

    bool initialize();

    // Property getters
    QString getPlayerName() const;
    int getCurrentMonth() const;
    int getCurrentYear() const;
    QString getCurrentMonthName() const;
    double getTotalIncome() const;
    double getTotalExpenses() const;
    double getCashFlow() const;
    double getTotalAssets() const;
    double getTotalLiabilities() const;
    double getNetWorth() const;
    double getPassiveIncome() const;
    double getSavingsRate() const;
    double getFinancialFreedomPercent() const;
    QString getFinancialStatus() const;
    double getMonthlySalary() const;
    double getEmergencyFundTarget() const;
    double getEmergencyFundCurrent() const;
    double getEmergencyFundPercent() const;
    QString getEmergencyFundStatus() const;
    int getMonthsPlayed() const;
    int getGoalsAchieved() const;
    int getTotalGoals() const;

    // Model getters
    IncomeModel* getIncomeModel() { return m_incomeModel; }
    AssetModel* getAssetModel() { return m_assetModel; }
    LiabilityModel* getLiabilityModel() { return m_liabilityModel; }
    InvestmentModel* getInvestmentModel() { return m_investmentModel; }
    GoalModel* getGoalModel() { return m_goalModel; }
    DailyExpenseModel* getDailyExpenseModel() { return m_dailyExpenseModel; }

    // Formatted getters for QML
    Q_INVOKABLE QString formatCurrency(double amount) const;
    Q_INVOKABLE QString formatPercent(double percent) const;
    Q_INVOKABLE QString formatIndianCurrency(double amount) const;

    // Game operations
    Q_INVOKABLE bool startNewGame(const QString &playerName, double monthlySalary);
    Q_INVOKABLE void resetGame();
    Q_INVOKABLE bool nextTurn();
    Q_INVOKABLE void saveCurrentState();

    // Income operations
    Q_INVOKABLE bool addIncome(const QString &date, const QString &source,
                              const QString &category, double amount, bool recurring, const QString &notes);
    Q_INVOKABLE bool deleteIncome(int id);

    // Expense operations
    Q_INVOKABLE QVariantList getExpenseCategories() const;
    Q_INVOKABLE bool updateExpense(const QString &category, double budget, double actual);
    Q_INVOKABLE void setFoodExpenseActual(double amount);

    // Daily Expense operations
    Q_INVOKABLE bool addDailyExpense(const QString &date, const QString &dayOfWeek,
                                    double food, double other, const QString &description);

    // Asset operations
    Q_INVOKABLE bool addAsset(const QString &name, const QString &type, double purchaseValue,
                             double currentValue, double monthlyPassiveIncome, double annualReturn);
    Q_INVOKABLE bool updateAsset(int id, const QString &name, const QString &type,
                                double purchaseValue, double currentValue,
                                double monthlyPassiveIncome, double annualReturn);
    Q_INVOKABLE bool deleteAsset(int id);

    // Liability operations
    Q_INVOKABLE bool addLiability(const QString &name, double outstandingBalance,
                                 double monthlyEmi, double interestRate, const QString &dueDate);
    Q_INVOKABLE bool updateLiability(int id, const QString &name, double outstandingBalance,
                                    double monthlyEmi, double interestRate, const QString &dueDate);
    Q_INVOKABLE bool deleteLiability(int id);

    // Investment operations
    Q_INVOKABLE bool addInvestment(const QString &name, const QString &type,
                                  double investedAmount, double currentValue);
    Q_INVOKABLE bool deleteInvestment(int id);

    // Emergency Fund operations
    Q_INVOKABLE bool updateEmergencyFund(double currentAmount);

    // Financial Goal operations
    Q_INVOKABLE bool addFinancialGoal(const QString &name, double targetAmount, const QString &targetDate);
    Q_INVOKABLE bool updateFinancialGoalProgress(int id, double currentAmount);
    Q_INVOKABLE bool deleteFinancialGoal(int id);

    // Charts data
    Q_INVOKABLE QVariantList getIncomeVsExpenseData() const;
    Q_INVOKABLE QVariantList getAssetBreakdownData() const;
    Q_INVOKABLE QVariantList getMonthlyNetWorthData() const;
    Q_INVOKABLE QVariantList getCashFlowTrendData() const;
    Q_INVOKABLE QVariantList getExpenseBreakdownData() const;

    // Validation
    Q_INVOKABLE QString validateAmount(double amount, bool allowZero = false) const;
    Q_INVOKABLE QString validateName(const QString &name) const;
    Q_INVOKABLE QString validateDate(const QString &date) const;

    // Excel category lists
    Q_INVOKABLE QStringList getIncomeCategoryList() const;
    Q_INVOKABLE QStringList getAssetTypeList() const;
    Q_INVOKABLE QStringList getInvestmentTypeList() const;

signals:
    void gameStateChanged();
    void errorOccurred(const QString &error);
    void notification(const QString &message);

private slots:
    void onGameEngineEventOccurred(const QString &description, double amount, bool isPositive);
    void onGameEngineErrorOccurred(const QString &error);
    void onGameEngineTurnChanged();
    void onGameEngineGameFinished(bool won);

private:
    void loadData();
    void emitDataChanged();

    DatabaseManager *m_db;
    FinancialCalculator *m_calculator;
    GameEngine *m_engine;

    IncomeModel *m_incomeModel;
    AssetModel *m_assetModel;
    LiabilityModel *m_liabilityModel;
    InvestmentModel *m_investmentModel;
    GoalModel *m_goalModel;
    DailyExpenseModel *m_dailyExpenseModel;
};

#endif // GAMECONTROLLER_H
