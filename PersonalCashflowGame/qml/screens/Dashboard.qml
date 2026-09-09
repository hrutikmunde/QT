import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "../components"

Rectangle {
    id: dashboard
    color: "#1a1a2e"

    property var cashFlowData: []
    property var expenseData: []

    Component.onCompleted: {
        refreshData()
    }

    function refreshData() {
        cashFlowData = gameController.getIncomeVsExpenseData()
        expenseData = gameController.getExpenseBreakdownData()
    }

    Connections {
        target: gameController
        function onGameStateChanged() {
            refreshData()
        }
    }

    ScrollView {
        anchors.fill: parent
        anchors.margins: 24

        ColumnLayout {
            width: parent.width
            spacing: 20

            // Welcome section
            RowLayout {
                Layout.fillWidth: true
                spacing: 12

                ColumnLayout {
                    spacing: 4
                    Label {
                        text: "Welcome back, " + gameController.playerName + "!"
                        color: "#ecf0f1"
                        font.pixelSize: 24
                        font.bold: true
                    }
                    Label {
                        text: "Track your finances and achieve Financial Freedom"
                        color: "#95a5a6"
                        font.pixelSize: 14
                    }
                }

                Item {
                    Layout.fillWidth: true
                }

                // Financial Freedom Status Badge
                Rectangle {
                    radius: 8
                    height: 40
                    implicitWidth: statusLabel.implicitWidth + 32
                    color: {
                        if (gameController.financialFreedomPercent >= 100) return "#2ecc71"
                        if (gameController.financialFreedomPercent >= 75) return "#f39c12"
                        if (gameController.financialFreedomPercent >= 50) return "#3498db"
                        return "#9b59b6"
                    }

                    Label {
                        id: statusLabel
                        anchors.centerIn: parent
                        text: gameController.financialStatus
                        color: "white"
                        font.pixelSize: 13
                        font.bold: true
                    }
                }
            }

            // Main stats row
            RowLayout {
                Layout.fillWidth: true
                spacing: 16

                StatCard {
                    title: "TOTAL INCOME"
                    value: "₹" + gameController.formatIndianCurrency(gameController.totalIncome)
                    subtitle: "This month"
                    accentColor: "#2ecc71"
                    icon: "💰"
                    Layout.fillWidth: true
                }

                StatCard {
                    title: "TOTAL EXPENSES"
                    value: "₹" + gameController.formatIndianCurrency(gameController.totalExpenses)
                    subtitle: "This month"
                    accentColor: "#e74c3c"
                    icon: "💸"
                    Layout.fillWidth: true
                }

                StatCard {
                    title: "CASH FLOW"
                    value: "₹" + gameController.formatIndianCurrency(gameController.cashFlow)
                    subtitle: gameController.cashFlow >= 0 ? "Positive" : "Negative"
                    accentColor: gameController.cashFlow >= 0 ? "#4ecdc4" : "#e74c3c"
                    icon: "📊"
                    Layout.fillWidth: true
                }

                StatCard {
                    title: "SAVINGS RATE"
                    value: gameController.formatPercent(gameController.savingsRate)
                    subtitle: gameController.getSavingsStatus()
                    accentColor: "#f39c12"
                    icon: "💹"
                    Layout.fillWidth: true
                }
            }

            // Second row of stats
            RowLayout {
                Layout.fillWidth: true
                spacing: 16

                StatCard {
                    title: "NET WORTH"
                    value: "₹" + gameController.formatIndianCurrency(gameController.netWorth)
                    subtitle: "Assets - Liabilities"
                    accentColor: "#3498db"
                    icon: "🏦"
                    Layout.fillWidth: true
                }

                StatCard {
                    title: "PASSIVE INCOME"
                    value: "₹" + gameController.formatIndianCurrency(gameController.passiveIncome)
                    subtitle: "Monthly"
                    accentColor: "#9b59b6"
                    icon: "📈"
                    Layout.fillWidth: true
                }

                StatCard {
                    title: "TOTAL ASSETS"
                    value: "₹" + gameController.formatIndianCurrency(gameController.totalAssets)
                    subtitle: "Current value"
                    accentColor: "#2ecc71"
                    icon: "🏠"
                    Layout.fillWidth: true
                }

                StatCard {
                    title: "TOTAL LIABILITIES"
                    value: "₹" + gameController.formatIndianCurrency(gameController.totalLiabilities)
                    subtitle: "Outstanding"
                    accentColor: "#e74c3c"
                    icon: "🏋️"
                    Layout.fillWidth: true
                }
            }

            // Financial Freedom Progress Section
            Rectangle {
                Layout.fillWidth: true
                height: 140
                radius: 12
                color: "#16213e"
                border.color: "#2c3e50"
                border.width: 1

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 20
                    spacing: 12

                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 8

                        Label {
                            text: "🎯"
                            font.pixelSize: 24
                        }

                        Label {
                            text: "Financial Freedom Progress"
                            color: "#ecf0f1"
                            font.pixelSize: 18
                            font.bold: true
                            Layout.fillWidth: true
                        }

                        Label {
                            text: gameController.formatPercent(gameController.financialFreedomPercent)
                            color: "#4ecdc4"
                            font.pixelSize: 24
                            font.bold: true
                        }
                    }

                    ProgressBar {
                        Layout.fillWidth: true
                        value: gameController.financialFreedomPercent / 100
                        barColor: "#4ecdc4"
                        height: 16
                    }

                    Label {
                        text: "Goal: Passive Income ≥ Monthly Expenses (₹" + gameController.formatIndianCurrency(gameController.totalExpenses) + ")"
                        color: "#95a5a6"
                        font.pixelSize: 12
                    }
                }
            }

            // Charts section
            RowLayout {
                Layout.fillWidth: true
                spacing: 16

                // Income vs Expense Chart
                Rectangle {
                    Layout.fillWidth: true
                    Layout.minimumWidth: 300
                    height: 300
                    radius: 12
                    color: "#16213e"
                    border.color: "#2c3e50"
                    border.width: 1

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 16
                        spacing: 8

                        Label {
                            text: "💵 Income vs Expenses"
                            color: "#ecf0f1"
                            font.pixelSize: 16
                            font.bold: true
                        }

                        Item {
                            Layout.fillWidth: true
                            Layout.fillHeight: true

                            RowLayout {
                                anchors.fill: parent
                                spacing: 20

                                ColumnLayout {
                                    Layout.fillHeight: true
                                    Layout.alignment: Qt.AlignHCenter
                                    spacing: 8

                                    Rectangle {
                                        width: 100
                                        height: Math.max(20, incomeBar.height)
                                        radius: 6
                                        color: "#2ecc71"
                                        Label {
                                            anchors.centerIn: parent
                                            text: "₹" + gameController.formatIndianCurrency(gameController.totalIncome)
                                            color: "white"
                                            font.pixelSize: 11
                                            font.bold: true
                                        }
                                        property real heightRatio: gameController.totalIncome > 0
                                                       ? Math.min(gameController.totalIncome / Math.max(gameController.totalIncome, gameController.totalExpenses), 1)
                                                       : 0
                                        property real height: parent.height * heightRatio
                                    }

                                    Label {
                                        text: "Income"
                                        color: "#2ecc71"
                                        font.pixelSize: 12
                                        font.bold: true
                                    }
                                }

                                ColumnLayout {
                                    Layout.fillHeight: true
                                    Layout.alignment: Qt.AlignHCenter
                                    spacing: 8

                                    Rectangle {
                                        width: 100
                                        height: Math.max(20, expenseBar.height)
                                        radius: 6
                                        color: "#e74c3c"
                                        Label {
                                            anchors.centerIn: parent
                                            text: "₹" + gameController.formatIndianCurrency(gameController.totalExpenses)
                                            color: "white"
                                            font.pixelSize: 11
                                            font.bold: true
                                        }
                                        property real heightRatio: gameController.totalExpenses > 0
                                                       ? Math.min(gameController.totalExpenses / Math.max(gameController.totalIncome, gameController.totalExpenses), 1)
                                                       : 0
                                        property real height: parent.height * heightRatio
                                    }

                                    Label {
                                        text: "Expenses"
                                        color: "#e74c3c"
                                        font.pixelSize: 12
                                        font.bold: true
                                    }
                                }
                            }
                        }
                    }
                }

                // Goals Progress
                Rectangle {
                    Layout.fillWidth: true
                    Layout.minimumWidth: 300
                    height: 300
                    radius: 12
                    color: "#16213e"
                    border.color: "#2c3e50"
                    border.width: 1

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 16
                        spacing: 12

                        RowLayout {
                            Layout.fillWidth: true
                            spacing: 8

                            Label {
                                text: "🏆"
                                font.pixelSize: 20
                            }

                            Label {
                                text: "Goals Progress"
                                color: "#ecf0f1"
                                font.pixelSize: 16
                                font.bold: true
                                Layout.fillWidth: true
                            }

                            Label {
                                text: gameController.goalsAchieved + "/" + gameController.totalGoals
                                color: "#f39c12"
                                font.pixelSize: 14
                                font.bold: true
                            }
                        }

                        ListView {
                            id: goalsList
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            model: gameController.goalModel
                            clip: true

                            delegate: Rectangle {
                                width: goalsList.width
                                height: 50
                                color: "transparent"

                                ColumnLayout {
                                    anchors.fill: parent
                                    anchors.margins: 4
                                    spacing: 2

                                    RowLayout {
                                        Layout.fillWidth: true
                                        spacing: 8

                                        Label {
                                            text: goalName
                                            color: "#ecf0f1"
                                            font.pixelSize: 13
                                            Layout.fillWidth: true
                                        }

                                        Label {
                                            text: gameController.formatPercent(progressPercent)
                                            color: progressPercent >= 100 ? "#2ecc71" : "#95a5a6"
                                            font.pixelSize: 12
                                            font.bold: true
                                        }
                                    }

                                    ProgressBar {
                                        Layout.fillWidth: true
                                        value: progressPercent / 100
                                        barColor: progressPercent >= 100 ? "#2ecc71" : "#4ecdc4"
                                        height: 6
                                    }
                                }
                            }
                        }
                    }
                }
            }

            // Emergency Fund Progress
            Rectangle {
                Layout.fillWidth: true
                height: 100
                radius: 12
                color: "#16213e"
                border.color: "#2c3e50"
                border.width: 1

                RowLayout {
                    anchors.fill: parent
                    anchors.margins: 20
                    spacing: 30

                    ColumnLayout {
                        spacing: 4

                        Label {
                            text: "🛡️ Emergency Fund"
                            color: "#ecf0f1"
                            font.pixelSize: 16
                            font.bold: true
                        }

                        Label {
                            text: gameController.emergencyFundStatus
                            color: "#95a5a6"
                            font.pixelSize: 12
                        }
                    }

                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 4

                        RowLayout {
                            Layout.fillWidth: true
                            Label {
                                text: "₹" + gameController.formatIndianCurrency(gameController.emergencyFundCurrent)
                                color: "#4ecdc4"
                                font.pixelSize: 18
                                font.bold: true
                            }
                            Label {
                                text: " / ₹" + gameController.formatIndianCurrency(gameController.emergencyFundTarget)
                                color: "#95a5a6"
                                font.pixelSize: 14
                            }
                        }

                        ProgressBar {
                            Layout.fillWidth: true
                            value: gameController.emergencyFundPercent / 100
                            barColor: gameController.emergencyFundPercent >= 100 ? "#2ecc71" : "#f39c12"
                            height: 10
                        }
                    }

                    Label {
                        text: gameController.formatPercent(gameController.emergencyFundPercent)
                        color: "#4ecdc4"
                        font.pixelSize: 20
                        font.bold: true
                    }
                }
            }
        }
    }
}
