import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import PersonalCashflowGame
Page {
    background: Rectangle { color: "#0b1220" }
    ColumnLayout { anchors.fill: parent; anchors.margins: 30; spacing: 22
        SectionTitle { title: "Financial Freedom Tracker" }
        Label { text: "Passive Income / Monthly Expenses × 100"; color: "#8495af" }
        Label { text: (finance.freedomPercent * 100).toFixed(1) + "%"; color: "white"; font.pixelSize: 56; font.bold: true }
        ProgressBar { Layout.fillWidth: true; value: Math.min(finance.freedomPercent, 1) }
        Label { text: finance.freedomStatus; color: "#9fb0c8"; font.pixelSize: 22 }
        RowLayout { Layout.fillWidth: true
            Label { text: "Passive income: ₹" + Number(finance.passiveIncome).toLocaleString(Qt.locale("en-IN"), "f", 0); color: "#9fb0c8" }
            Label { text: "Expenses: ₹" + Number(finance.totalExpenses).toLocaleString(Qt.locale("en-IN"), "f", 0); color: "#9fb0c8" }
        }
    }
}
