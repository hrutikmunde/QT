import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: sidebar
    color: "#16213e"
    property string currentScreen: ""
    signal navigate(string screen)

    Rectangle {
        width: parent.width
        height: 1
        color: "#2c3e50"
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.topMargin: 20
        spacing: 4

        // Dashboard
        SidebarItem {
            icon: "📊"
            label: "Dashboard"
            screenName: "Dashboard"
            currentScreen: sidebar.currentScreen
            onClicked: sidebar.navigate("Dashboard")
        }

        // Section Divider
        Rectangle {
            Layout.fillWidth: true
            Layout.topMargin: 10
            Layout.bottomMargin: 5
            Layout.leftMargin: 16
            Layout.rightMargin: 16
            height: 1
            color: "#2c3e50"
        }

        Label {
            text: "TRACKING"
            color: "#7f8c8d"
            font.pixelSize: 10
            font.bold: true
            font.letterSpacing: 1
            Layout.leftMargin: 20
            Layout.topMargin: 5
            Layout.bottomMargin: 5
        }

        SidebarItem {
            icon: "💰"
            label: "Income"
            screenName: "Income"
            currentScreen: sidebar.currentScreen
            onClicked: sidebar.navigate("Income")
        }

        SidebarItem {
            icon: "💸"
            label: "Expenses"
            screenName: "Expenses"
            currentScreen: sidebar.currentScreen
            onClicked: sidebar.navigate("Expenses")
        }

        SidebarItem {
            icon: "📅"
            label: "Daily Tracker"
            screenName: "Daily Tracker"
            currentScreen: sidebar.currentScreen
            onClicked: sidebar.navigate("Daily Tracker")
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.topMargin: 10
            Layout.bottomMargin: 5
            Layout.leftMargin: 16
            Layout.rightMargin: 16
            height: 1
            color: "#2c3e50"
        }

        Label {
            text: "WEALTH"
            color: "#7f8c8d"
            font.pixelSize: 10
            font.bold: true
            font.letterSpacing: 1
            Layout.leftMargin: 20
            Layout.topMargin: 5
            Layout.bottomMargin: 5
        }

        SidebarItem {
            icon: "📈"
            label: "Assets"
            screenName: "Assets"
            currentScreen: sidebar.currentScreen
            onClicked: sidebar.navigate("Assets")
        }

        SidebarItem {
            icon: "📉"
            label: "Liabilities"
            screenName: "Liabilities"
            currentScreen: sidebar.currentScreen
            onClicked: sidebar.navigate("Liabilities")
        }

        SidebarItem {
            icon: "💼"
            label: "Investments"
            screenName: "Investments"
            currentScreen: sidebar.currentScreen
            onClicked: sidebar.navigate("Investments")
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.topMargin: 10
            Layout.bottomMargin: 5
            Layout.leftMargin: 16
            Layout.rightMargin: 16
            height: 1
            color: "#2c3e50"
        }

        Label {
            text: "PLANNING"
            color: "#7f8c8d"
            font.pixelSize: 10
            font.bold: true
            font.letterSpacing: 1
            Layout.leftMargin: 20
            Layout.topMargin: 5
            Layout.bottomMargin: 5
        }

        SidebarItem {
            icon: "🌊"
            label: "Cash Flow"
            screenName: "Cash Flow"
            currentScreen: sidebar.currentScreen
            onClicked: sidebar.navigate("Cash Flow")
        }

        SidebarItem {
            icon: "🛡️"
            label: "Emergency Fund"
            screenName: "Emergency Fund"
            currentScreen: sidebar.currentScreen
            onClicked: sidebar.navigate("Emergency Fund")
        }

        SidebarItem {
            icon: "🎯"
            label: "Financial Freedom"
            screenName: "Financial Freedom"
            currentScreen: sidebar.currentScreen
            onClicked: sidebar.navigate("Financial Freedom")
        }

        SidebarItem {
            icon: "🏆"
            label: "Goal Planner"
            screenName: "Goal Planner"
            currentScreen: sidebar.currentScreen
            onClicked: sidebar.navigate("Goal Planner")
        }

        Item {
            Layout.fillHeight: true
        }

        // Bottom action
        Rectangle {
            Layout.fillWidth: true
            Layout.leftMargin: 16
            Layout.rightMargin: 16
            Layout.bottomMargin: 20
            height: 1
            color: "#2c3e50"
        }

        // Next month button
        Rectangle {
            Layout.fillWidth: true
            Layout.leftMargin: 16
            Layout.rightMargin: 16
            Layout.bottomMargin: 20
            height: 44
            radius: 8
            color: advanceMouse.containsMouse ? "#e94560" : "#0f3460"
            border.color: "#e94560"
            border.width: 1

            RowLayout {
                anchors.centerIn: parent
                spacing: 8

                Label {
                    text: "➡️"
                    font.pixelSize: 14
                }

                Label {
                    text: "Next Month"
                    color: "white"
                    font.pixelSize: 13
                    font.bold: true
                }
            }

            MouseArea {
                id: advanceMouse
                anchors.fill: parent
                hoverEnabled: true
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    gameController.nextTurn()
                }
            }
        }
    }
}
