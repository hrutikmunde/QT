import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ToolBar {
    id: header
    height: 60
    property string currentScreen: ""
    property string playerName: ""
    property string monthYear: ""

    background: Rectangle {
        color: "#16213e"
        Rectangle {
            width: parent.width
            height: 1
            anchors.bottom: parent.bottom
            color: "#2c3e50"
        }
    }

    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        spacing: 20

        // App title with logo
        RowLayout {
            spacing: 12

            Rectangle {
                width: 32
                height: 32
                radius: 6
                color: "#e94560"

                Label {
                    anchors.centerIn: parent
                    text: "₹"
                    font.pixelSize: 20
                    font.bold: true
                    color: "white"
                }
            }

            ColumnLayout {
                spacing: 0
                Label {
                    text: "CASHFLOW GAME"
                    font.pixelSize: 16
                    font.bold: true
                    font.letterSpacing: 1
                    color: "#ecf0f1"
                }
                Label {
                    text: "Personal Finance Tracker"
                    font.pixelSize: 10
                    color: "#95a5a6"
                }
            }
        }

        Item {
            Layout.fillWidth: true
        }

        // Current screen indicator
        Rectangle {
            color: "#0f3460"
            radius: 6
            height: 36
            implicitWidth: screenLabel.implicitWidth + 24

            Label {
                id: screenLabel
                anchors.centerIn: parent
                text: header.currentScreen
                color: "#ecf0f1"
                font.pixelSize: 13
                font.bold: true
            }
        }

        // Player info
        RowLayout {
            spacing: 8

            ColumnLayout {
                spacing: 0
                Label {
                    text: header.playerName
                    color: "#ecf0f1"
                    font.pixelSize: 13
                    font.bold: true
                    horizontalAlignment: Text.AlignRight
                }
                Label {
                    text: header.monthYear
                    color: "#95a5a6"
                    font.pixelSize: 11
                    horizontalAlignment: Text.AlignRight
                }
            }

            Rectangle {
                width: 36
                height: 36
                radius: 18
                color: "#4ecdc4"

                Label {
                    anchors.centerIn: parent
                    text: header.playerName.charAt(0).toUpperCase()
                    color: "white"
                    font.bold: true
                    font.pixelSize: 16
                }
            }
        }
    }
}
