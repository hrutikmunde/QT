import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "../components"

Rectangle {
    id: goalPlannerScreen
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
                    text: "🏆 Goal Planner"
                    color: "#ecf0f1"
                    font.pixelSize: 24
                    font.bold: true
                }
                Label {
                    text: "Set targets and track your progress"
                    color: "#95a5a6"
                    font.pixelSize: 14
                }
            }

            Item { Layout.fillWidth: true }

            // Achievement Summary
            Rectangle {
                radius: 8
                height: 50
                implicitWidth: achievementLabel.implicitWidth + 40
                color: "#f39c12"

                Label {
                    id: achievementLabel
                    anchors.centerIn: parent
                    text: gameController.goalsAchieved + " / " + gameController.totalGoals + " Achieved"
                    color: "white"
                    font.pixelSize: 16
                    font.bold: true
                }
            }
        }

        // Add Goal Form
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
                spacing: 12

                ColumnLayout {
                    spacing: 4
                    Label { text: "Goal Name"; color: "#95a5a6"; font.pixelSize: 11 }
                    TextField {
                        id: goalNameField
                        placeholderText: "e.g., New Car"
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
                    Label { text: "Target Amount (₹)"; color: "#95a5a6"; font.pixelSize: 11 }
                    TextField {
                        id: goalAmountField
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
                    Label { text: "Target Date"; color: "#95a5a6"; font.pixelSize: 11 }
                    TextField {
                        id: goalDateField
                        placeholderText: "YYYY-MM-DD"
                        Layout.preferredWidth: 150
                        background: Rectangle {
                            color: "#0f3460"
                            radius: 6
                        }
                        color: "#ecf0f1"
                    }
                }

                Item {}

                Button {
                    text: "Add Goal"
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
                        var name = goalNameField.text.trim()
                        var amount = parseFloat(goalAmountField.text) || 0
                        var date = goalDateField.text.trim()

                        if (name === "") {
                            gameController.errorOccurred("Please enter goal name")
                            return
                        }
                        if (amount <= 0) {
                            gameController.errorOccurred("Please enter valid target amount")
                            return
                        }

                        gameController.addFinancialGoal(name, amount, date)
                        goalNameField.text = ""
                        goalAmountField.text = ""
                        goalDateField.text = ""
                    }
                }
            }
        }

        // Goals List
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: 12
            color: "#16213e"
            border.color: "#2c3e50"
            border.width: 1

            ListView {
                id: goalsListView
                anchors.fill: parent
                anchors.margins: 16
                model: gameController.goalModel
                clip: true
                spacing: 8

                delegate: Rectangle {
                    width: goalsListView.width
                    height: 100
                    radius: 8
                    color: "#0f3460"
                    border.color: isAchieved ? "#2ecc71" : "#2c3e50"
                    border.width: 1

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 16
                        spacing: 16

                        // Icon
                        Rectangle {
                            width: 60
                            height: 60
                            radius: 30
                            color: isAchieved ? "#2ecc71" : "#16213e"
                            border.color: isAchieved ? "#2ecc71" : "#4ecdc4"
                            border.width: 2

                            Label {
                                anchors.centerIn: parent
                                text: isAchieved ? "✓" : Math.round(progressPercent) + "%"
                                color: isAchieved ? "white" : "#4ecdc4"
                                font.pixelSize: isAchieved ? 24 : 14
                                font.bold: true
                            }
                        }

                        // Goal Info
                        ColumnLayout {
                            Layout.fillWidth: true
                            spacing: 4

                            RowLayout {
                                spacing: 8
                                Label {
                                    text: goalName
                                    color: "#ecf0f1"
                                    font.pixelSize: 16
                                    font.bold: true
                                }
                                Rectangle {
                                    visible: isAchieved
                                    color: "#2ecc71"
                                    radius: 4
                                    height: 18
                                    implicitWidth: achievedLabel.implicitWidth + 12
                                    Label {
                                        id: achievedLabel
                                        anchors.centerIn: parent
                                        text: "ACHIEVED"
                                        color: "white"
                                        font.pixelSize: 9
                                        font.bold: true
                                    }
                                }
                            }

                            Label {
                                text: "₹" + gameController.formatIndianCurrency(currentAmount) + " / ₹" + gameController.formatIndianCurrency(targetAmount)
                                color: "#95a5a6"
                                font.pixelSize: 12
                            }

                            Label {
                                text: "Remaining: ₹" + gameController.formatIndianCurrency(remainingAmount) + " by " + targetDate
                                color: "#7f8c8d"
                                font.pixelSize: 11
                            }

                            ProgressBar {
                                Layout.fillWidth: true
                                value: progressPercent / 100
                                barColor: isAchieved ? "#2ecc71" : "#4ecdc4"
                                height: 8
                            }
                        }

                        // Update and Delete Buttons
                        ColumnLayout {
                            spacing: 6

                            TextField {
                                id: goalCurrentField
                                placeholderText: "Current"
                                Layout.preferredWidth: 100
                                Layout.preferredHeight: 30
                                background: Rectangle {
                                    color: "#16213e"
                                    radius: 4
                                }
                                color: "#ecf0f1"
                                font.pixelSize: 12
                                validator: DoubleValidator { notation: DoubleValidator.StandardNotation }
                            }

                            RowLayout {
                                spacing: 4
                                Button {
                                    text: "Update"
                                    Layout.preferredHeight: 30
                                    Layout.preferredWidth: 70
                                    background: Rectangle {
                                        color: parent.hovered ? "#3cd9c4" : "#4ecdc4"
                                        radius: 4
                                    }
                                    contentItem: Label {
                                        text: parent.text
                                        color: "#1a1a2e"
                                        font.bold: true
                                        font.pixelSize: 11
                                        horizontalAlignment: Text.AlignHCenter
                                    }
                                    onClicked: {
                                        var current = parseFloat(goalCurrentField.text) || 0
                                        gameController.updateFinancialGoalProgress(id, current)
                                    }
                                }
                                Button {
                                    text: "✕"
                                    Layout.preferredHeight: 30
                                    Layout.preferredWidth: 30
                                    background: Rectangle {
                                        color: parent.hovered ? "#c0392b" : "transparent"
                                        radius: 4
                                    }
                                    contentItem: Label {
                                        text: parent.text
                                        color: "#e74c3c"
                                        horizontalAlignment: Text.AlignHCenter
                                    }
                                    onClicked: gameController.deleteFinancialGoal(id)
                                }
                            }
                        }
                    }
                }

                Label {
                    anchors.centerIn: parent
                    text: "No goals yet. Add your first goal above!"
                    color: "#7f8c8d"
                    font.pixelSize: 14
                    visible: gameController.goalModel.count === 0
                }
            }
        }
    }
}
