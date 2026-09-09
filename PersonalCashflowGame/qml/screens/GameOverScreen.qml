import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: gameOverScreen
    color: "#1a1a2e"

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 30

        ColumnLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 8

            Label {
                text: "🎉"
                font.pixelSize: 80
                Layout.alignment: Qt.AlignHCenter
            }

            Label {
                text: "FINANCIAL FREEDOM ACHIEVED!"
                color: "#2ecc71"
                font.pixelSize: 32
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                Layout.alignment: Qt.AlignHCenter
            }

            Label {
                text: "Your passive income now covers all your expenses!"
                color: "#ecf0f1"
                font.pixelSize: 16
                horizontalAlignment: Text.AlignHCenter
                Layout.alignment: Qt.AlignHCenter
            }
        }

        // Stats Summary
        Rectangle {
            Layout.alignment: Qt.AlignHCenter
            width: 500
            height: 300
            radius: 12
            color: "#16213e"
            border.color: "#2ecc71"
            border.width: 2

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 16

                Label {
                    text: "🏆 Your Achievement Summary"
                    color: "#2ecc71"
                    font.pixelSize: 20
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    Layout.alignment: Qt.AlignHCenter
                }

                GridLayout {
                    Layout.fillWidth: true
                    columns: 2
                    columnSpacing: 30
                    rowSpacing: 12

                    Label { text: "Net Worth:"; color: "#95a5a6"; font.pixelSize: 14 }
                    Label {
                        text: "₹" + gameController.formatIndianCurrency(gameController.netWorth)
                        color: "#2ecc71"
                        font.pixelSize: 16
                        font.bold: true
                    }

                    Label { text: "Passive Income:"; color: "#95a5a6"; font.pixelSize: 14 }
                    Label {
                        text: "₹" + gameController.formatIndianCurrency(gameController.passiveIncome)
                        color: "#9b59b6"
                        font.pixelSize: 16
                        font.bold: true
                    }

                    Label { text: "Total Assets:"; color: "#95a5a6"; font.pixelSize: 14 }
                    Label {
                        text: "₹" + gameController.formatIndianCurrency(gameController.totalAssets)
                        color: "#2ecc71"
                        font.pixelSize: 16
                        font.bold: true
                    }

                    Label { text: "Goals Achieved:"; color: "#95a5a6"; font.pixelSize: 14 }
                    Label {
                        text: gameController.goalsAchieved + " / " + gameController.totalGoals
                        color: "#f39c12"
                        font.pixelSize: 16
                        font.bold: true
                    }

                    Label { text: "Savings Rate:"; color: "#95a5a6"; font.pixelSize: 14 }
                    Label {
                        text: gameController.formatPercent(gameController.savingsRate)
                        color: "#4ecdc4"
                        font.pixelSize: 16
                        font.bold: true
                    }

                    Label { text: "Months Played:"; color: "#95a5a6"; font.pixelSize: 14 }
                    Label {
                        text: gameController.monthsPlayed
                        color: "#3498db"
                        font.pixelSize: 16
                        font.bold: true
                    }
                }
            }
        }

        Button {
            text: "Back to Dashboard"
            Layout.alignment: Qt.AlignHCenter
            Layout.preferredHeight: 50
            Layout.preferredWidth: 200
            background: Rectangle {
                color: parent.hovered ? "#3cd9c4" : "#4ecdc4"
                radius: 8
            }
            contentItem: Label {
                text: parent.text
                color: "#1a1a2e"
                font.bold: true
                font.pixelSize: 14
                horizontalAlignment: Text.AlignHCenter
            }
            onClicked: {
                mainWindow.navigateTo("Dashboard")
            }
        }
    }
}
