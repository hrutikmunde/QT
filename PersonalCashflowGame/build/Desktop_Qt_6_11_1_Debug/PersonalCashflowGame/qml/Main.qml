import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import PersonalCashflowGame

ApplicationWindow {
    id: root
    visible: true
    width: 1280
    height: 760
    minimumWidth: 1000
    minimumHeight: 650
    title: "Personal Cashflow Game — India"
    color: "#0b1220"

    property string currentPage: "Dashboard"

    RowLayout {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            Layout.preferredWidth: 225
            Layout.fillHeight: true
            color: "#111a2b"

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 18
                spacing: 7

                Label {
                    text: "CASHFLOW"
                    color: "white"
                    font.pixelSize: 23
                    font.bold: true
                }
                Label {
                    text: "Personal Finance • India"
                    color: "#8191aa"
                    font.pixelSize: 12
                    bottomPadding: 18
                }

                Repeater {
                    model: ["Dashboard","Daily Tracker","Income","Expenses","Assets","Liabilities","Investments","Emergency Fund","Financial Freedom","Goals"]
                    delegate: Button {
                        Layout.fillWidth: true
                        text: modelData
                        flat: true
                        highlighted: root.currentPage === modelData
                        contentItem: Label {
                            text: parent.text
                            color: parent.highlighted ? "white" : "#aebbd0"
                            verticalAlignment: Text.AlignVCenter
                            horizontalAlignment: Text.AlignLeft
                            leftPadding: 8
                        }
                        background: Rectangle {
                            radius: 8
                            color: parent.highlighted ? "#263a5d" : "transparent"
                        }
                        onClicked: root.currentPage = modelData
                    }
                }

                Item { Layout.fillHeight: true }

                Button {
                    text: "＋ New Game"
                    Layout.fillWidth: true
                    onClicked: gameController.newGame()
                }
            }
        }

        StackLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            currentIndex: {
                switch(root.currentPage) {
                case "Dashboard": return 0
                case "Daily Tracker": return 1
                case "Income": return 2
                case "Expenses": return 3
                case "Assets": return 4
                case "Liabilities": return 5
                case "Investments": return 6
                case "Emergency Fund": return 7
                case "Financial Freedom": return 8
                case "Goals": return 9
                }
                return 0
            }

            Dashboard {}
            DailyTrackerPage {}
            IncomePage {}
            ExpensesPage {}
            AssetsPage {}
            LiabilitiesPage {}
            InvestmentsPage {}
            EmergencyFundPage {}
            FreedomPage {}
            GoalsPage {}
        }
    }
}
