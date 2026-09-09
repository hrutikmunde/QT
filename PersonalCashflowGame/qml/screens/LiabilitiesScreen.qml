import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: liabilitiesScreen
    color: "#1a1a2e"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 24
        spacing: 20

        // Header
        RowLayout {
            Layout.fillWidth: true
            spacing: 16

            ColumnLayout {
                spacing: 4
                Label {
                    text: "📉 Liabilities"
                    color: "#ecf0f1"
                    font.pixelSize: 24
                    font.bold: true
                }
                Label {
                    text: "Things that take money out of your pocket"
                    color: "#95a5a6"
                    font.pixelSize: 14
                }
            }

            Item { Layout.fillWidth: true }

            // Summary
            ColumnLayout {
                spacing: 2
                Label { text: "Total Liabilities"; color: "#7f8c8d"; font.pixelSize: 11 }
                Label {
                    text: "₹" + gameController.formatIndianCurrency(gameController.totalLiabilities)
                    color: "#e74c3c"
                    font.pixelSize: 18
                    font.bold: true
                }
            }
        }

        // Add Liability Form
        Rectangle {
            Layout.fillWidth: true
            height: 160
            radius: 12
            color: "#16213e"
            border.color: "#2c3e50"
            border.width: 1

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 16
                spacing: 12

                Label {
                    text: "Add New Liability"
                    color: "#ecf0f1"
                    font.pixelSize: 14
                    font.bold: true
                }

                RowLayout {
                    Layout.fillWidth: true
                    spacing: 12

                    ColumnLayout {
                        spacing: 4
                        Label { text: "Loan Name"; color: "#95a5a6"; font.pixelSize: 11 }
                        TextField {
                            id: liabilityNameField
                            placeholderText: "e.g., Car Loan"
                            Layout.preferredWidth: 180
                            background: Rectangle {
                                color: "#0f3460"
                                radius: 6
                            }
                            color: "#ecf0f1"
                        }
                    }

                    ColumnLayout {
                        spacing: 4
                        Label { text: "Outstanding Balance (₹)"; color: "#95a5a6"; font.pixelSize: 11 }
                        TextField {
                            id: liabilityBalanceField
                            placeholderText: "0"
                            Layout.preferredWidth: 150
                            background: Rectangle {
                                color: "#0f3460"
                                radius: 6
                            }
                            color: "#ecf0f1"
                            validator: DoubleValidator { notation: DoubleValidator.StandardNotation }
                        }
                    }

                    ColumnLayout {
                        spacing: 4
                        Label { text: "Monthly EMI (₹)"; color: "#95a5a6"; font.pixelSize: 11 }
                        TextField {
                            id: liabilityEmiField
                            placeholderText: "0"
                            Layout.preferredWidth: 130
                            background: Rectangle {
                                color: "#0f3460"
                                radius: 6
                            }
                            color: "#ecf0f1"
                            validator: DoubleValidator { notation: DoubleValidator.StandardNotation }
                        }
                    }

                    ColumnLayout {
                        spacing: 4
                        Label { text: "Interest Rate (%)"; color: "#95a5a6"; font.pixelSize: 11 }
                        TextField {
                            id: liabilityRateField
                            placeholderText: "0"
                            Layout.preferredWidth: 100
                            background: Rectangle {
                                color: "#0f3460"
                                radius: 6
                            }
                            color: "#ecf0f1"
                            validator: DoubleValidator { notation: DoubleValidator.StandardNotation }
                        }
                    }

                    ColumnLayout {
                        spacing: 4
                        Label { text: "Due Date"; color: "#95a5a6"; font.pixelSize: 11 }
                        TextField {
                            id: liabilityDueField
                            placeholderText: "YYYY-MM-DD"
                            Layout.preferredWidth: 120
                            background: Rectangle {
                                color: "#0f3460"
                                radius: 6
                            }
                            color: "#ecf0f1"
                        }
                    }

                    Item {}

                    Button {
                        text: "Add Liability"
                        Layout.preferredHeight: 40
                        Layout.preferredWidth: 140
                        background: Rectangle {
                            color: parent.hovered ? "#c0392b" : "#e74c3c"
                            radius: 8
                        }
                        contentItem: Label {
                            text: parent.text
                            color: "white"
                            font.bold: true
                            horizontalAlignment: Text.AlignHCenter
                        }
                        onClicked: {
                            var name = liabilityNameField.text.trim()
                            var balance = parseFloat(liabilityBalanceField.text) || 0
                            var emi = parseFloat(liabilityEmiField.text) || 0
                            var rate = parseFloat(liabilityRateField.text) || 0
                            var due = liabilityDueField.text.trim()

                            if (name === "") {
                                gameController.errorOccurred("Please enter liability name")
                                return
                            }

                            gameController.addLiability(name, balance, emi, rate, due)
                            liabilityNameField.text = ""
                            liabilityBalanceField.text = ""
                            liabilityEmiField.text = ""
                            liabilityRateField.text = ""
                            liabilityDueField.text = ""
                        }
                    }
                }
            }
        }

        // Liabilities List
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: 12
            color: "#16213e"
            border.color: "#2c3e50"
            border.width: 1

            ListView {
                id: liabilitiesList
                anchors.fill: parent
                anchors.margins: 16
                model: gameController.liabilityModel
                clip: true

                header: Rectangle {
                    width: liabilitiesList.width
                    height: 40
                    color: "#0f3460"
                    radius: 6

                    RowLayout {
                        anchors.fill: parent
                        anchors.leftMargin: 16
                        anchors.rightMargin: 16
                        spacing: 0

                        Label { text: "Name"; color: "#95a5a6"; font.bold: true; Layout.preferredWidth: 180 }
                        Label { text: "Balance"; color: "#95a5a6"; font.bold: true; Layout.preferredWidth: 140 }
                        Label { text: "Monthly EMI"; color: "#95a5a6"; font.bold: true; Layout.preferredWidth: 120 }
                        Label { text: "Interest Rate"; color: "#95a5a6"; font.bold: true; Layout.preferredWidth: 100 }
                        Label { text: "Due Date"; color: "#95a5a6"; font.bold: true; Layout.preferredWidth: 120 }
                        Item { Layout.fillWidth: true }
                    }
                }

                delegate: Rectangle {
                    width: liabilitiesList.width
                    height: 55
                    color: "transparent"

                    Rectangle {
                        anchors.fill: parent
                        radius: 4
                        color: index % 2 === 0 ? "transparent" : "#0f3460"
                    }

                    RowLayout {
                        anchors.fill: parent
                        anchors.leftMargin: 16
                        anchors.rightMargin: 16

                        Label { text: name; color: "#ecf0f1"; Layout.preferredWidth: 180 }
                        Label {
                            text: "₹" + gameController.formatIndianCurrency(balance)
                            color: "#e74c3c"
                            font.bold: true
                            Layout.preferredWidth: 140
                        }
                        Label {
                            text: "₹" + gameController.formatIndianCurrency(monthlyEmi)
                            color: "#f39c12"
                            Layout.preferredWidth: 120
                        }
                        Label {
                            text: gameController.formatPercent(interestRate)
                            color: interestRate > 10 ? "#e74c3c" : "#f39c12"
                            Layout.preferredWidth: 100
                        }
                        Label {
                            text: dueDate || "N/A"
                            color: "#95a5a6"
                            Layout.preferredWidth: 120
                        }

                        Button {
                            text: "✕"
                            Layout.preferredWidth: 40
                            background: Rectangle { color: "transparent" }
                            contentItem: Label {
                                text: parent.text
                                color: "#e74c3c"
                            }
                            onClicked: {
                                gameController.deleteLiability(id)
                            }
                        }
                    }
                }

                Label {
                    anchors.centerIn: parent
                    text: "No liabilities! Great job staying debt-free!"
                    color: "#2ecc71"
                    font.pixelSize: 14
                    visible: gameController.liabilityModel.count === 0
                }
            }
        }
    }
}
