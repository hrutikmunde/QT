import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: dailyTrackerScreen
    color: "#1a1a2e"

    property var dayNames: ["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"]

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
                    text: "📅 Daily Tracker"
                    color: "#ecf0f1"
                    font.pixelSize: 24
                    font.bold: true
                }
                Label {
                    text: "Log your daily expenses"
                    color: "#95a5a6"
                    font.pixelSize: 14
                }
            }

            Item { Layout.fillWidth: true }

            // Summary
            RowLayout {
                spacing: 20

                ColumnLayout {
                    spacing: 2
                    Label { text: "Food Today"; color: "#7f8c8d"; font.pixelSize: 11 }
                    Label {
                        text: "₹" + gameController.formatIndianCurrency(foodToday)
                        color: "#f39c12"
                        font.pixelSize: 16
                        font.bold: true
                    }
                }

                ColumnLayout {
                    spacing: 2
                    Label { text: "Other Today"; color: "#7f8c8d"; font.pixelSize: 11 }
                    Label {
                        text: "₹" + gameController.formatIndianCurrency(otherToday)
                        color: "#e74c3c"
                        font.pixelSize: 16
                        font.bold: true
                    }
                }

                ColumnLayout {
                    spacing: 2
                    Label { text: "Total Today"; color: "#7f8c8d"; font.pixelSize: 11 }
                    Label {
                        text: "₹" + gameController.formatIndianCurrency(foodToday + otherToday)
                        color: "#4ecdc4"
                        font.pixelSize: 16
                        font.bold: true
                    }
                }
            }
        }

        // Add Daily Expense Form
        Rectangle {
            Layout.fillWidth: true
            height: 120
            radius: 12
            color: "#16213e"
            border.color: "#2c3e50"
            border.width: 1

            RowLayout {
                anchors.fill: parent
                anchors.margins: 16
                spacing: 16

                ColumnLayout {
                    spacing: 4
                    Label { text: "Date"; color: "#95a5a6"; font.pixelSize: 11 }
                    TextField {
                        id: dailyDateField
                        text: new Date().toISOString().split('T')[0]
                        Layout.preferredWidth: 140
                        background: Rectangle {
                            color: "#0f3460"
                            radius: 6
                        }
                        color: "#ecf0f1"
                    }
                }

                ColumnLayout {
                    spacing: 4
                    Label { text: "Food (₹)"; color: "#95a5a6"; font.pixelSize: 11 }
                    TextField {
                        id: dailyFoodField
                        placeholderText: "0"
                        Layout.preferredWidth: 120
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
                    Label { text: "Other (₹)"; color: "#95a5a6"; font.pixelSize: 11 }
                    TextField {
                        id: dailyOtherField
                        placeholderText: "0"
                        Layout.preferredWidth: 120
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
                    Label { text: "Description"; color: "#95a5a6"; font.pixelSize: 11 }
                    TextField {
                        id: dailyDescField
                        placeholderText: "Optional notes"
                        Layout.preferredWidth: 200
                        background: Rectangle {
                            color: "#0f3460"
                            radius: 6
                        }
                        color: "#ecf0f1"
                    }
                }

                Item {}

                Button {
                    text: "Add Entry"
                    Layout.preferredHeight: 44
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
                        var date = dailyDateField.text.trim()
                        var food = parseFloat(dailyFoodField.text) || 0
                        var other = parseFloat(dailyOtherField.text) || 0
                        var desc = dailyDescField.text.trim()

                        if (date === "") {
                            gameController.errorOccurred("Please enter a date")
                            return
                        }

                        var d = new Date(date)
                        var dayName = dayNames[d.getDay()]

                        if (gameController.addDailyExpense(date, dayName, food, other, desc)) {
                            dailyFoodField.text = ""
                            dailyOtherField.text = ""
                            dailyDescField.text = ""
                            refreshTodayTotals()
                        }
                    }
                }
            }
        }

        // Daily Expenses List
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: 12
            color: "#16213e"
            border.color: "#2c3e50"
            border.width: 1

            ListView {
                id: dailyList
                anchors.fill: parent
                anchors.margins: 16
                model: gameController.dailyExpenseModel
                clip: true

                header: Rectangle {
                    width: dailyList.width
                    height: 40
                    color: "#0f3460"
                    radius: 6

                    RowLayout {
                        anchors.fill: parent
                        anchors.leftMargin: 16
                        anchors.rightMargin: 16
                        spacing: 0

                        Label { text: "Date"; color: "#95a5a6"; font.bold: true; Layout.preferredWidth: 100 }
                        Label { text: "Day"; color: "#95a5a6"; font.bold: true; Layout.preferredWidth: 100 }
                        Label { text: "Food"; color: "#95a5a6"; font.bold: true; Layout.preferredWidth: 100 }
                        Label { text: "Other"; color: "#95a5a6"; font.bold: true; Layout.preferredWidth: 100 }
                        Label { text: "Total"; color: "#95a5a6"; font.bold: true; Layout.preferredWidth: 100 }
                        Label { text: "Description"; color: "#95a5a6"; font.bold: true; Layout.fillWidth: true }
                    }
                }

                delegate: Rectangle {
                    width: dailyList.width
                    height: 45
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

                        Label { text: date; color: "#ecf0f1"; Layout.preferredWidth: 100 }
                        Label { text: dayOfWeek; color: "#95a5a6"; Layout.preferredWidth: 100 }
                        Label {
                            text: "₹" + gameController.formatIndianCurrency(foodAmount)
                            color: "#f39c12"
                            Layout.preferredWidth: 100
                        }
                        Label {
                            text: "₹" + gameController.formatIndianCurrency(otherAmount)
                            color: "#e74c3c"
                            Layout.preferredWidth: 100
                        }
                        Label {
                            text: "₹" + gameController.formatIndianCurrency(foodAmount + otherAmount)
                            color: "#4ecdc4"
                            font.bold: true
                            Layout.preferredWidth: 100
                        }
                        Label {
                            text: description
                            color: "#7f8c8d"
                            Layout.fillWidth: true
                            elide: Text.ElideRight
                        }
                    }
                }

                Label {
                    anchors.centerIn: parent
                    text: "No daily expenses recorded yet"
                    color: "#7f8c8d"
                    font.pixelSize: 14
                    visible: gameController.dailyExpenseModel.count === 0
                }
            }
        }
    }

    // Today's totals
    property double foodToday: {
        var today = new Date().toISOString().split('T')[0]
        var expenses = gameController.dailyExpenseModel
        var total = 0
        for (var i = 0; i < expenses.count; i++) {
            var item = expenses.get(i)
            if (item && item.date === today) {
                total += (item.foodAmount || 0)
            }
        }
        return total
    }

    property double otherToday: {
        var today = new Date().toISOString().split('T')[0]
        var expenses = gameController.dailyExpenseModel
        var total = 0
        for (var i = 0; i < expenses.count; i++) {
            var item = expenses.get(i)
            if (item && item.date === today) {
                total += (item.otherAmount || 0)
            }
        }
        return total
    }

    function refreshTodayTotals() {
        var today = new Date().toISOString().split('T')[0]
        // Trigger refresh by forcing update
    }
}
