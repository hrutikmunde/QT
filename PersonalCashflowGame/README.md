# Personal Cashflow Game - India

A professional desktop application built with Qt 6 and C++ for tracking personal finances and achieving financial freedom, inspired by "Rich Dad Poor Dad" principles.

## 📋 Overview

This application helps you:
- Track monthly income and expenses
- Monitor assets that generate passive income
- Manage liabilities and debts
- Plan for financial goals
- Build emergency funds (6 months expenses)
- Achieve "Financial Freedom" (passive income ≥ expenses)

## 🎮 Game Concept

Based on Robert Kiyosaki's "Rich Dad Poor Dad" principles:
- **Assets**: Things that put money in your pocket
- **Liabilities**: Things that take money out of your pocket
- **Financial Freedom**: When passive income covers all expenses

### Win Condition
Achieve **100% Financial Freedom** when your passive income equals or exceeds your monthly expenses.

## ✨ Features

### Core Features
- **Dashboard**: Real-time financial overview with key metrics
- **Income Tracker**: Log salary, business, freelance, and other income sources
- **Expense Tracker**: Budget vs actual expenses with variance analysis
- **Daily Tracker**: Day-by-day expense logging
- **Assets Manager**: Track investments generating passive income
- **Liabilities Manager**: Monitor loans and debts
- **Investment Tracker**: Monitor portfolio performance
- **Emergency Fund Planner**: 6-month expense buffer planning
- **Financial Freedom Tracker**: Progress toward passive income goals
- **Goal Planner**: Set and track financial targets

### Financial Calculations (Excel-to-C++ Mapping)

| Excel Reference | Formula | C++ Implementation |
|---------------|---------|-------------------|
| Dashboard!B6 | B4 - B5 | `calculateCashFlow()` |
| Dashboard!B11 | IFERROR(B6/B4, 0) | `calculateSavingsRate()` |
| Dashboard!B10 | B8 - B9 | `calculateNetWorth()` |
| Dashboard!B12 | Assets!E24 | `calculatePassiveIncome()` |
| FF Tracker!B6 | IFERROR(Passive/Expenses, 0) | `calculateFinancialFreedomPercent()` |
| Emergency!B7 | MAX(B5-B6, 0) | `calculateEmergencyFundPercent()` |

### Status Thresholds

**Financial Freedom Status:**
- 0-25%: Just Getting Started
- 25-50%: Building Momentum
- 50-75%: Halfway There
- 75-99%: Almost There
- 100%+: Financial Freedom Achieved!

**Savings Rate:**
- Excellent: ≥20%
- Good: 10-20%
- Fair: 5-10%
- Needs Improvement: <5%

## 🏗️ Architecture

```
PersonalCashflowGame/
├── CMakeLists.txt
├── README.md
├── src/
│   ├── main.cpp
│   ├── models/
│   │   ├── Player.h/cpp
│   │   ├── Transaction.h/cpp
│   │   ├── Asset.h/cpp
│   │   ├── Liability.h/cpp
│   │   ├── GameState.h/cpp
│   │   ├── DailyExpense.h/cpp
│   │   ├── Investment.h/cpp
│   │   └── FinancialGoal.h/cpp
│   ├── services/
│   │   ├── DatabaseManager.h/cpp
│   │   ├── FinancialCalculator.h/cpp
│   │   └── GameEngine.h/cpp
│   └── controllers/
│       └── GameController.h/cpp
├── qml/
│   ├── Main.qml
│   ├── screens/
│   │   ├── Dashboard.qml
│   │   ├── IncomeScreen.qml
│   │   ├── ExpenseScreen.qml
│   │   ├── DailyTrackerScreen.qml
│   │   ├── AssetsScreen.qml
│   │   ├── LiabilitiesScreen.qml
│   │   ├── CashFlowScreen.qml
│   │   ├── InvestmentScreen.qml
│   │   ├── EmergencyFundScreen.qml
│   │   ├── FinancialFreedomScreen.qml
│   │   ├── GoalPlannerScreen.qml
│   │   └── GameOverScreen.qml
│   └── components/
│       ├── HeaderBar.qml
│       ├── Sidebar.qml
│       ├── SidebarItem.qml
│       ├── StatCard.qml
│       ├── ProgressBar.qml
│       ├── BarChartCard.qml
│       └── LineChartCard.qml
├── database/
│   └── schema.sql
├── tests/
│   ├── test_financialcalculator.cpp
│   └── test_gameengine.cpp
└── resources/
    └── resources.qrc
```

## 🛠️ Technology Stack

- **Qt 6**: Core framework
- **C++20**: Programming language
- **Qt Quick/QML**: User interface
- **Qt Charts**: Data visualization
- **SQLite**: Persistent storage (via Qt SQL)
- **CMake**: Build system

## 💾 Database Schema

