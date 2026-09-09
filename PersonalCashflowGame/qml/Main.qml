import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

ApplicationWindow {
    id: mainWindow
    width: 1280
    height: 800
    minimumWidth: 1024
    minimumHeight: 700
    visible: true
    title: "Personal Cashflow Game - India"

    property string currentScreen: "Dashboard"
    property var screenHistory: ["Dashboard"]

    // Color palette
    readonly property color backgroundColor: "#1a1a2e"
    readonly property color surfaceColor: "#16213e"
    readonly property color surfaceAccent: "#0f3460"
    readonly property color primaryColor: "#e94560"
    readonly property color secondaryColor: "#4ecdc4"
    readonly property color successColor: "#2ecc71"
    readonly property color warningColor: "#f39c12"
    readonly property color dangerColor: "#e74c3c"
    readonly property color textColor: "#ecf0f1"
    readonly property color textMuted: "#95a5a6"
    readonly property color borderColor: "#2c3e50"

    background: Rectangle {
        color: mainWindow.backgroundColor
    }

    // Navigation function
    function navigateTo(screen) {
        if (screen !== currentScreen) {
            screenHistory.push(screen)
            currentScreen = screen
        }
    }

    function goBack() {
        if (screenHistory.length > 1) {
            screenHistory.pop()
            currentScreen = screenHistory[screenHistory.length - 1]
        }
    }

    // Header
    header: HeaderBar {
        currentScreen: mainWindow.currentScreen
        playerName: gameController.playerName
        monthYear: gameController.currentMonthName
    }

    // Main layout with sidebar and content
    RowLayout {
        anchors.fill: parent
        spacing: 0

        // Sidebar
        Sidebar {
            Layout.fillHeight: true
            Layout.preferredWidth: 240
            currentScreen: mainWindow.currentScreen
            onNavigate: (screen) => mainWindow.navigateTo(screen)
        }

        // Main content area
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            color: mainWindow.backgroundColor

            StackView {
                id: stackView
                anchors.fill: parent
                initialItem: dashboardComponent
            }

            Component {
                id: dashboardComponent
                Dashboard {}
            }

            Component {
                id: incomeComponent
                IncomeScreen {}
            }

            Component {
                id: expenseComponent
                ExpenseScreen {}
            }

            Component {
                id: dailyTrackerComponent
                DailyTrackerScreen {}
            }

            Component {
                id: assetsComponent
                AssetsScreen {}
            }

            Component {
                id: liabilitiesComponent
                LiabilitiesScreen {}
            }

            Component {
                id: cashFlowComponent
                CashFlowScreen {}
            }

            Component {
                id: investmentComponent
                InvestmentScreen {}
            }

            Component {
                id: emergencyFundComponent
                EmergencyFundScreen {}
            }

            Component {
                id: financialFreedomComponent
                FinancialFreedomScreen {}
            }

            Component {
                id: goalPlannerComponent
                GoalPlannerScreen {}
            }

            Component {
                id: gameOverComponent
                GameOverScreen {}
            }
        }
    }

    // Watch for screen changes
    Connections {
        target: mainWindow
        function onCurrentScreenChanged() {
            var component
            switch (mainWindow.currentScreen) {
            case "Dashboard":
                component = dashboardComponent
                break
            case "Income":
                component = incomeComponent
                break
            case "Expenses":
                component = expenseComponent
                break
            case "Daily Tracker":
                component = dailyTrackerComponent
                break
            case "Assets":
                component = assetsComponent
                break
            case "Liabilities":
                component = liabilitiesComponent
                break
            case "Cash Flow":
                component = cashFlowComponent
                break
            case "Investments":
                component = investmentComponent
                break
            case "Emergency Fund":
                component = emergencyFundComponent
                break
            case "Financial Freedom":
                component = financialFreedomComponent
                break
            case "Goal Planner":
                component = goalPlannerComponent
                break
            case "GameOver":
                component = gameOverComponent
                break
            default:
                component = dashboardComponent
            }
            if (component) {
                stackView.replace(component)
            }
        }
    }

    // Error dialog
    Dialog {
        id: errorDialog
        modal: true
        title: "Error"
        anchors.centerIn: parent

        property string errorMessage: ""

        Label {
            text: errorDialog.errorMessage
            wrapMode: Text.WordWrap
            color: mainWindow.textColor
        }

        standardButtons: Dialog.Ok
    }

    // Notification popup
    Rectangle {
        id: notificationBar
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 20
        width: Math.min(parent.width * 0.6, 500)
        height: 50
        radius: 8
        color: mainWindow.successColor
        visible: false
        opacity: 0

        property string message: ""

        Label {
            anchors.centerIn: parent
            text: notificationBar.message
            color: "white"
            font.bold: true
            font.pixelSize: 14
        }

        Behavior on opacity {
            NumberAnimation { duration: 300 }
        }
    }

    Timer {
        id: notificationTimer
        interval: 3000
        onTriggered: {
            notificationBar.opacity = 0
        }
    }

    // Watch for errors
    Connections {
        target: gameController
        function onErrorOccurred(error) {
            errorDialog.errorMessage = error
            errorDialog.open()
        }

        function onNotification(message) {
            notificationBar.message = message
            notificationBar.visible = true
            notificationBar.opacity = 1
            notificationTimer.restart()
        }
    }

    Component.onCompleted: {
        // Start with dashboard
        currentScreen = "Dashboard"
    }
}
