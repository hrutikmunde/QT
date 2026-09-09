import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import PersonalCashflowGame
Page {
    background: Rectangle { color: "#0b1220" }
    property var rows: gameController.incomeRows()
    Connections { target: database; function onDataChanged() { rows = gameController.incomeRows() } }
    ColumnLayout { anchors.fill: parent; anchors.margins: 30
        SectionTitle { title: "Income Tracker" }
        Label { text: "Total: ₹" + Number(finance.totalIncome).toLocaleString(Qt.locale("en-IN"), "f", 0); color: "#9fb0c8" }
        RowLayout { Layout.fillWidth: true
            TextField { id: s; placeholderText: "Income source" }
            TextField { id: c; placeholderText: "Category" }
            TextField { id: a; placeholderText: "Amount"; inputMethodHints: Qt.ImhDigitsOnly }
            CheckBox { id: r; text: "Recurring" }
            TextField { id: n; placeholderText: "Notes" }
            Button { text: "Add"; onClicked: {
                if (gameController.addIncome(s.text, c.text, Number(a.text), r.checked, n.text)) {
                    s.clear(); c.clear(); a.clear(); n.clear()
                    rows = gameController.incomeRows()
                }
            }}
        }
        ListView { Layout.fillWidth: true; Layout.fillHeight: true; model: rows; clip: true
            delegate: Rectangle { width: ListView.view.width; height: 52; color: index % 2 ? "#101a2a" : "#142033"
                Row { anchors.fill: parent; anchors.margins: 12; spacing: 35
                    Label { text: date; color: "#8294ae"; width: 90 }
                    Label { text: source; color: "white"; width: 180 }
                    Label { text: category; color: "#9fb0c8"; width: 130 }
                    Label { text: "₹" + Number(amount).toLocaleString(Qt.locale("en-IN"), "f", 0); color: "white"; width: 120 }
                    Label { text: recurring ? "Yes" : "No"; color: "#9fb0c8" }
                }
            }
        }
    }
}
