import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import PersonalCashflowGame
Page {
    background: Rectangle{color:"#0b1220"}
    property var rows: gameController.goalRows()
    Connections { target: database; function onDataChanged() { rows = gameController.goalRows() } }
    ColumnLayout { anchors.fill: parent; anchors.margins: 30
        SectionTitle { title: "Goal Planner" }
        RowLayout { Layout.fillWidth: true
            TextField { id: n; placeholderText: "Goal" }
            TextField { id: t; placeholderText: "Target amount" }
            TextField { id: s; placeholderText: "Current savings" }
            TextField { id: d; placeholderText: "Target date" }
            Button { text: "Add"; onClicked: {
                if (gameController.addGoal(n.text, Number(t.text), Number(s.text), d.text, "")) {
                    rows = gameController.goalRows()
                    n.clear(); t.clear(); s.clear(); d.clear()
                }
            }}
        }
        ListView { Layout.fillWidth: true; Layout.fillHeight: true; model: rows
            delegate: Rectangle { width: ListView.view.width; height: 76; color: index % 2 ? "#101a2a" : "#142033"
                Column { anchors.fill: parent; anchors.margins: 12; spacing: 7
                    Row { spacing: 35
                        Label { text: name; color: "white"; width: 220 }
                        Label { text: "₹" + Number(saved).toLocaleString(Qt.locale("en-IN"), "f", 0) + " / ₹" + Number(target).toLocaleString(Qt.locale("en-IN"), "f", 0); color: "#9fb0c8"; width: 230 }
                        Label { text: targetDate; color: "#8495af" }
                    }
                    ProgressBar { width: parent.width; value: Math.min(progress, 1) }
                }
            }
        }
    }
}
