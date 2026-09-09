import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: investmentScreen
    color: "#1a1a2e"

    property var investmentTypes: ["SIP", "Mutual Funds", "Stocks", "Gold", "PPF", "NPS", "Crypto"]

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
                    text: "💼 Investment Tracker"
                    color: "#ecf0f1"
                    font.pixelSize: 24
                    font.bold: true
                }
                Label {
                    text: "Track your investment portfolio"
                    color: "#95a5a6"
                    font.pixelSize: 14
                }
            }

            Item { Layout.fillWidth: true }

            // Portfolio Summary
            ColumnLayout {
                spacing: 2
                Label { text: "Total Portfolio Value"; color: "#7f8c8d"; font.pixelSize: 11 }
                Label {
                    id: portfolioValueLabel
                    property var investments: gameController.investmentModel
                    property double totalInvested: {
                        var total = 0
                        for (var i = 0; i < investments.count; i++) {
                            var item = investments.get(i)
                            if (item) total += (item.investedAmount || 0)
                        }
                        return total
                    }
                    property double currentValue: {
                        var total = 0
                        for (var i = 0; i < investments.count; i++) {
                            var item = investments.get(i)
                            if (item) total += (item.currentValue || 0)
                        }
                        return total
                    }
                    text: "₹" + gameController.formatIndianCurrency(currentValue)
                    color: "#2ecc71"
                    font.pixelSize: 18
                    font.bold: true
                }
            }
        }

        // Add Investment Form
        Rectangle {
            Layout.fillWidth: true
            height: 160
            radius: 12
            color: "#16213e"
            border.color: "#2c3e50"
            border.width: 1

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 16
                spacing: 12

                Label {
                    text: "Add New Investment"
                    color: "#ecf0f1"
                    font.pixelSize: 14
                    font.bold: true
                }

                RowLayout {
                    Layout.fillWidth: true
                    spacing: 12

                    ColumnLayout {
                        spacing: 4
                        Label { text: "Investment Name"; color: "#95a5a6"; font.pixelSize: 11 }
                        TextField {
                            id: investmentNameField
                            placeholderText: "e.g., Axis Bluechip Fund"
                            Layout.preferredWidth: 200
                            background: Rectangle {
                                color: "#0f3460"
                                radius: 6
                            }
                            color: "#ecf0f1"
                        }
                    }

                    ColumnLayout {
                        spacing: 4
                        Label { text: "Type"; color: "#95a5a6"; font.pixelSize: 11 }
                        ComboBox {
                            id: investmentTypeCombo
                            model: investmentScreen.investmentTypes
                            Layout.preferredWidth: 130
                            background: Rectangle {
                                color: "#0f3460"
                                radius: 6
                            }
                            contentItem: Label {
                                text: parent.displayText
                                color: "#ecf0f1"
                            }
                        }
                    }

                    ColumnLayout {
                        spacing: 4
                        Label { text: "Invested Amount (₹)"; color: "#95a5a6"; font.pixelSize: 11 }
                        TextField {
                            id: investmentInvestedField
                            placeholderText: "0"
                            Layout.preferredWidth: 150
                            background: Rectangle {
                                color: "#0f3460"
                                radius: 6
                            }
                            color: "#ecf0f1"
                            validator: DoubleValidator { notation: DoubleValidator.StandardNotation }
                        }
                    }

                    ColumnLayout {
                        spacing: 4
                        Label { text: "Current Value (₹)"; color: "#95a5a6"; font.pixelSize: 11 }
                        TextField {
                            id: investmentCurrentField
                            placeholderText: "0"
                            Layout.preferredWidth: 150
                            background: Rectangle {
                                color: "#0f3460"
                                radius: 6
                            }
                            color: "#ecf0f1"
                            validator: DoubleValidator { notation: DoubleValidator.StandardNotation }
                        }
                    }

                    Item {}

                    Button {
                        text: "Add"
                        Layout.preferredHeight: 40
                        Layout.preferredWidth: 100
                        background: Rectangle {
                            color: parent.hovered ? "#3cd9c4" : "#4ecdc4"
                            radius: 8
                        }
                        contentItem: Label {
                            text: parent.text
                            color: "#1a1a2e"
                            font.bold: true
                            horizontalAlignment: Text.AlignHCenter
                        }
                        onClicked: {
                            var name = investmentNameField.text.trim()
                            var type = investmentTypeCombo.currentValue || investmentScreen.investmentTypes[0]
                            var invested = parseFloat(investmentInvestedField.text) || 0
                            var current = parseFloat(investmentCurrentField.text) || 0

                            if (name === "") {
                                gameController.errorOccurred("Please enter investment name")
                                return
                            }

                            gameController.addInvestment(name, type, invested, current)
                            investmentNameField.text = ""
                            investmentInvestedField.text = ""
                            investmentCurrentField.text = ""
                        }
                    }
                }
            }
        }

        // Investment List
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: 12
            color: "#16213e"
            border.color: "#2c3e50"
            border.width: 1

            ListView {
                id: investmentList
                anchors.fill: parent
                anchors.margins: 16
                model: gameController.investmentModel
                clip: true

                header: Rectangle {
                    width: investmentList.width
                    height: 40
                    color: "#0f3460"
                    radius: 6

                    RowLayout {
                        anchors.fill: parent
                        anchors.leftMargin: 16
                        anchors.rightMargin: 16
                        spacing: 0

                        Label { text: "Name"; color: "#95a5a6"; font.bold: true; Layout.preferredWidth: 200 }
                        Label { text: "Type"; color: "#95a5a6"; font.bold: true; Layout.preferredWidth: 120 }
                        Label { text: "Invested"; color: "#95a5a6"; font.bold: true; Layout.preferredWidth: 140 }
                        Label { text: "Current Value"; color: "#95a5a6"; font.bold: true; Layout.preferredWidth: 140 }
                        Label { text: "Profit/Loss"; color: "#95a5a6"; font.bold: true; Layout.preferredWidth: 140 }
                        Label { text: "%"; color: "#95a5a6"; font.bold: true; Layout.preferredWidth: 80 }
                        Item { Layout.fillWidth: true }
                    }
                }

                delegate: Rectangle {
                    width: investmentList.width
                    height: 50
                    color: "transparent"

                    Rectangle {
                        anchors.fill: parent
                        radius: 4
                        color: index % 2 === 0 ? "transparent" : "#0f3460"
                    }

                    RowLayout {
                        anchors.fill: parent
                        anchors.leftMargin: 16
                        anchors.rightMargin: 16

                        Label { text: name; color: "#ecf0f1"; Layout.preferredWidth: 200 }
                        Label {
                            text: type
                            color: "#3498db"
                            Layout.preferredWidth: 120
                        }
                        Label {
                            text: "₹" + gameController.formatIndianCurrency(investedAmount)
                            color: "#95a5a6"
                            Layout.preferredWidth: 140
                        }
                        Label {
                            text: "₹" + gameController.formatIndianCurrency(currentValue)
                            color: "#2ecc71"
                            font.bold: true
                            Layout.preferredWidth: 140
                        }
                        Label {
                            text: (profitLoss >= 0 ? "+" : "") + "₹" + gameController.formatIndianCurrency(profitLoss)
                            color: profitLoss >= 0 ? "#2ecc71" : "#e74c3c"
                            font.bold: true
                            Layout.preferredWidth: 140
                        }
                        Label {
                            text: gameController.formatPercent(profitLossPercent)
                            color: profitLossPercent >= 0 ? "#2ecc71" : "#e74c3c"
                            Layout.preferredWidth: 80
                        }

                        Button {
                            text: "✕"
                            Layout.preferredWidth: 40
                            background: Rectangle { color: "transparent" }
                            contentItem: Label {
                                text: parent.text
                                color: "#e74c3c"
                            }
                            onClicked: {
                                gameController.deleteInvestment(id)
                            }
                        }
                    }
                }

                Label {
                    anchors.centerIn: parent
                    text: "No investments yet. Start building your portfolio!"
                    color: "#7f8c8d"
                    font.pixelSize: 14
                    visible: gameController.investmentModel.count === 0
                }
            }
        }
    }
}
