import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import PersonalCashflowGame

Page {
    background: Rectangle { color: "#0b1220" }

    Flickable {
        anchors.fill: parent
        contentWidth: width
        contentHeight: column.implicitHeight + 50
        clip: true

        ColumnLayout {
            id: column
            x: 30; y: 28
            width: parent.width - 60
            spacing: 22

            RowLayout {
                Layout.fillWidth: true
                ColumnLayout {
                    Layout.fillWidth: true
                    Label { text: "Financial Dashboard"; color: "white"; font.pixelSize: 30; font.bold: true }
                    Label { text: "Rich Dad Poor Dad inspired personal cash-flow tracker"; color: "#8495af"; font.pixelSize: 13 }
                }
                Label { text: "Turn / Month " + gameController.turn; color: "#9fb0c8"; font.pixelSize: 14 }
            }

            GridLayout {
                Layout.fillWidth: true
                columns: 4
                columnSpacing: 14
                rowSpacing: 14

                StatCard { title:"Monthly Income"; value:"₹" + Number(finance.totalIncome).toLocaleString(Qt.locale("en-IN"), "f", 0); subtitle:"Income sources" }
                StatCard { title:"Monthly Expenses"; value:"₹" + Number(finance.totalExpenses).toLocaleString(Qt.locale("en-IN"), "f", 0); subtitle:"Actual expenses" }
                StatCard { title:"Cash Flow"; value:"₹" + Number(finance.cashFlow).toLocaleString(Qt.locale("en-IN"), "f", 0); subtitle:"Income − expenses" }
                StatCard { title:"Savings Rate"; value:(finance.savingsRate*100).toFixed(1)+"%"; subtitle:"Cash flow / income" }
                StatCard { title:"Passive Income"; value:"₹" + Number(finance.passiveIncome).toLocaleString(Qt.locale("en-IN"), "f", 0); subtitle:"Monthly" }
                StatCard { title:"Total Assets"; value:"₹" + Number(finance.totalAssets).toLocaleString(Qt.locale("en-IN"), "f", 0); subtitle:"Current value" }
                StatCard { title:"Liabilities"; value:"₹" + Number(finance.totalLiabilities).toLocaleString(Qt.locale("en-IN"), "f", 0); subtitle:"Outstanding balance" }
                StatCard { title:"Net Worth"; value:"₹" + Number(finance.netWorth).toLocaleString(Qt.locale("en-IN"), "f", 0); subtitle:"Assets − liabilities" }
            }

            Rectangle {
                Layout.fillWidth: true
                height: 170
                radius: 14
                color: "#121d30"
                border.color: "#263650"
                Column {
                    anchors.fill: parent; anchors.margins: 20; spacing: 12
                    Label { text:"Financial Freedom"; color:"white"; font.pixelSize:20; font.bold:true }
                    ProgressBar { width: parent.width; value: Math.min(finance.freedomPercent,1); from:0; to:1 }
                    Label { text:(finance.freedomPercent*100).toFixed(1)+"%  •  "+finance.freedomStatus; color:"#9fb0c8"; font.pixelSize:14 }
                    Label { text:"Passive income ₹"+Number(finance.passiveIncome).toLocaleString(Qt.locale("en-IN"),"f",0)+" / expenses ₹"+Number(finance.totalExpenses).toLocaleString(Qt.locale("en-IN"),"f",0); color:"#6f8099" }
                }
            }

            RowLayout {
                Layout.fillWidth:true
                Button { text:"Next Month"; onClicked:gameController.nextTurn() }
                Button { text:"Refresh"; onClicked:gameController.refresh() }
            }
        }
    }
}
