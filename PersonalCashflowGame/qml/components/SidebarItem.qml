import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ItemDelegate {
    id: sidebarItem
    property string icon: ""
    property string label: ""
    property string screenName: ""
    property string currentScreen: ""

    Layout.fillWidth: true
    Layout.leftMargin: 12
    Layout.rightMargin: 12
    height: 44

    background: Rectangle {
        anchors.fill: parent
        color: sidebarItem.screenName === sidebarItem.currentScreen ? "#0f3460" :
               (hover.containsMouse ? "#1f2c4e" : "transparent")
        radius: 8

        Rectangle {
            width: 3
            height: parent.height - 8
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 0
            color: "#e94560"
            radius: 2
            visible: sidebarItem.screenName === sidebarItem.currentScreen
        }
    }

    contentItem: RowLayout {
        spacing: 12
        anchors.left: parent.left
        anchors.leftMargin: 16
        anchors.verticalCenter: parent.verticalCenter

        Label {
            text: sidebarItem.icon
            font.pixelSize: 18
        }

        Label {
            text: sidebarItem.label
            color: sidebarItem.screenName === sidebarItem.currentScreen ? "#ecf0f1" : "#bdc3c7"
            font.pixelSize: 13
            font.bold: sidebarItem.screenName === sidebarItem.currentScreen
        }
    }

    MouseArea {
        id: hover
        anchors.fill: parent
        hoverEnabled: true
        cursorShape: Qt.PointingHandCursor
        onClicked: sidebarItem.clicked()
    }
}
