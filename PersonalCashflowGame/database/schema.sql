-- Personal Cashflow Game Database Schema
-- Based on Personal_Cashflow_Game_India.xlsx

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
    category TEXT NOT NULL CHECK(category IN ('Salary', 'Business', 'Freelance', 'Interest', 'Dividend', 'Rental', 'Bonus', 'Other')),
    amount REAL NOT NULL,
    is_recurring INTEGER NOT NULL DEFAULT 0 CHECK(is_recurring IN (0, 1)),
    notes TEXT,
    created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
);

-- Expense Categories Table (predefined)
CREATE TABLE IF NOT EXISTS expense_categories (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL UNIQUE,
    budget_amount REAL NOT NULL DEFAULT 0,
    is_active INTEGER NOT NULL DEFAULT 1 CHECK(is_active IN (0, 1))
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

-- Daily Expenses Table (from DailyTracker sheet)
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
    investment_type TEXT NOT NULL CHECK(investment_type IN ('Real Estate', 'Stocks', 'Mutual Fund', 'Gold', 'FD', 'PPF', 'NPS', 'SIP', 'Business', 'Bank Savings', 'Other')),
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
    investment_type TEXT NOT NULL CHECK(investment_type IN ('SIP', 'Mutual Funds', 'Stocks', 'Gold', 'PPF', 'NPS', 'Crypto')),
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
    status TEXT NOT NULL DEFAULT 'Keep Building' CHECK(status IN ('Keep Building', 'Halfway There', 'Fully Funded!')),
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
    is_achieved INTEGER NOT NULL DEFAULT 0 CHECK(is_achieved IN (0, 1)),
    created_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
    updated_at TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP
);

-- Monthly Summary Table (for tracking progress)
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
