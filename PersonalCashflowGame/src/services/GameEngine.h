#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QMap>

class DatabaseManager;
class FinancialCalculator;
class GameState;

class GameEngine : public QObject
{
    Q_OBJECT

public:
    explicit GameEngine(QObject *parent = nullptr);

    // Game lifecycle
    bool startNewGame(const QString &playerName, double monthlySalary);
    void resetGame();
    bool loadGame();

    // Game progression
    bool nextTurn();
    bool processMonth();
    void saveCurrentState();

    // Game events
    void processTransactionEvent(const QString &type, double amount, const QString &description);
    void processAssetChange(const QString &assetName, double valueChange, bool isGain);
    void processLiabilityPayoff(double amount, const QString &liabilityName);

    // Win/lose conditions
    bool checkWinCondition() const;
    bool checkLoseCondition() const;
    QString getGameStatus() const;

    // Game state
    GameState* getGameState() const;
    int getCurrentMonth() const;
    int getCurrentYear() const;
    QString getPlayerName() const;
    double getMonthlySalary() const;

    // Statistics
    int getMonthsPlayed() const;
    double getTotalEarnings() const;
    double getTotalSpending() const;
    int getGoalsAchieved() const;
    int getTotalGoals() const;

    // Validation
    bool validateIncomeAmount(double amount) const;
    bool validateExpenseAmount(double amount) const;
    bool validateAssetValue(double value) const;
    bool validateLiabilityAmount(double amount) const;

    // Random events
    QString getRandomExpense() const;
    QString getRandomIncome() const;
    QString getRandomOpportunity() const;

signals:
    void gameStateChanged();
    void turnChanged();
    void gameFinished(bool won);
    void eventOccurred(const QString &description, double amount, bool isPositive);
    void errorOccurred(const QString &error);

private:
    DatabaseManager &m_db;
    FinancialCalculator *m_calculator;
    GameState *m_gameState;
    int m_initialMonth;
    int m_initialYear;

    void initializeGameState();
    void checkAndEmitEvents();
    QString getFinancialStatusText() const;
};

#endif // GAMEENGINE_H
