import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: statCard
    property string title: ""
    property string value: "₹0"
    property string subtitle: ""
    property color accentColor: "#4ecdc4"
    property string icon: "📊"
    property string trend: "" // "up", "down", or ""
    property string trendValue: ""

    width: 200
    height: 130
    radius: 12
    color: "#16213e"
    border.color: "#2c3e50"
    border.width: 1

    Rectangle {
        // Top accent bar
        width: parent.width
        height: 3
        color: statCard.accentColor
        radius: 2
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 16
        spacing: 6

        RowLayout {
            Layout.fillWidth: true
            spacing: 8

            Label {
                text: statCard.icon
                font.pixelSize: 22
            }

            Label {
                text: statCard.title
                color: "#95a5a6"
                font.pixelSize: 12
                font.bold: true
                font.letterSpacing: 0.5
                Layout.fillWidth: true
                elide: Text.ElideRight
            }

            Rectangle {
                visible: statCard.trend !== ""
                color: statCard.trend === "up" ? "#2ecc71" : "#e74c3c"
                radius: 4
                height: 20
                implicitWidth: trendLabel.implicitWidth + 12

                Label {
                    id: trendLabel
                    anchors.centerIn: parent
                    text: statCard.trend === "up" ? "▲ " + statCard.trendValue : "▼ " + statCard.trendValue
                    color: "white"
                    font.pixelSize: 10
                    font.bold: true
                }
            }
        }

        Item {
            Layout.fillHeight: true
        }

        Label {
            text: statCard.value
            color: "#ecf0f1"
            font.pixelSize: 26
            font.bold: true
            Layout.fillWidth: true
            elide: Text.ElideRight
        }

        Label {
            text: statCard.subtitle
            color: "#7f8c8d"
            font.pixelSize: 11
            Layout.fillWidth: true
            elide: Text.ElideRight
        }
    }
}
