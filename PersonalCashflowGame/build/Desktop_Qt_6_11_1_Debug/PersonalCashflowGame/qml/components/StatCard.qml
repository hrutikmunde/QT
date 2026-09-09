import QtQuick
import QtQuick.Controls

Rectangle {
    property string title: ""
    property string value: ""
    property string subtitle: ""
    radius: 14
    color: "#182235"
    border.color: "#2b3a55"
    implicitWidth: 220
    implicitHeight: 110

    Column {
        anchors.fill: parent
        anchors.margins: 16
        spacing: 6
        Label { text: title; color: "#9fb0c8"; font.pixelSize: 13 }
        Label { text: value; color: "white"; font.pixelSize: 25; font.bold: true }
        Label { text: subtitle; color: "#7f90aa"; font.pixelSize: 11 }
    }
}