### Core Tables
- `game_state`: Player info and game progress
- `income`: Income sources and amounts
- `expenses`: Expense categories with budget/actual
- `daily_expenses`: Day-by-day spending
- `assets`: Investments and passive income sources
- `liabilities`: Loans and debts
- `investments`: Portfolio tracking
- `financial_goals`: Goal planning
- `emergency_fund`: Emergency fund status
- `monthly_summary`: Historical tracking

## 📊 Indian Currency Formatting

Uses proper Indian number system:
- 1,000 = 1,000
- 10,000 = 10,000
- 1,00,000 = 1 Lakh
- 10,00,000 = 10 Lakhs
- 1,00,00,000 = 1 Crore

Example: ₹15,075 → ₹15,075, ₹1,50,000

## 🔨 Build Instructions

### Prerequisites
On Ubuntu/Debian, install Qt 6 development packages:
```bash
sudo apt-get update
sudo apt-get install -y qt6-qmltooling qt6-qml-dev qt6-quick-dev qt6-quickcontrols2-dev qt6-charts-dev
sudo apt-get install -y qt6-base-dev qtcreator
```

Or use Qt Online Installer from https://www.qt.io/download-qt-installer

Required packages:
- Qt 6.5+ (Qt Creator recommended)
- CMake 3.16+
- C++20 compatible compiler (GCC 11+, Clang 14+, MSVC 2022+)
- Qt6::Core, Qt6::Gui, Qt6::Qml, Qt6::Quick
- Qt6::QuickControls2, Qt6::Sql, Qt6::Charts

### Build with Qt Creator
1. Open `CMakeLists.txt` in Qt Creator
2. Configure kit with Qt 6.x
3. Build project (Ctrl+B)
4. Run (F5)

### Build with CMake CLI
```bash
cd PersonalCashflowGame
mkdir build
cd build
cmake ..
cmake --build . --parallel
./PersonalCashflowGame
```

### Build Tests
```bash
cd build
ctest
```

## 🎯 Excel Data Reference

Based on `Personal_Cashflow_Game_India.xlsx` with sample data:

| Metric | Excel Value | Description |
|--------|-------------|-------------|
| Monthly Salary | ₹13,850 | Base salary |
| Bonus | ₹200 | One-time bonus |
| Total Income | ₹15,075 | Sum of all income |
| Food (Actual) | ₹6,520 | From DailyTracker |
| Total Expenses | ₹13,858 | All expenses |
| Cash Flow | ₹1,217 | Income - Expenses |
| Savings Rate | 8.07% | Cash Flow / Income |
| Total Assets | ₹0 | No assets yet |
| Total Liabilities | ₹0 | No debts |
| Net Worth | ₹0 | Assets - Liabilities |
| Passive Income | ₹0 | From assets |
| FF Percent | 0% | Not yet started |

## 📱 Screens

1. **Dashboard**: Financial overview with charts
2. **Income**: Add and track income sources
3. **Expenses**: Budget vs actual with categories
4. **Daily Tracker**: Day-by-day expense log
5. **Assets**: Passive income investments
6. **Liabilities**: Debts and EMIs
7. **Investments**: Portfolio tracking
8. **Cash Flow**: Money in vs money out
9. **Emergency Fund**: 6-month safety net
10. **Financial Freedom**: Progress tracker
11. **Goal Planner**: Financial targets
12. **Game Over**: Achievement celebration

## 🧪 Testing

Unit tests verify Excel-derived calculations:

```cpp
// Test Cash Flow calculation
// Excel: B4-B5 = 15075-13858 = 1217
void TestFinancialCalculator::testCalculateCashFlow()
{
    double expected = 1217.0;
    double actual = m_calculator->calculateCashFlow();
    QVERIFY2(qAbs(expected - actual) < 0.01, "Cash Flow mismatch");
}
```

## 🎨 UI Design

- Dark theme with professional styling
- Indian rupee (₹) currency throughout
- Responsive sidebar navigation
- Color-coded metrics (green=positive, red=negative)
- Progress bars for goals and freedom

## 📋 Known Assumptions

1. Default monthly salary: ₹20,000
2. Emergency fund target: 6 months expenses
3. Financial freedom: passive income ≥ expenses
4. No multiplayer or cloud sync
5. Data stored locally in SQLite

## 🔮 Future Improvements

- [ ] Import data from Excel
- [ ] Export reports to PDF
- [ ] Investment recommendations
- [ ] Debt payoff strategies
- [ ] Tax planning module
- [ ] Multi-language support
- [ ] Cloud backup/sync
- [ ] Mobile companion app

## 📄 License

This project is for educational purposes.

## 🙏 Acknowledgments

- Robert Kiyosaki - "Rich Dad Poor Dad" inspiration
- Personal_Cashflow_Game_India.xlsx - Source data reference

---

**Built with ❤️ for personal finance tracking in India**
