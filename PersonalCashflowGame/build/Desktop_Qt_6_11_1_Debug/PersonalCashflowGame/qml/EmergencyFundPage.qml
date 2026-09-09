import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import PersonalCashflowGame
Page {
    background: Rectangle { color: "#0b1220" }
    ColumnLayout { anchors.fill: parent; anchors.margins: 30; spacing: 20
        SectionTitle { title: "Emergency Fund Planner" }
        Label { text: "Target = 6 months of actual expenses"; color: "#8495af" }
        RowLayout { Layout.fillWidth: true
            ColumnLayout {
                Label { text: "Monthly Expenses"; color: "#8294ae" }
                Label { text: "₹" + Number(finance.totalExpenses).toLocaleString(Qt.locale("en-IN"), "f", 0); color: "white"; font.pixelSize: 24; font.bold: true }
            }
            ColumnLayout {
                Label { text: "6-Month Target"; color: "#8294ae" }
                Label { text: "₹" + Number(finance.emergencyTarget).toLocaleString(Qt.locale("en-IN"), "f", 0); color: "white"; font.pixelSize: 24; font.bold: true }
            }
            ColumnLayout {
                Label { text: "Current Fund"; color: "#8294ae" }
                TextField {
                    id: v
                    text: "" + finance.emergencyCurrent
                    onEditingFinished: gameController.setEmergencyFund(Number(text))
                }
            }
        }
        ProgressBar { Layout.fillWidth: true; value: Math.min(finance.emergencyProgress, 1) }
        Label { text: (finance.emergencyProgress * 100).toFixed(1) + "% • " + finance.emergencyStatus; color: "#9fb0c8"; font.pixelSize: 18 }
    }
}
