#include "GameController.h"
#include "services/DatabaseManager.h"
#include "services/FinancialCalculator.h"
#include "services/GameEngine.h"
#include "models/Player.h"
#include "models/Transaction.h"
#include "models/Asset.h"
#include "models/Liability.h"
#include "models/Investment.h"
#include "models/FinancialGoal.h"
#include "models/DailyExpense.h"

#include <QDate>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariantList>
#include <QVariantMap>
#include <QDebug>

// IncomeModel
IncomeModel::IncomeModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int IncomeModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return m_transactions.size();
}

QVariant IncomeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_transactions.size())
        return QVariant();

    const Transaction &t = m_transactions[index.row()];

    switch (role) {
    case IdRole: return t.getId();
    case DateRole: return t.getDateStr();
    case SourceRole: return t.getSource();
    case CategoryRole: return t.getCategory();
    case AmountRole: return t.getAmount();
    case RecurringRole: return t.isRecurring();
    case NotesRole: return t.getNotes();
    default: return QVariant();
    }
}

QHash<int, QByteArray> IncomeModel::roleNames() const
{
    return {
        {IdRole, "id"},
        {DateRole, "date"},
        {SourceRole, "source"},
        {CategoryRole, "category"},
        {AmountRole, "amount"},
        {RecurringRole, "recurring"},
        {NotesRole, "notes"}
    };
}

void IncomeModel::setTransactions(const QVector<Transaction> &transactions)
{
    beginResetModel();
    m_transactions = transactions;
    endResetModel();
    emit countChanged();
}

void IncomeModel::clear()
{
    beginResetModel();
    m_transactions.clear();
    endResetModel();
    emit countChanged();
}

// AssetModel
AssetModel::AssetModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int AssetModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return m_assets.size();
}

QVariant AssetModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_assets.size())
        return QVariant();

    const Asset &a = m_assets[index.row()];

    switch (role) {
    case IdRole: return a.getId();
    case NameRole: return a.getName();
    case TypeRole: return a.getInvestmentType();
    case PurchaseValueRole: return a.getPurchaseValue();
    case CurrentValueRole: return a.getCurrentValue();
    case MonthlyPassiveIncomeRole: return a.getMonthlyPassiveIncome();
    case AnnualReturnRole: return a.getAnnualReturnPercent();
    default: return QVariant();
    }
}

QHash<int, QByteArray> AssetModel::roleNames() const
{
    return {
        {IdRole, "id"},
        {NameRole, "name"},
        {TypeRole, "investmentType"},
        {PurchaseValueRole, "purchaseValue"},
        {CurrentValueRole, "currentValue"},
        {MonthlyPassiveIncomeRole, "monthlyPassiveIncome"},
        {AnnualReturnRole, "annualReturn"}
    };
}

void AssetModel::setAssets(const QVector<Asset> &assets)
{
    beginResetModel();
    m_assets = assets;
    endResetModel();
    emit countChanged();
}

void AssetModel::clear()
{
    beginResetModel();
    m_assets.clear();
    endResetModel();
    emit countChanged();
}

// LiabilityModel
LiabilityModel::LiabilityModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int LiabilityModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return m_liabilities.size();
}

QVariant LiabilityModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_liabilities.size())
        return QVariant();

    const Liability &l = m_liabilities[index.row()];

    switch (role) {
    case IdRole: return l.getId();
    case NameRole: return l.getName();
    case BalanceRole: return l.getOutstandingBalance();
    case MonthlyEmiRole: return l.getMonthlyEmi();
    case InterestRateRole: return l.getInterestRate();
    case DueDateRole: return l.getDueDate();
    default: return QVariant();
    }
}

QHash<int, QByteArray> LiabilityModel::roleNames() const
{
    return {
        {IdRole, "id"},
        {NameRole, "name"},
        {BalanceRole, "balance"},
        {MonthlyEmiRole, "monthlyEmi"},
        {InterestRateRole, "interestRate"},
        {DueDateRole, "dueDate"}
    };
}

void LiabilityModel::setLiabilities(const QVector<Liability> &liabilities)
{
    beginResetModel();
    m_liabilities = liabilities;
    endResetModel();
    emit countChanged();
}

void LiabilityModel::clear()
{
    beginResetModel();
    m_liabilities.clear();
    endResetModel();
    emit countChanged();
}

// InvestmentModel
InvestmentModel::InvestmentModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int InvestmentModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return m_investments.size();
}

