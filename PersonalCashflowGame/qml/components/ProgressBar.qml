import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    id: progressBar
    property real value: 0  // 0 to 1
    property string label: ""
    property string rightLabel: ""
    property color barColor: "#4ecdc4"
    property real height: 8
    property bool showPercent: true

    implicitHeight: column.implicitHeight
    implicitWidth: 200

    ColumnLayout {
        id: column
        anchors.fill: parent
        spacing: 4

        RowLayout {
            Layout.fillWidth: true
            visible: progressBar.label !== ""

            Label {
                text: progressBar.label
                color: "#bdc3c7"
                font.pixelSize: 12
                Layout.fillWidth: true
            }

            Label {
                text: progressBar.showPercent
                      ? (progressBar.value * 100).toFixed(1) + "%"
                      : progressBar.rightLabel
                color: "#ecf0f1"
                font.pixelSize: 12
                font.bold: true
            }
        }

        Rectangle {
            Layout.fillWidth: true
            height: progressBar.height
            radius: progressBar.height / 2
            color: "#0f3460"

            Rectangle {
                width: Math.min(parent.width * Math.max(0, Math.min(1, progressBar.value)), parent.width)
                height: parent.height
                radius: parent.height / 2
                color: progressBar.barColor

                Behavior on width {
                    NumberAnimation { duration: 600; easing.type: Easing.OutCubic }
                }
            }
        }
    }
}
