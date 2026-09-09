import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "../components"

Rectangle {
    id: cashFlowScreen
    color: "#1a1a2e"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 24
        spacing: 20

        // Header
        RowLayout {
            Layout.fillWidth: true
            spacing: 16

            ColumnLayout {
                spacing: 4
                Label {
                    text: "🌊 Cash Flow Statement"
                    color: "#ecf0f1"
                    font.pixelSize: 24
                    font.bold: true
                }
                Label {
                    text: "Money in vs money out"
                    color: "#95a5a6"
                    font.pixelSize: 14
                }
            }

            Item { Layout.fillWidth: true }

            // Cash Flow Display
            Rectangle {
                radius: 12
                height: 70
                implicitWidth: cashFlowLabel.implicitWidth + 60
                color: gameController.cashFlow >= 0 ? "#2ecc71" : "#e74c3c"

                ColumnLayout {
                    anchors.centerIn: parent
                    spacing: 2

                    Label {
                        text: "NET CASH FLOW"
                        color: "rgba(255,255,255,0.8)"
                        font.pixelSize: 11
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                    }

                    Label {
                        id: cashFlowLabel
                        text: (gameController.cashFlow >= 0 ? "+" : "") + "₹" + gameController.formatIndianCurrency(gameController.cashFlow)
                        color: "white"
                        font.pixelSize: 24
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                    }
                }
            }
        }

        // Cash Flow Chart
        Rectangle {
            Layout.fillWidth: true
            height: 300
            radius: 12
            color: "#16213e"
            border.color: "#2c3e50"
            border.width: 1

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 16
                spacing: 12

                Label {
                    text: "Cash Flow Trend"
                    color: "#ecf0f1"
                    font.pixelSize: 16
                    font.bold: true
                }

                Item {
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    // Simple bar chart representation
                    RowLayout {
                        anchors.fill: parent
                        spacing: 8

                        // Income bar
                        Rectangle {
                            Layout.fillHeight: true
                            Layout.preferredWidth: parent.width / 2 - 4

                            ColumnLayout {
                                anchors.fill: parent
                                anchors.margins: 8
                                spacing: 8

                                Label {
                                    text: "💰 Income"
                                    color: "#2ecc71"
                                    font.pixelSize: 14
                                    font.bold: true
                                }

                                Item { Layout.fillHeight: true }

                                Rectangle {
                                    Layout.fillWidth: true
                                    Layout.preferredHeight: Math.max(20, (gameController.totalIncome / Math.max(gameController.totalIncome, gameController.totalExpenses)) * (parent.height - 60))
                                    radius: 8
                                    color: "#2ecc71"

                                    anchors.bottom: parent.bottom

                                    Label {
                                        anchors.centerIn: parent
                                        text: "₹" + gameController.formatIndianCurrency(gameController.totalIncome)
                                        color: "white"
                                        font.pixelSize: 12
                                        font.bold: true
                                    }
                                }
                            }
                        }

                        // Expense bar
                        Rectangle {
                            Layout.fillHeight: true
                            Layout.preferredWidth: parent.width / 2 - 4

                            ColumnLayout {
                                anchors.fill: parent
                                anchors.margins: 8
                                spacing: 8

                                Label {
                                    text: "💸 Expenses"
                                    color: "#e74c3c"
                                    font.pixelSize: 14
                                    font.bold: true
                                }

                                Item { Layout.fillHeight: true }

                                Rectangle {
                                    Layout.fillWidth: true
                                    Layout.preferredHeight: Math.max(20, (gameController.totalExpenses / Math.max(gameController.totalIncome, gameController.totalExpenses)) * (parent.height - 60))
                                    radius: 8
                                    color: "#e74c3c"

                                    anchors.bottom: parent.bottom

                                    Label {
                                        anchors.centerIn: parent
                                        text: "₹" + gameController.formatIndianCurrency(gameController.totalExpenses)
                                        color: "white"
                                        font.pixelSize: 12
                                        font.bold: true
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        // Detailed Breakdown
        RowLayout {
            Layout.fillWidth: true
            spacing: 16

            // Income Sources
            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                radius: 12
                color: "#16213e"
                border.color: "#2c3e50"
                border.width: 1

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 16
                    spacing: 12

                    RowLayout {
                        spacing: 8
                        Label { text: "💰"; font.pixelSize: 20 }
                        Label {
                            text: "Income Sources"
                            color: "#ecf0f1"
                            font.pixelSize: 16
                            font.bold: true
                        }
                    }

                    ListView {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        model: gameController.incomeModel
                        clip: true

                        delegate: RowLayout {
                            width: parent.width
                            height: 35
                            spacing: 8

                            Label {
                                text: source
                                color: "#ecf0f1"
                                font.pixelSize: 13
                                Layout.fillWidth: true
                            }
                            Label {
                                text: "₹" + gameController.formatIndianCurrency(amount)
                                color: "#2ecc71"
                                font.bold: true
                            }
                        }

                        Label {
                            anchors.centerIn: parent
                            text: "No income sources"
                            color: "#7f8c8d"
                            visible: gameController.incomeModel.count === 0
                        }
                    }
                }
            }

            // Expense Categories
            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                radius: 12
                color: "#16213e"
                border.color: "#2c3e50"
                border.width: 1

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 16
                    spacing: 12

                    RowLayout {
                        spacing: 8
                        Label { text: "💸"; font.pixelSize: 20 }
                        Label {
                            text: "Expense Categories"
                            color: "#ecf0f1"
                            font.pixelSize: 16
                            font.bold: true
                        }
                    }

                    ListView {
                        id: expenseBreakdown
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        clip: true

                        model: gameController.getExpenseCategories()

                        delegate: RowLayout {
                            width: parent.width
                            height: 35
                            spacing: 8

                            Label {
                                text: modelData.name || ""
                                color: "#ecf0f1"
                                font.pixelSize: 13
                                Layout.fillWidth: true
                            }
                            Label {
                                text: "₹" + gameController.formatIndianCurrency(modelData.actual || 0)
                                color: "#e74c3c"
                                font.bold: true
                            }
                        }

                        Label {
                            anchors.centerIn: parent
                            text: "No expenses"
                            color: "#7f8c8d"
                            visible: expenseBreakdown.count === 0
                        }
                    }
                }
            }
        }

        // Tips Section
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
                spacing: 20

                ColumnLayout {
                    spacing: 4
                    Label { text: "💡"; font.pixelSize: 24 }
                    Label {
                        text: "Rich Dad Tip"
                        color: "#f39c12"
                        font.pixelSize: 14
                        font.bold: true
                    }
                }

                ColumnLayout {
                    spacing: 4
                    Label {
                        text: {
                            if (gameController.cashFlow < 0) {
                                return "Your expenses exceed your income. Focus on reducing expenses or finding additional income sources."
                            } else if (gameController.cashFlow < gameController.totalIncome * 0.1) {
                                return "Your savings rate is low. Try to save at least 20% of your income."
                            } else {
                                return "Great job! You're saving well. Consider investing your savings to build passive income."
                            }
                        }
                        color: "#ecf0f1"
                        font.pixelSize: 13
                        wrapMode: Text.WordWrap
                        Layout.fillWidth: true
                    }
                }
            }
        }
    }
}