QVariant InvestmentModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_investments.size())
        return QVariant();

    const Investment &i = m_investments[index.row()];

    switch (role) {
    case IdRole: return i.getId();
    case NameRole: return i.getName();
    case TypeRole: return i.getInvestmentType();
    case InvestedAmountRole: return i.getInvestedAmount();
    case CurrentValueRole: return i.getCurrentValue();
    case ProfitLossRole: return i.getProfitLoss();
    case ProfitLossPercentRole: return i.getProfitLossPercent();
    default: return QVariant();
    }
}

QHash<int, QByteArray> InvestmentModel::roleNames() const
{
    return {
        {IdRole, "id"},
        {NameRole, "name"},
        {TypeRole, "type"},
        {InvestedAmountRole, "investedAmount"},
        {CurrentValueRole, "currentValue"},
        {ProfitLossRole, "profitLoss"},
        {ProfitLossPercentRole, "profitLossPercent"}
    };
}

void InvestmentModel::setInvestments(const QVector<Investment> &investments)
{
    beginResetModel();
    m_investments = investments;
    endResetModel();
    emit countChanged();
}

void InvestmentModel::clear()
{
    beginResetModel();
    m_investments.clear();
    endResetModel();
    emit countChanged();
}

// GoalModel
GoalModel::GoalModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int GoalModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return m_goals.size();
}

QVariant GoalModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_goals.size())
        return QVariant();

    const FinancialGoal &g = m_goals[index.row()];

    switch (role) {
    case IdRole: return g.getId();
    case NameRole: return g.getGoalName();
    case TargetAmountRole: return g.getTargetAmount();
    case CurrentAmountRole: return g.getCurrentAmount();
    case RemainingAmountRole: return g.getRemainingAmount();
    case TargetDateRole: return g.getTargetDate();
    case ProgressPercentRole: return g.getProgressPercent();
    case IsAchievedRole: return g.isAchieved();
    default: return QVariant();
    }
}

QHash<int, QByteArray> GoalModel::roleNames() const
{
    return {
        {IdRole, "id"},
        {NameRole, "goalName"},
        {TargetAmountRole, "targetAmount"},
        {CurrentAmountRole, "currentAmount"},
        {RemainingAmountRole, "remainingAmount"},
        {TargetDateRole, "targetDate"},
        {ProgressPercentRole, "progressPercent"},
        {IsAchievedRole, "isAchieved"}
    };
}

void GoalModel::setGoals(const QVector<FinancialGoal> &goals)
{
    beginResetModel();
    m_goals = goals;
    endResetModel();
    emit countChanged();
}

void GoalModel::clear()
{
    beginResetModel();
    m_goals.clear();
    endResetModel();
    emit countChanged();
}

// DailyExpenseModel
DailyExpenseModel::DailyExpenseModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int DailyExpenseModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return m_expenses.size();
}

QVariant DailyExpenseModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_expenses.size())
        return QVariant();

    const DailyExpense &e = m_expenses[index.row()];

    switch (role) {
    case IdRole: return e.getId();
    case DateRole: return e.getDateStr();
    case DayOfWeekRole: return e.getDayOfWeek();
    case FoodAmountRole: return e.getFoodAmount();
    case OtherAmountRole: return e.getOtherAmount();
    case DescriptionRole: return e.getDescription();
    default: return QVariant();
    }
}

QHash<int, QByteArray> DailyExpenseModel::roleNames() const
{
    return {
        {IdRole, "id"},
        {DateRole, "date"},
        {DayOfWeekRole, "dayOfWeek"},
        {FoodAmountRole, "foodAmount"},
        {OtherAmountRole, "otherAmount"},
        {DescriptionRole, "description"}
    };
}

void DailyExpenseModel::setExpenses(const QVector<DailyExpense> &expenses)
{
    beginResetModel();
    m_expenses = expenses;
    endResetModel();
    emit countChanged();
}

void DailyExpenseModel::clear()
{
    beginResetModel();
    m_expenses.clear();
    endResetModel();
    emit countChanged();
}

