import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import PersonalCashflowGame
Page {
    background: Rectangle{color:"#0b1220"}
    property var rows: gameController.investmentRows()
    Connections { target: database; function onDataChanged() { rows = gameController.investmentRows() } }
    ColumnLayout { anchors.fill: parent; anchors.margins: 30
        SectionTitle { title: "Investment Tracker" }
        RowLayout { Layout.fillWidth: true
            TextField { id: t; placeholderText: "Investment type" }
            TextField { id: i; placeholderText: "Invested amount" }
            TextField { id: c; placeholderText: "Current value" }
            TextField { id: n; placeholderText: "Notes" }
            Button { text: "Add"; onClicked: {
                if (gameController.addInvestment(t.text, Number(i.text), Number(c.text), n.text)) {
                    rows = gameController.investmentRows()
                    t.clear(); i.clear(); c.clear(); n.clear()
                }
            }}
        }
        ListView { Layout.fillWidth: true; Layout.fillHeight: true; model: rows
            delegate: Rectangle { width: ListView.view.width; height: 54; color: index % 2 ? "#101a2a" : "#142033"
                Row { anchors.fill: parent; anchors.margins: 12; spacing: 40
                    Label { text: type; color: "white"; width: 180 }
                    Label { text: "₹" + Number(invested).toLocaleString(Qt.locale("en-IN"), "f", 0); color: "#9fb0c8"; width: 140 }
                    Label { text: "₹" + Number(current).toLocaleString(Qt.locale("en-IN"), "f", 0); color: "white"; width: 140 }
                    Label { text: "₹" + Number(profit).toLocaleString(Qt.locale("en-IN"), "f", 0); color: "#9fb0c8"; width: 130 }
                    Label { text: (profitPercent * 100).toFixed(1) + "%"; color: "#9fb0c8" }
                }
            }
        }
    }
}
