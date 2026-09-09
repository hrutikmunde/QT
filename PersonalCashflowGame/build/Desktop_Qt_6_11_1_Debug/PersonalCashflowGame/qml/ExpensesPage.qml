import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import PersonalCashflowGame
Page {
    background: Rectangle { color: "#0b1220" }
    property var rows: gameController.expenseRows()
    Connections { target: database; function onDataChanged() { rows = gameController.expenseRows() } }
    ColumnLayout { anchors.fill: parent; anchors.margins: 30
        SectionTitle { title: "Expense Tracker" }
        Label { text: "Actual expenses: ₹" + Number(finance.totalExpenses).toLocaleString(Qt.locale("en-IN"), "f", 0); color: "#9fb0c8" }
        RowLayout { Layout.fillWidth: true
            TextField { id: c; placeholderText: "Category" }
            TextField { id: b; placeholderText: "Budget" }
            TextField { id: a; placeholderText: "Actual" }
            TextField { id: n; placeholderText: "Notes" }
            Button { text: "Add"; onClicked: {
                if (gameController.addExpense(c.text, Number(b.text), Number(a.text), n.text)) {
                    c.clear(); b.clear(); a.clear(); n.clear()
                    rows = gameController.expenseRows()
                }
            }}
        }
        ListView { Layout.fillWidth: true; Layout.fillHeight: true; model: rows
            delegate: Rectangle { width: ListView.view.width; height: 52; color: index % 2 ? "#101a2a" : "#142033"
                Row { anchors.fill: parent; anchors.margins: 12; spacing: 45
                    Label { text: category; color: "white"; width: 220 }
                    Label { text: "₹" + Number(budget).toLocaleString(Qt.locale("en-IN"), "f", 0); color: "#9fb0c8"; width: 150 }
                    Label { text: "₹" + Number(actual).toLocaleString(Qt.locale("en-IN"), "f", 0); color: "white"; width: 150 }
                    Label { text: notes; color: "#71829a" }
                }
            }
        }
    }
}
