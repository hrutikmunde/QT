import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import PersonalCashflowGame
Page {
    background: Rectangle{color:"#0b1220"}
    property var rows: gameController.liabilityRows()
    Connections { target: database; function onDataChanged() { rows = gameController.liabilityRows() } }
    ColumnLayout { anchors.fill: parent; anchors.margins: 30
        SectionTitle { title: "Liabilities" }
        Label { text: "Outstanding: ₹" + Number(finance.totalLiabilities).toLocaleString(Qt.locale("en-IN"), "f", 0); color: "#8495af" }
        RowLayout { Layout.fillWidth: true
            TextField { id: n; placeholderText: "Loan name" }
            TextField { id: b; placeholderText: "Balance" }
            TextField { id: e; placeholderText: "Monthly EMI" }
            TextField { id: i; placeholderText: "Interest %" }
            TextField { id: d; placeholderText: "Due date" }
            Button { text: "Add"; onClicked: {
                if (gameController.addLiability(n.text, Number(b.text), Number(e.text), Number(i.text), d.text)) {
                    rows = gameController.liabilityRows()
                    n.clear(); b.clear(); e.clear(); i.clear(); d.clear()
                }
            }}
        }
        ListView { Layout.fillWidth: true; Layout.fillHeight: true; model: rows
            delegate: Rectangle { width: ListView.view.width; height: 52; color: index % 2 ? "#101a2a" : "#142033"
                Row { anchors.fill: parent; anchors.margins: 12; spacing: 35
                    Label { text: name; color: "white"; width: 190 }
                    Label { text: "₹" + Number(balance).toLocaleString(Qt.locale("en-IN"), "f", 0); color: "white"; width: 150 }
                    Label { text: "EMI ₹" + Number(emi).toLocaleString(Qt.locale("en-IN"), "f", 0); color: "#9fb0c8"; width: 150 }
                    Label { text: Number(interest).toFixed(2) + "%"; color: "#9fb0c8"; width: 100 }
                    Label { text: dueDate; color: "#8294ae" }
                }
            }
        }
    }
}
