import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: incomeScreen
    color: "#1a1a2e"

    property var incomeCategories: ["Salary", "Business", "Freelance", "Interest", "Dividend", "Rental", "Bonus", "Other"]

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
                    text: "💰 Income Tracker"
                    color: "#ecf0f1"
                    font.pixelSize: 24
                    font.bold: true
                }
                Label {
                    text: "Log all your income sources"
                    color: "#95a5a6"
                    font.pixelSize: 14
                }
            }

            Item { Layout.fillWidth: true }

            // Total Income Display
            Rectangle {
                radius: 8
                height: 50
                implicitWidth: totalIncomeLabel.implicitWidth + 40
                color: "#2ecc71"

                Label {
                    id: totalIncomeLabel
                    anchors.centerIn: parent
                    text: "Total: ₹" + gameController.formatIndianCurrency(gameController.totalIncome)
                    color: "white"
                    font.pixelSize: 16
                    font.bold: true
                }
            }
        }

        // Add Income Form
        Rectangle {
            Layout.fillWidth: true
            height: 180
            radius: 12
            color: "#16213e"
            border.color: "#2c3e50"
            border.width: 1

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 16
                spacing: 12

                Label {
                    text: "Add New Income"
                    color: "#ecf0f1"
                    font.pixelSize: 14
                    font.bold: true
                }

                RowLayout {
                    Layout.fillWidth: true
                    spacing: 12

                    ColumnLayout {
                        spacing: 4
                        Label { text: "Source"; color: "#95a5a6"; font.pixelSize: 11 }
                        TextField {
                            id: incomeSourceField
                            placeholderText: "e.g., Freelance Project"
                            Layout.preferredWidth: 200
                            background: Rectangle {
                                color: "#0f3460"
                                radius: 6
                                border.color: parent.activeFocus ? "#4ecdc4" : "#2c3e50"
                            }
                            color: "#ecf0f1"
                        }
                    }

                    ColumnLayout {
                        spacing: 4
                        Label { text: "Category"; color: "#95a5a6"; font.pixelSize: 11 }
                        ComboBox {
                            id: incomeCategoryCombo
                            model: incomeScreen.incomeCategories
                            Layout.preferredWidth: 150
                            background: Rectangle {
                                color: "#0f3460"
                                radius: 6
                                border.color: parent.activeFocus ? "#4ecdc4" : "#2c3e50"
                            }
                            contentItem: Label {
                                text: parent.displayText
                                color: "#ecf0f1"
                            }
                        }
                    }

                    ColumnLayout {
                        spacing: 4
                        Label { text: "Amount (₹)"; color: "#95a5a6"; font.pixelSize: 11 }
                        TextField {
                            id: incomeAmountField
                            placeholderText: "0"
                            Layout.preferredWidth: 150
                            background: Rectangle {
                                color: "#0f3460"
                                radius: 6
                                border.color: parent.activeFocus ? "#4ecdc4" : "#2c3e50"
                            }
                            color: "#ecf0f1"
                            validator: DoubleValidator { notation: DoubleValidator.StandardNotation }
                        }
                    }

                    ColumnLayout {
                        spacing: 4
                        Label { text: "Recurring?"; color: "#95a5a6"; font.pixelSize: 11 }
                        CheckBox {
                            id: incomeRecurringCheck
                            text: "Yes"
                            Layout.preferredWidth: 100
                            contentItem: Label {
                                text: parent.text
                                color: "#ecf0f1"
                            }
                            indicator: Rectangle {
                                width: 18
                                height: 18
                                radius: 4
                                color: "#0f3460"
                                border.color: parent.checked ? "#4ecdc4" : "#2c3e50"
                                Rectangle {
                                    anchors.centerIn: parent
                                    width: 10
                                    height: 10
                                    radius: 2
                                    color: "#4ecdc4"
                                    visible: parent.parent.checked
                                }
                            }
                        }
                    }

                    Item {}

                    Button {
                        text: "Add Income"
                        Layout.preferredHeight: 40
                        Layout.preferredWidth: 120
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
                            var source = incomeSourceField.text.trim()
                            var category = incomeCategoryCombo.currentValue || incomeScreen.incomeCategories[0]
                            var amount = parseFloat(incomeAmountField.text)

                            if (source === "") {
                                gameController.errorOccurred("Please enter income source")
                                return
                            }
                            if (isNaN(amount) || amount <= 0) {
                                gameController.errorOccurred("Please enter valid amount")
                                return
                            }

                            var date = new Date().toISOString().split('T')[0]
                            gameController.addIncome(date, source, category, amount,
                                                    incomeRecurringCheck.checked, "")
                            incomeSourceField.text = ""
                            incomeAmountField.text = ""
                        }
                    }
                }
            }
        }

        // Income List
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

                Label {
                    text: "Income History"
                    color: "#ecf0f1"
                    font.pixelSize: 14
                    font.bold: true
                }

                ListView {
                    id: incomeList
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    model: gameController.incomeModel
                    clip: true

                    header: Rectangle {
                        width: incomeList.width
                        height: 40
                        color: "#0f3460"
                        radius: 6

                        RowLayout {
                            anchors.fill: parent
                            anchors.leftMargin: 16
                            anchors.rightMargin: 16
                            spacing: 0

                            Label { text: "Date"; color: "#95a5a6"; font.bold: true; Layout.preferredWidth: 100 }
                            Label { text: "Source"; color: "#95a5a6"; font.bold: true; Layout.fillWidth: true }
                            Label { text: "Category"; color: "#95a5a6"; font.bold: true; Layout.preferredWidth: 120 }
                            Label { text: "Amount"; color: "#95a5a6"; font.bold: true; Layout.preferredWidth: 120 }
                            Label { text: "Recurring"; color: "#95a5a6"; font.bold: true; Layout.preferredWidth: 80 }
                            Item { Layout.preferredWidth: 50 }
                        }
                    }

                    delegate: Rectangle {
                        width: incomeList.width
                        height: 50
                        color: "transparent"

                        Rectangle {
                            anchors.fill: parent
                            anchors.rightMargin: 0
                            radius: 4
                            color: index % 2 === 0 ? "transparent" : "#0f3460"
                        }

                        RowLayout {
                            anchors.fill: parent
                            anchors.leftMargin: 16
                            anchors.rightMargin: 16

                            Label { text: date; color: "#ecf0f1"; Layout.preferredWidth: 100 }
                            Label { text: source; color: "#ecf0f1"; Layout.fillWidth: true }
                            Label {
                                text: category
                                color: {
                                    if (category === "Salary") return "#3498db"
                                    if (category === "Bonus") return "#f39c12"
                                    if (category === "Business" || category === "Freelance") return "#9b59b6"
                                    return "#95a5a6"
                                }
                                Layout.preferredWidth: 120
                            }
                            Label {
                                text: "₹" + gameController.formatIndianCurrency(amount)
                                color: "#2ecc71"
                                font.bold: true
                                Layout.preferredWidth: 120
                            }
                            Label {
                                text: recurring ? "✓" : "—"
                                color: recurring ? "#2ecc71" : "#7f8c8d"
                                Layout.preferredWidth: 80
                            }

                            Button {
                                text: "✕"
                                Layout.preferredWidth: 40
                                background: Rectangle {
                                    color: "transparent"
                                }
                                contentItem: Label {
                                    text: parent.text
                                    color: "#e74c3c"
                                    horizontalAlignment: Text.AlignHCenter
                                }
                                onClicked: {
                                    gameController.deleteIncome(id)
                                }
                            }
                        }
                    }

                    model: gameController.incomeModel

                    Label {
                        anchors.centerIn: parent
                        text: "No income recorded yet"
                        color: "#7f8c8d"
                        font.pixelSize: 14
                        visible: gameController.incomeModel.count === 0
                    }
                }
            }
        }
    }
}