// GameController
GameController::GameController(QObject *parent)
    : QObject(parent)
    , m_db(nullptr)
    , m_calculator(nullptr)
    , m_engine(nullptr)
    , m_incomeModel(nullptr)
    , m_assetModel(nullptr)
    , m_liabilityModel(nullptr)
    , m_investmentModel(nullptr)
    , m_goalModel(nullptr)
    , m_dailyExpenseModel(nullptr)
{
    m_db = &DatabaseManager::instance();
    m_calculator = new FinancialCalculator(this);
    m_engine = new GameEngine(this);

    m_incomeModel = new IncomeModel(this);
    m_assetModel = new AssetModel(this);
    m_liabilityModel = new LiabilityModel(this);
    m_investmentModel = new InvestmentModel(this);
    m_goalModel = new GoalModel(this);
    m_dailyExpenseModel = new DailyExpenseModel(this);

    // Connect engine signals
    connect(m_engine, &GameEngine::eventOccurred, this, &GameController::onGameEngineEventOccurred);
    connect(m_engine, &GameEngine::errorOccurred, this, &GameController::onGameEngineErrorOccurred);
    connect(m_engine, &GameEngine::turnChanged, this, &GameController::onGameEngineTurnChanged);
    connect(m_engine, &GameEngine::gameFinished, this, &GameController::onGameEngineGameFinished);
}

GameController::~GameController()
{
}

bool GameController::initialize()
{
    if (!m_db->initialize()) {
        emit errorOccurred("Failed to initialize database");
        return false;
    }

    m_engine->loadGame();
    loadData();
    return true;
}

void GameController::loadData()
{
    // Load income
    m_incomeModel->setTransactions(m_db->getAllIncome());

    // Load assets
    m_assetModel->setAssets(m_db->getAllAssets());

    // Load liabilities
    m_liabilityModel->setLiabilities(m_db->getAllLiabilities());

    // Load investments
    m_investmentModel->setInvestments(m_db->getAllInvestments());

    // Load financial goals
    m_goalModel->setGoals(m_db->getAllFinancialGoals());

    // Load daily expenses
    m_dailyExpenseModel->setExpenses(m_db->getDailyExpenses());

    emit gameStateChanged();
}

void GameController::emitDataChanged()
{
    loadData();
    emit gameStateChanged();
}

// Property getters
QString GameController::getPlayerName() const
{
    return m_db->getPlayer()->getName();
}

int GameController::getCurrentMonth() const
{
    return m_engine->getCurrentMonth();
}

int GameController::getCurrentYear() const
{
    return m_engine->getCurrentYear();
}

QString GameController::getCurrentMonthName() const
{
    QDate date(getCurrentYear(), getCurrentMonth(), 1);
    return date.toString("MMMM yyyy");
}

double GameController::getTotalIncome() const
{
    return m_calculator->calculateTotalIncome();
}

double GameController::getTotalExpenses() const
{
    return m_calculator->calculateTotalExpenses();
}

double GameController::getCashFlow() const
{
    return m_calculator->calculateCashFlow();
}

double GameController::getTotalAssets() const
{
    return m_calculator->calculateTotalAssets();
}

double GameController::getTotalLiabilities() const
{
    return m_calculator->calculateTotalLiabilities();
}

double GameController::getNetWorth() const
{
    return m_calculator->calculateNetWorth();
}

double GameController::getPassiveIncome() const
{
    return m_calculator->calculatePassiveIncome();
}

double GameController::getSavingsRate() const
{
    return m_calculator->calculateSavingsRate();
}

double GameController::getFinancialFreedomPercent() const
{
    return m_calculator->calculateFinancialFreedomPercent();
}

QString GameController::getFinancialStatus() const
{
    return m_calculator->getFinancialFreedomStatus();
}

double GameController::getMonthlySalary() const
{
    return m_engine->getMonthlySalary();
}

double GameController::getEmergencyFundTarget() const
{
    QMap<QString, double> data = m_db->getEmergencyFundData();
    return data.value("targetAmount", 0.0);
}

double GameController::getEmergencyFundCurrent() const
{
    QMap<QString, double> data = m_db->getEmergencyFundData();
    return data.value("currentAmount", 0.0);
}

double GameController::getEmergencyFundPercent() const
{
    return m_calculator->calculateEmergencyFundPercent();
}

QString GameController::getEmergencyFundStatus() const
{
    return m_calculator->getEmergencyFundStatus();
}

int GameController::getMonthsPlayed() const
{
    return m_engine->getMonthsPlayed();
}

int GameController::getGoalsAchieved() const
{
    return m_engine->getGoalsAchieved();
}

int GameController::getTotalGoals() const
{
    return m_engine->getTotalGoals();
}

// Formatting
QString GameController::formatCurrency(double amount) const
{
    return m_calculator->formatCurrency(amount);
}

