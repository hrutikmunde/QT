import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: expenseScreen
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
                    text: "💸 Expense Tracker"
                    color: "#ecf0f1"
                    font.pixelSize: 24
                    font.bold: true
                }
                Label {
                    text: "Track your monthly expenses vs budget"
                    color: "#95a5a6"
                    font.pixelSize: 14
                }
            }

            Item { Layout.fillWidth: true }

            // Variance Display
            Rectangle {
                radius: 8
                height: 50
                implicitWidth: varianceLabel.implicitWidth + 40
                color: {
                    var variance = gameController.totalExpenses - gameController.getExpenseCategories()[0]?.budget || 0
                    return variance > 0 ? "#e74c3c" : "#2ecc71"
                }

                Label {
                    id: varianceLabel
                    anchors.centerIn: parent
                    property var categories: gameController.getExpenseCategories()
                    property double totalBudget: {
                        var total = 0
                        for (var i = 0; i < categories.length; i++) total += categories[i].budget
                        return total
                    }
                    property double variance: gameController.totalExpenses - totalBudget
                    text: "Variance: " + (variance >= 0 ? "+" : "") + "₹" + gameController.formatIndianCurrency(variance)
                    color: "white"
                    font.pixelSize: 16
                    font.bold: true
                }
            }
        }

        // Expense Categories Grid
        GridView {
            id: expenseGrid
            Layout.fillWidth: true
            Layout.fillHeight: true
            cellWidth: 280
            cellHeight: 160
            clip: true

            model: ListModel {
                id: expenseModel
                ListElement {
                    name: "Rent/Family Contribution"
                    icon: "🏠"
                    defaultBudget: 6000
                }
                ListElement {
                    name: "Food"
                    icon: "🍔"
                    defaultBudget: 4500
                }
                ListElement {
                    name: "Transport"
                    icon: "🚌"
                    defaultBudget: 1200
                }
                ListElement {
                    name: "Mobile & Internet"
                    icon: "📱"
                    defaultBudget: 300
                }
                ListElement {
                    name: "Electricity"
                    icon: "💡"
                    defaultBudget: 0
                }
                ListElement {
                    name: "Entertainment"
                    icon: "🎬"
                    defaultBudget: 1000
                }
                ListElement {
                    name: "Shopping"
                    icon: "🛍️"
                    defaultBudget: 500
                }
                ListElement {
                    name: "Medical"
                    icon: "🏥"
                    defaultBudget: 0
                }
                ListElement {
                    name: "Insurance"
                    icon: "🛡️"
                    defaultBudget: 500
                }
                ListElement {
                    name: "Miscellaneous"
                    icon: "📦"
                    defaultBudget: 0
                }
            }

            delegate: Rectangle {
                width: expenseGrid.cellWidth - 10
                height: expenseGrid.cellHeight - 10
                radius: 12
                color: "#16213e"
                border.color: "#2c3e50"
                border.width: 1

                property var categoryData: {
                    var categories = gameController.getExpenseCategories()
                    for (var i = 0; i < categories.length; i++) {
                        if (categories[i].name === name) return categories[i]
                    }
                    return { name: name, budget: defaultBudget, actual: 0 }
                }

                property double budget: categoryData.budget || defaultBudget
                property double actual: categoryData.actual || 0
                property double variance: actual - budget

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 16
                    spacing: 8

                    RowLayout {
                        Layout.fillWidth: true

                        Label {
                            text: icon
                            font.pixelSize: 24
                        }

                        ColumnLayout {
                            spacing: 2
                            Label {
                                text: name
                                color: "#ecf0f1"
                                font.pixelSize: 14
                                font.bold: true
                            }
                            Label {
                                text: "Budget: ₹" + gameController.formatIndianCurrency(budget)
                                color: "#7f8c8d"
                                font.pixelSize: 11
                            }
                        }

                        Item { Layout.fillWidth: true }

                        Rectangle {
                            radius: 4
                            height: 24
                            implicitWidth: statusLabel.implicitWidth + 16
                            color: variance > 0 ? "#e74c3c" : (variance < 0 ? "#2ecc71" : "#95a5a6")

                            Label {
                                id: statusLabel
                                anchors.centerIn: parent
                                text: variance > 0 ? "Over" : (variance < 0 ? "Under" : "On Track")
                                color: "white"
                                font.pixelSize: 11
                                font.bold: true
                            }
                        }
                    }

                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 8

                        ColumnLayout {
                            spacing: 2
                            Label { text: "Actual"; color: "#7f8c8d"; font.pixelSize: 10 }
                            Label {
                                text: "₹" + gameController.formatIndianCurrency(actual)
                                color: "#e74c3c"
                                font.pixelSize: 18
                                font.bold: true
                            }
                        }

                        Rectangle {
                            width: 1
                            height: 40
                            color: "#2c3e50"
                        }

                        ColumnLayout {
                            spacing: 2
                            Label { text: "Variance"; color: "#7f8c8d"; font.pixelSize: 10 }
                            Label {
                                text: (variance >= 0 ? "+" : "") + "₹" + gameController.formatIndianCurrency(variance)
                                color: variance > 0 ? "#e74c3c" : "#2ecc71"
                                font.pixelSize: 18
                                font.bold: true
                            }
                        }
                    }

                    // Mini progress bar
                    Rectangle {
                        Layout.fillWidth: true
                        height: 6
                        radius: 3
                        color: "#0f3460"

                        Rectangle {
                            width: parent.width * Math.min(1, actual / Math.max(1, budget))
                            height: parent.height
                            radius: parent.radius
                            color: variance > 0 ? "#e74c3c" : "#4ecdc4"
                        }
                    }

                    // Edit button
                    RowLayout {
                        Layout.fillWidth: true

                        TextField {
                            id: editBudgetField
                            placeholderText: "Budget"
                            text: budget
                            Layout.preferredWidth: 100
                            Layout.preferredHeight: 32
                            background: Rectangle {
                                color: "#0f3460"
                                radius: 6
                            }
                            color: "#ecf0f1"
                            font.pixelSize: 12
                        }

                        TextField {
                            id: editActualField
                            placeholderText: "Actual"
                            text: actual
                            Layout.preferredWidth: 100
                            Layout.preferredHeight: 32
                            background: Rectangle {
                                color: "#0f3460"
                                radius: 6
                            }
                            color: "#ecf0f1"
                            font.pixelSize: 12
                        }

                        Item { Layout.fillWidth: true }

                        Button {
                            text: "Update"
                            Layout.preferredHeight: 32
                            Layout.preferredWidth: 80
                            background: Rectangle {
                                color: parent.hovered ? "#3cd9c4" : "#4ecdc4"
                                radius: 6
                            }
                            contentItem: Label {
                                text: parent.text
                                color: "#1a1a2e"
                                font.bold: true
                                horizontalAlignment: Text.AlignHCenter
                            }
                            onClicked: {
                                var budgetVal = parseFloat(editBudgetField.text) || 0
                                var actualVal = parseFloat(editActualField.text) || 0
                                gameController.updateExpense(name, budgetVal, actualVal)
                            }
                        }
                    }
                }
            }
        }
    }
}
