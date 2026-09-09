import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "../components"

Rectangle {
    id: financialFreedomScreen
    color: "#1a1a2e"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 24
        spacing: 20

        // Header
        ColumnLayout {
            spacing: 4
            Label {
                text: "🎯 Financial Freedom Tracker"
                color: "#ecf0f1"
                font.pixelSize: 24
                font.bold: true
            }
            Label {
                text: "Financial Freedom % = Passive Income / Monthly Expenses × 100"
                color: "#95a5a6"
                font.pixelSize: 14
            }
        }

        // Main Progress Card
        Rectangle {
            Layout.fillWidth: true
            height: 320
            radius: 12
            color: "#16213e"
            border.color: "#2c3e50"
            border.width: 1

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 30
                spacing: 20

                RowLayout {
                    Layout.fillWidth: true
                    spacing: 8

                    Label { text: "🎯"; font.pixelSize: 32 }
                    Label {
                        text: "Freedom Status"
                        color: "#ecf0f1"
                        font.pixelSize: 18
                        font.bold: true
                        Layout.fillWidth: true
                    }
                    Label {
                        text: gameController.financialStatus
                        color: gameController.financialFreedomPercent >= 100 ? "#2ecc71" : "#4ecdc4"
                        font.pixelSize: 16
                        font.bold: true
                    }
                }

                // Big percentage display
                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 100
                    radius: 8
                    color: "#0f3460"

                    Label {
                        anchors.centerIn: parent
                        text: gameController.formatPercent(gameController.financialFreedomPercent)
                        color: gameController.financialFreedomPercent >= 100 ? "#2ecc71" : "#4ecdc4"
                        font.pixelSize: 48
                        font.bold: true
                    }
                }

                ProgressBar {
                    Layout.fillWidth: true
                    value: gameController.financialFreedomPercent / 100
                    barColor: gameController.financialFreedomPercent >= 100 ? "#2ecc71" : "#4ecdc4"
                    height: 16
                }

                // Numbers
                RowLayout {
                    Layout.fillWidth: true
                    spacing: 16

                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 4
                        Label { text: "Passive Income"; color: "#7f8c8d"; font.pixelSize: 12 }
                        Label {
                            text: "₹" + gameController.formatIndianCurrency(gameController.passiveIncome)
                            color: "#9b59b6"
                            font.pixelSize: 18
                            font.bold: true
                        }
                    }

                    Rectangle { width: 1; height: 40; color: "#2c3e50" }

                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 4
                        Label { text: "Monthly Expenses"; color: "#7f8c8d"; font.pixelSize: 12 }
                        Label {
                            text: "₹" + gameController.formatIndianCurrency(gameController.totalExpenses)
                            color: "#e74c3c"
                            font.pixelSize: 18
                            font.bold: true
                        }
                    }

                    Rectangle { width: 1; height: 40; color: "#2c3e50" }

                    ColumnLayout {
                        Layout.fillWidth: true
                        spacing: 4
                        Label { text: "Gap to Cover"; color: "#7f8c8d"; font.pixelSize: 12 }
                        Label {
                            text: "₹" + gameController.formatIndianCurrency(Math.max(0, gameController.totalExpenses - gameController.passiveIncome))
                            color: "#f39c12"
                            font.pixelSize: 18
                            font.bold: true
                        }
                    }
                }
            }
        }

        // Freedom Scale
        Rectangle {
            Layout.fillWidth: true
            height: 180
            radius: 12
            color: "#16213e"
            border.color: "#2c3e50"
            border.width: 1

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 12

                Label {
                    text: "Freedom Scale"
                    color: "#ecf0f1"
                    font.pixelSize: 16
                    font.bold: true
                }

                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 6

                    RowLayout {
                        spacing: 8
                        Rectangle { width: 16; height: 16; radius: 8; color: "#e74c3c" }
                        Label { text: "0-25%: Just Getting Started"; color: "#ecf0f1"; font.pixelSize: 13 }
                    }
                    RowLayout {
                        spacing: 8
                        Rectangle { width: 16; height: 16; radius: 8; color: "#f39c12" }
                        Label { text: "25-50%: Building Momentum"; color: "#ecf0f1"; font.pixelSize: 13 }
                    }
                    RowLayout {
                        spacing: 8
                        Rectangle { width: 16; height: 16; radius: 8; color: "#3498db" }
                        Label { text: "50-75%: Halfway There"; color: "#ecf0f1"; font.pixelSize: 13 }
                    }
                    RowLayout {
                        spacing: 8
                        Rectangle { width: 16; height: 16; radius: 8; color: "#f1c40f" }
                        Label { text: "75-99%: Almost There"; color: "#ecf0f1"; font.pixelSize: 13 }
                    }
                    RowLayout {
                        spacing: 8
                        Rectangle { width: 16; height: 16; radius: 8; color: "#2ecc71" }
                        Label { text: "100%+: Financial Freedom Achieved!"; color: "#2ecc71"; font.bold: true; font.pixelSize: 13 }
                    }
                }
            }
        }

        // Tip Section
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

                Label { text: "🎓"; font.pixelSize: 28 }

                ColumnLayout {
                    spacing: 4
                    Label {
                        text: "Rich Dad's Definition of Wealth"
                        color: "#f39c12"
                        font.pixelSize: 14
                        font.bold: true
                    }
                    Label {
                        text: "Wealth is measured by time. How long can you survive without working? If your passive income covers your expenses for the rest of your life, you are financially free."
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