QString GameController::formatPercent(double percent) const
{
    return m_calculator->formatPercent(percent);
}

QString GameController::formatIndianCurrency(double amount) const
{
    return m_calculator->formatIndianCurrency(amount);
}

// Game operations
bool GameController::startNewGame(const QString &playerName, double monthlySalary)
{
    if (validateName(playerName).isEmpty() == false) {
        emit errorOccurred(validateName(playerName));
        return false;
    }
    if (monthlySalary <= 0) {
        emit errorOccurred("Monthly salary must be greater than 0");
        return false;
    }

    bool result = m_engine->startNewGame(playerName, monthlySalary);
    if (result) {
        emitDataChanged();
        emit notification("New game started: " + playerName);
    }
    return result;
}

void GameController::resetGame()
{
    m_engine->resetGame();
    emitDataChanged();
    emit notification("Game reset successfully");
}

bool GameController::nextTurn()
{
    m_engine->nextTurn();
    emitDataChanged();
    return true;
}

void GameController::saveCurrentState()
{
    m_engine->saveCurrentState();
    emit gameStateChanged();
}

// Income operations
bool GameController::addIncome(const QString &date, const QString &source,
                              const QString &category, double amount, bool recurring, const QString &notes)
{
    if (source.isEmpty()) {
        emit errorOccurred("Income source cannot be empty");
        return false;
    }
    if (!m_engine->validateIncomeAmount(amount)) {
        emit errorOccurred("Invalid income amount");
        return false;
    }

    bool result = m_db->addIncome(date, source, category, amount, recurring, notes);
    if (result) {
        emitDataChanged();
        emit notification("Income added: " + source);
    }
    return result;
}

bool GameController::deleteIncome(int id)
{
    bool result = m_db->deleteIncome(id);
    if (result) {
        emitDataChanged();
    }
    return result;
}

// Expense operations
QVariantList GameController::getExpenseCategories() const
{
    QVariantList list;
    QVector<QPair<QString, double>> categories = m_db->getExpenseCategories();
    QVector<QPair<QString, double>> actuals = m_db->getExpenseActuals();

    QMap<QString, double> actualMap;
    for (const auto &p : actuals) {
        actualMap[p.first] = p.second;
    }

    for (const auto &p : categories) {
        QVariantMap map;
        map["name"] = p.first;
        map["budget"] = p.second;
        map["actual"] = actualMap.value(p.first, 0.0);
        map["variance"] = map["actual"].toDouble() - p.second;
        list.append(map);
    }
    return list;
}

bool GameController::updateExpense(const QString &category, double budget, double actual)
{
    if (category.isEmpty()) {
        emit errorOccurred("Category cannot be empty");
        return false;
    }
    if (budget < 0 || actual < 0) {
        emit errorOccurred("Amounts cannot be negative");
        return false;
    }

    bool result = m_db->updateExpenseCategory(category, budget, actual);
    if (result) {
        emitDataChanged();
    }
    return result;
}

void GameController::setFoodExpenseActual(double amount)
{
    m_db->updateExpenseCategory("Food", m_db->getTotalExpenseBudget() * 0.4, amount);
    emitDataChanged();
}

// Daily Expense operations
bool GameController::addDailyExpense(const QString &date, const QString &dayOfWeek,
                                    double food, double other, const QString &description)
{
    if (date.isEmpty()) {
        emit errorOccurred("Date cannot be empty");
        return false;
    }
    if (food < 0 || other < 0) {
        emit errorOccurred("Amounts cannot be negative");
        return false;
    }

    bool result = m_db->addDailyExpense(date, dayOfWeek, food, other, description);
    if (result) {
        m_dailyExpenseModel->setExpenses(m_db->getDailyExpenses());
        emit gameStateChanged();
    }
    return result;
}

// Asset operations
bool GameController::addAsset(const QString &name, const QString &type, double purchaseValue,
                             double currentValue, double monthlyPassiveIncome, double annualReturn)
{
    if (name.isEmpty()) {
        emit errorOccurred("Asset name cannot be empty");
        return false;
    }
    if (!m_engine->validateAssetValue(purchaseValue) || !m_engine->validateAssetValue(currentValue)) {
        emit errorOccurred("Invalid asset value");
        return false;
    }

    bool result = m_db->addAsset(name, type, purchaseValue, currentValue, monthlyPassiveIncome, annualReturn);
    if (result) {
        emitDataChanged();
        emit notification("Asset added: " + name);
    }
    return result;
}

