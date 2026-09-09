import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import PersonalCashflowGame
Page {
    background: Rectangle{color:"#0b1220"}
    property var rows: gameController.assetRows()
    Connections { target: database; function onDataChanged() { rows = gameController.assetRows() } }
    ColumnLayout { anchors.fill: parent; anchors.margins: 30; spacing: 14
        SectionTitle { title: "Assets" }
        Label { text: "Assets that have value or generate income."; color: "#8495af" }
        RowLayout { Layout.fillWidth: true
            TextField { id: n; placeholderText: "Asset name" }
            TextField { id: t; placeholderText: "Type" }
            TextField { id: p; placeholderText: "Purchase value" }
            TextField { id: c; placeholderText: "Current value" }
            TextField { id: pi; placeholderText: "Monthly passive income" }
            TextField { id: r; placeholderText: "Annual return %" }
            Button { text: "Add"; onClicked: {
                if (gameController.addAsset(n.text, t.text, Number(p.text), Number(c.text), Number(pi.text), Number(r.text), "")) {
                    rows = gameController.assetRows()
                    n.clear(); t.clear(); p.clear(); c.clear(); pi.clear(); r.clear()
                }
            }}
        }
        ListView { Layout.fillWidth: true; Layout.fillHeight: true; model: rows
            delegate: Rectangle { width: ListView.view.width; height: 58; color: index % 2 ? "#101a2a" : "#142033"
                Row { anchors.fill: parent; anchors.margins: 12; spacing: 30
                    Label { text: name; color: "white"; width: 180 }
                    Label { text: type; color: "#9fb0c8"; width: 130 }
                    Label { text: "₹" + Number(current).toLocaleString(Qt.locale("en-IN"), "f", 0); color: "white"; width: 140 }
                    Label { text: "Passive ₹" + Number(passive).toLocaleString(Qt.locale("en-IN"), "f", 0); color: "#9fb0c8" }
                    Label { text: Number(annualReturn).toFixed(1) + "%"; color: "#9fb0c8" }
                }
            }
        }
    }
}
