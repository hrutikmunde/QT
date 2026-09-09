import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import PersonalCashflowGame
Page {
    background: Rectangle{color:"#0b1220"}
    property var rows: gameController.dailyRows()
    Connections { target: database; function onDataChanged() { rows = gameController.dailyRows() } }
    ColumnLayout { anchors.fill: parent; anchors.margins: 30
        SectionTitle { title: "Daily Expense Tracker" }
        Label { text: "Track food, other spending and room rent."; color: "#8495af" }
        RowLayout { Layout.fillWidth: true
            TextField { id: day; placeholderText: "Day" }
            TextField { id: date; placeholderText: "YYYY-MM-DD" }
            TextField { id: f; placeholderText: "Food" }
            TextField { id: desc; placeholderText: "Description" }
            TextField { id: o; placeholderText: "Other" }
            TextField { id: r; placeholderText: "Room rent" }
            Button { text: "Add"; onClicked: {
                if (gameController.addDailyEntry(day.text, date.text, Number(f.text), desc.text, Number(o.text), Number(r.text))) {
                    rows = gameController.dailyRows()
                    day.clear(); date.clear(); f.clear(); desc.clear(); o.clear(); r.clear()
                }
            }}
        }
        ListView { Layout.fillWidth: true; Layout.fillHeight: true; model: rows
            delegate: Rectangle { width: ListView.view.width; height: 50; color: index % 2 ? "#101a2a" : "#142033"
                Row { anchors.fill: parent; anchors.margins: 12; spacing: 35
                    Label { text: date; color: "#8294ae"; width: 100 }
                    Label { text: day; color: "#9fb0c8"; width: 110 }
                    Label { text: "Food ₹" + Number(food).toLocaleString(Qt.locale("en-IN"), "f", 0); color: "white"; width: 140 }
                    Label { text: description; color: "#9fb0c8"; width: 260 }
                    Label { text: "Other ₹" + Number(other).toLocaleString(Qt.locale("en-IN"), "f", 0); color: "#9fb0c8"; width: 150 }
                    Label { text: "Rent ₹" + Number(rent).toLocaleString(Qt.locale("en-IN"), "f", 0); color: "#9fb0c8" }
                }
            }
        }
    }
}