bool GameController::updateAsset(int id, const QString &name, const QString &type,
                                double purchaseValue, double currentValue,
                                double monthlyPassiveIncome, double annualReturn)
{
    if (name.isEmpty()) {
        emit errorOccurred("Asset name cannot be empty");
        return false;
    }

    bool result = m_db->updateAsset(id, name, type, purchaseValue, currentValue, monthlyPassiveIncome, annualReturn);
    if (result) {
        emitDataChanged();
    }
    return result;
}

bool GameController::deleteAsset(int id)
{
    bool result = m_db->deleteAsset(id);
    if (result) {
        emitDataChanged();
    }
    return result;
}

// Liability operations
bool GameController::addLiability(const QString &name, double outstandingBalance,
                                 double monthlyEmi, double interestRate, const QString &dueDate)
{
    if (name.isEmpty()) {
        emit errorOccurred("Liability name cannot be empty");
        return false;
    }
    if (!m_engine->validateLiabilityAmount(outstandingBalance)) {
        emit errorOccurred("Invalid balance amount");
        return false;
    }

    bool result = m_db->addLiability(name, outstandingBalance, monthlyEmi, interestRate, dueDate);
    if (result) {
        emitDataChanged();
        emit notification("Liability added: " + name);
    }
    return result;
}

bool GameController::updateLiability(int id, const QString &name, double outstandingBalance,
                                    double monthlyEmi, double interestRate, const QString &dueDate)
{
    if (name.isEmpty()) {
        emit errorOccurred("Liability name cannot be empty");
        return false;
    }

    bool result = m_db->updateLiability(id, name, outstandingBalance, monthlyEmi, interestRate, dueDate);
    if (result) {
        emitDataChanged();
    }
    return result;
}

bool GameController::deleteLiability(int id)
{
    bool result = m_db->deleteLiability(id);
    if (result) {
        emitDataChanged();
    }
    return result;
}

// Investment operations
bool GameController::addInvestment(const QString &name, const QString &type,
                                  double investedAmount, double currentValue)
{
    if (name.isEmpty()) {
        emit errorOccurred("Investment name cannot be empty");
        return false;
    }
    if (investedAmount < 0 || currentValue < 0) {
        emit errorOccurred("Amounts cannot be negative");
        return false;
    }

    bool result = m_db->addInvestment(name, type, investedAmount, currentValue);
    if (result) {
        emitDataChanged();
        emit notification("Investment added: " + name);
    }
    return result;
}

bool GameController::deleteInvestment(int id)
{
    bool result = m_db->deleteInvestment(id);
    if (result) {
        emitDataChanged();
    }
    return result;
}

// Emergency Fund operations
bool GameController::updateEmergencyFund(double currentAmount)
{
    if (currentAmount < 0) {
        emit errorOccurred("Amount cannot be negative");
        return false;
    }

    double monthlyExpenses = getTotalExpenses();
    bool result = m_db->updateEmergencyFund(monthlyExpenses, currentAmount);
    if (result) {
        emit gameStateChanged();
    }
    return result;
}

// Financial Goal operations
bool GameController::addFinancialGoal(const QString &name, double targetAmount, const QString &targetDate)
{
    if (name.isEmpty()) {
        emit errorOccurred("Goal name cannot be empty");
        return false;
    }
    if (targetAmount <= 0) {
        emit errorOccurred("Target amount must be greater than 0");
        return false;
    }

    bool result = m_db->addFinancialGoal(name, targetAmount, targetDate);
    if (result) {
        m_goalModel->setGoals(m_db->getAllFinancialGoals());
        emit gameStateChanged();
        emit notification("Goal added: " + name);
    }
    return result;
}

bool GameController::updateFinancialGoalProgress(int id, double currentAmount)
{
    if (currentAmount < 0) {
        emit errorOccurred("Amount cannot be negative");
        return false;
    }

    bool result = m_db->updateFinancialGoal(id, currentAmount);
    if (result) {
        m_goalModel->setGoals(m_db->getAllFinancialGoals());
        emit gameStateChanged();
    }
    return result;
}

bool GameController::deleteFinancialGoal(int id)
{
    bool result = m_db->deleteFinancialGoal(id);
    if (result) {
        m_goalModel->setGoals(m_db->getAllFinancialGoals());
        emit gameStateChanged();
    }
    return result;
}

