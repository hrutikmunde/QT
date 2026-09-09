import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "../components"

Rectangle {
    id: emergencyFundScreen
    color: "#1a1a2e"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 24
        spacing: 20

        // Header
        ColumnLayout {
            spacing: 4
            Label {
                text: "🛡️ Emergency Fund Planner"
                color: "#ecf0f1"
                font.pixelSize: 24
                font.bold: true
            }
            Label {
                text: "Aim for 6 months of expenses set aside for emergencies"
                color: "#95a5a6"
                font.pixelSize: 14
            }
        }

        // Main Card
        Rectangle {
            Layout.fillWidth: true
            height: 280
            radius: 12
            color: "#16213e"
            border.color: "#2c3e50"
            border.width: 1

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 30
                spacing: 16

                RowLayout {
                    Layout.fillWidth: true
                    spacing: 8

                    Label { text: "🛡️"; font.pixelSize: 32 }
                    Label {
                        text: "Emergency Fund Status"
                        color: "#ecf0f1"
                        font.pixelSize: 18
                        font.bold: true
                        Layout.fillWidth: true
                    }
                    Label {
                        text: gameController.emergencyFundStatus
                        color: gameController.emergencyFundPercent >= 100 ? "#2ecc71" : "#f39c12"
                        font.pixelSize: 16
                        font.bold: true
                    }
                }

                // Progress Display
                ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 8

                    RowLayout {
                        Layout.fillWidth: true
                        spacing: 8

                        ColumnLayout {
                            spacing: 2
                            Label { text: "Current"; color: "#7f8c8d"; font.pixelSize: 11 }
                            Label {
                                text: "₹" + gameController.formatIndianCurrency(gameController.emergencyFundCurrent)
                                color: "#4ecdc4"
                                font.pixelSize: 24
                                font.bold: true
                            }
                        }

                        Item { Layout.fillWidth: true }

                        ColumnLayout {
                            spacing: 2
                            Label { text: "Target (6 months)"; color: "#7f8c8d"; font.pixelSize: 11 }
                            Label {
                                text: "₹" + gameController.formatIndianCurrency(gameController.emergencyFundTarget)
                                color: "#f39c12"
                                font.pixelSize: 24
                                font.bold: true
                            }
                        }

                        Item { Layout.fillWidth: true }

                        ColumnLayout {
                            spacing: 2
                            Label { text: "Completion"; color: "#7f8c8d"; font.pixelSize: 11 }
                            Label {
                                text: gameController.formatPercent(gameController.emergencyFundPercent)
                                color: "#ecf0f1"
                                font.pixelSize: 24
                                font.bold: true
                            }
                        }
                    }

                    ProgressBar {
                        Layout.fillWidth: true
                        value: gameController.emergencyFundPercent / 100
                        barColor: gameController.emergencyFundPercent >= 100 ? "#2ecc71" : "#f39c12"
                        height: 16
                    }
                }

                // Update form
                RowLayout {
                    Layout.fillWidth: true
                    spacing: 12

                    Label { text: "Update Amount:"; color: "#95a5a6"; font.pixelSize: 13 }
                    TextField {
                        id: emergencyAmountField
                        placeholderText: "Current amount"
                        Layout.preferredWidth: 200
                        background: Rectangle {
                            color: "#0f3460"
                            radius: 6
                        }
                        color: "#ecf0f1"
                        validator: DoubleValidator { notation: DoubleValidator.StandardNotation }
                    }

                    Button {
                        text: "Update"
                        Layout.preferredHeight: 36
                        Layout.preferredWidth: 100
                        background: Rectangle {
                            color: parent.hovered ? "#3cd9c4" : "#4ecdc4"
                            radius: 8
                        }
                        contentItem: Label {
                            text: parent.text
                            color: "#1a1a2e"
                            font.bold: true
                            horizontalAlignment: Text.AlignHCenter
                        }
                        onClicked: {
                            var amount = parseFloat(emergencyAmountField.text) || 0
                            gameController.updateEmergencyFund(amount)
                            emergencyAmountField.text = ""
                        }
                    }

                    Item { Layout.fillWidth: true }
                }
            }
        }

        // Status Cards
        RowLayout {
            Layout.fillWidth: true
            spacing: 16

            Rectangle {
                Layout.fillWidth: true
                height: 120
                radius: 12
                color: "#16213e"
                border.color: "#e74c3c"
                border.width: 1

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 16
                    spacing: 8

                    Label { text: "⚠️"; font.pixelSize: 24 }
                    Label {
                        text: "Below 25%"
                        color: "#e74c3c"
                        font.pixelSize: 14
                        font.bold: true
                    }
                    Label {
                        text: "Critical: Build emergency fund urgently"
                        color: "#95a5a6"
                        font.pixelSize: 11
                        wrapMode: Text.WordWrap
                    }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                height: 120
                radius: 12
                color: "#16213e"
                border.color: "#f39c12"
                border.width: 1

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 16
                    spacing: 8

                    Label { text: "🟡"; font.pixelSize: 24 }
                    Label {
                        text: "50% There"
                        color: "#f39c12"
                        font.pixelSize: 14
                        font.bold: true
                    }
                    Label {
                        text: "Halfway done! Keep building consistently"
                        color: "#95a5a6"
                        font.pixelSize: 11
                        wrapMode: Text.WordWrap
                    }
                }
            }

            Rectangle {
                Layout.fillWidth: true
                height: 120
                radius: 12
                color: "#16213e"
                border.color: "#2ecc71"
                border.width: 1

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 16
                    spacing: 8

                    Label { text: "✅"; font.pixelSize: 24 }
                    Label {
                        text: "Fully Funded!"
                        color: "#2ecc71"
                        font.pixelSize: 14
                        font.bold: true
                    }
                    Label {
                        text: "Excellent! You're prepared for emergencies"
                        color: "#95a5a6"
                        font.pixelSize: 11
                        wrapMode: Text.WordWrap
                    }
                }
            }
        }

        // Tips Section
        Rectangle {
            Layout.fillWidth: true
            height: 100
            radius: 12
            color: "#16213e"
            border.color: "#2c3e50"
            border.width: 1

            RowLayout {
                anchors.fill: parent
                anchors.margins: 20
                spacing: 20

                Label { text: "💡"; font.pixelSize: 24 }

                ColumnLayout {
                    spacing: 4
                    Label {
                        text: "Why 6 months?"
                        color: "#f39c12"
                        font.pixelSize: 14
                        font.bold: true
                    }
                    Label {
                        text: "Six months gives you enough buffer for job loss, medical emergencies, or major repairs without going into debt."
                        color: "#ecf0f1"
                        font.pixelSize: 13
                        wrapMode: Text.WordWrap
                        Layout.fillWidth: true
                    }
                }
            }
        }
    }
}