// Charts data
QVariantList GameController::getIncomeVsExpenseData() const
{
    QVariantList result;
    QVariantMap data;
    data["label"] = "Income";
    data["value"] = getTotalIncome();
    result.append(data);
    data["label"] = "Expenses";
    data["value"] = getTotalExpenses();
    result.append(data);
    data["label"] = "Cash Flow";
    data["value"] = getCashFlow();
    result.append(data);
    return result;
}

QVariantList GameController::getAssetBreakdownData() const
{
    QVariantList result;
    QMap<QString, double> breakdown = m_calculator->getAssetBreakdown();

    for (auto it = breakdown.begin(); it != breakdown.end(); ++it) {
        if (it.value() > 0) {
            QVariantMap data;
            data["label"] = it.key();
            data["value"] = it.value();
            result.append(data);
        }
    }
    return result;
}

QVariantList GameController::getMonthlyNetWorthData() const
{
    QVariantList result;
    QVector<QMap<QString, QVariant>> summaries = m_db->getMonthlySummaries();

    // Reverse to get chronological order
    for (int i = summaries.size() - 1; i >= 0; --i) {
        QVariantMap data;
        const auto &row = summaries[i];
        data["month"] = row["month"].toInt();
        data["year"] = row["year"].toInt();
        data["netWorth"] = row["netWorth"].toDouble();
        data["cashFlow"] = row["cashFlow"].toDouble();
        result.append(data);
    }
    return result;
}

QVariantList GameController::getCashFlowTrendData() const
{
    QVariantList result;
    QVector<QMap<QString, QVariant>> summaries = m_db->getMonthlySummaries();

    for (int i = summaries.size() - 1; i >= 0; --i) {
        QVariantMap data;
        const auto &row = summaries[i];
        data["month"] = row["month"].toInt();
        data["year"] = row["year"].toInt();
        data["income"] = row["totalIncome"].toDouble();
        data["expenses"] = row["totalExpenses"].toDouble();
        data["cashFlow"] = row["cashFlow"].toDouble();
        result.append(data);
    }
    return result;
}

QVariantList GameController::getExpenseBreakdownData() const
{
    QVariantList result;
    QMap<QString, double> breakdown = m_calculator->getExpenseBreakdown();

    for (auto it = breakdown.begin(); it != breakdown.end(); ++it) {
        if (it.value() > 0) {
            QVariantMap data;
            data["label"] = it.key();
            data["value"] = it.value();
            result.append(data);
        }
    }
    return result;
}

// Validation
QString GameController::validateAmount(double amount, bool allowZero) const
{
    if (std::isnan(amount) || std::isinf(amount)) {
        return "Please enter a valid number";
    }
    if (!allowZero && amount == 0) {
        return "Amount cannot be zero";
    }
    if (amount < 0) {
        return "Amount cannot be negative";
    }
    if (amount > 99999999.99) {
        return "Amount is too large";
    }
    return "";
}

QString GameController::validateName(const QString &name) const
{
    if (name.isEmpty()) {
        return "Name cannot be empty";
    }
    if (name.length() > 100) {
        return "Name is too long";
    }
    return "";
}

QString GameController::validateDate(const QString &date) const
{
    if (date.isEmpty()) {
        return "Date cannot be empty";
    }
    QDate d = QDate::fromString(date, Qt::ISODate);
    if (!d.isValid()) {
        return "Invalid date format. Use YYYY-MM-DD";
    }
    return "";
}

QStringList GameController::getIncomeCategoryList() const
{
    return QStringList{"Salary", "Business", "Freelance", "Interest", "Dividend", "Rental", "Bonus", "Other"};
}

QStringList GameController::getAssetTypeList() const
{
    return QStringList{"Real Estate", "Stocks", "Mutual Fund", "Gold", "FD", "PPF", "NPS", "SIP", "Business", "Bank Savings", "Other"};
}

QStringList GameController::getInvestmentTypeList() const
{
    return QStringList{"SIP", "Mutual Funds", "Stocks", "Gold", "PPF", "NPS", "Crypto"};
}

// Slots
void GameController::onGameEngineEventOccurred(const QString &description, double amount, bool isPositive)
{
    emit notification(description);
}

void GameController::onGameEngineErrorOccurred(const QString &error)
{
    emit errorOccurred(error);
}

void GameController::onGameEngineTurnChanged()
{
    emit notification("Month advanced: " + getCurrentMonthName());
    emitDataChanged();
}

void GameController::onGameEngineGameFinished(bool won)
{
    if (won) {
        emit notification("🎉 Congratulations! You have achieved Financial Freedom!");
    }
}
