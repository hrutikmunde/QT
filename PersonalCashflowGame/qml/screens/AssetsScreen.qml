import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: assetsScreen
    color: "#1a1a2e"

    property var assetTypes: ["Real Estate", "Stocks", "Mutual Fund", "Gold", "FD", "PPF", "NPS", "SIP", "Business", "Bank Savings", "Other"]

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
                    text: "📈 Assets"
                    color: "#ecf0f1"
                    font.pixelSize: 24
                    font.bold: true
                }
                Label {
                    text: "Things that put money in your pocket"
                    color: "#95a5a6"
                    font.pixelSize: 14
                }
            }

            Item { Layout.fillWidth: true }

            // Summary
            RowLayout {
                spacing: 30

                ColumnLayout {
                    spacing: 2
                    Label { text: "Total Asset Value"; color: "#7f8c8d"; font.pixelSize: 11 }
                    Label {
                        text: "₹" + gameController.formatIndianCurrency(gameController.totalAssets)
                        color: "#2ecc71"
                        font.pixelSize: 18
                        font.bold: true
                    }
                }

                ColumnLayout {
                    spacing: 2
                    Label { text: "Monthly Passive Income"; color: "#7f8c8d"; font.pixelSize: 11 }
                    Label {
                        text: "₹" + gameController.formatIndianCurrency(gameController.passiveIncome)
                        color: "#9b59b6"
                        font.pixelSize: 18
                        font.bold: true
                    }
                }
            }
        }

        // Add Asset Form
        Rectangle {
            Layout.fillWidth: true
            height: 180
            radius: 12
            color: "#16213e"
            border.color: "#2c3e50"
            border.width: 1

            ColumnLayout {
                anchors.fill: parent
                anchors.margins: 16
                spacing: 12

                Label {
                    text: "Add New Asset"
                    color: "#ecf0f1"
                    font.pixelSize: 14
                    font.bold: true
                }

                RowLayout {
                    Layout.fillWidth: true
                    spacing: 12

                    ColumnLayout {
                        spacing: 4
                        Label { text: "Asset Name"; color: "#95a5a6"; font.pixelSize: 11 }
                        TextField {
                            id: assetNameField
                            placeholderText: "e.g., FD at HDFC Bank"
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
                        Label { text: "Type"; color: "#95a5a6"; font.pixelSize: 11 }
                        ComboBox {
                            id: assetTypeCombo
                            model: assetsScreen.assetTypes
                            Layout.preferredWidth: 150
                            background: Rectangle {
                                color: "#0f3460"
                                radius: 6
                            }
                            contentItem: Label {
                                text: parent.displayText
                                color: "#ecf0f1"
                            }
                        }
                    }

                    ColumnLayout {
                        spacing: 4
                        Label { text: "Purchase Value (₹)"; color: "#95a5a6"; font.pixelSize: 11 }
                        TextField {
                            id: assetPurchaseField
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
                        Label { text: "Current Value (₹)"; color: "#95a5a6"; font.pixelSize: 11 }
                        TextField {
                            id: assetCurrentField
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
                        Label { text: "Monthly Income (₹)"; color: "#95a5a6"; font.pixelSize: 11 }
                        TextField {
                            id: assetIncomeField
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
                        Label { text: "Annual Return (%)"; color: "#95a5a6"; font.pixelSize: 11 }
                        TextField {
                            id: assetReturnField
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

                    Item {}

                    Button {
                        text: "Add Asset"
                        Layout.preferredHeight: 40
                        Layout.preferredWidth: 120
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
                            var name = assetNameField.text.trim()
                            var type = assetTypeCombo.currentValue || assetsScreen.assetTypes[0]
                            var purchase = parseFloat(assetPurchaseField.text) || 0
                            var current = parseFloat(assetCurrentField.text) || 0
                            var income = parseFloat(assetIncomeField.text) || 0
                            var returns = parseFloat(assetReturnField.text) || 0

                            if (name === "") {
                                gameController.errorOccurred("Please enter asset name")
                                return
                            }

                            gameController.addAsset(name, type, purchase, current, income, returns)
                            assetNameField.text = ""
                            assetPurchaseField.text = ""
                            assetCurrentField.text = ""
                            assetIncomeField.text = ""
                            assetReturnField.text = ""
                        }
                    }
                }
            }
        }

        // Assets List
        Rectangle {
            Layout.fillWidth: true
            Layout.fillHeight: true
            radius: 12
            color: "#16213e"
            border.color: "#2c3e50"
            border.width: 1

            ListView {
                id: assetsList
                anchors.fill: parent
                anchors.margins: 16
                model: gameController.assetModel
                clip: true

                header: Rectangle {
                    width: assetsList.width
                    height: 40
                    color: "#0f3460"
                    radius: 6

                    RowLayout {
                        anchors.fill: parent
                        anchors.leftMargin: 16
                        anchors.rightMargin: 16
                        spacing: 0

                        Label { text: "Name"; color: "#95a5a6"; font.bold: true; Layout.preferredWidth: 150 }
                        Label { text: "Type"; color: "#95a5a6"; font.bold: true; Layout.preferredWidth: 120 }
                        Label { text: "Purchase Value"; color: "#95a5a6"; font.bold: true; Layout.preferredWidth: 120 }
                        Label { text: "Current Value"; color: "#95a5a6"; font.bold: true; Layout.preferredWidth: 120 }
                        Label { text: "Monthly Income"; color: "#95a5a6"; font.bold: true; Layout.preferredWidth: 120 }
                        Label { text: "Return %"; color: "#95a5a6"; font.bold: true; Layout.preferredWidth: 80 }
                        Item { Layout.fillWidth: true }
                    }
                }

                delegate: Rectangle {
                    width: assetsList.width
                    height: 50
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

                        Label { text: name; color: "#ecf0f1"; Layout.preferredWidth: 150 }
                        Label {
                            text: investmentType
                            color: "#3498db"
                            Layout.preferredWidth: 120
                        }
                        Label {
                            text: "₹" + gameController.formatIndianCurrency(purchaseValue)
                            color: "#95a5a6"
                            Layout.preferredWidth: 120
                        }
                        Label {
                            text: "₹" + gameController.formatIndianCurrency(currentValue)
                            color: "#2ecc71"
                            font.bold: true
                            Layout.preferredWidth: 120
                        }
                        Label {
                            text: "₹" + gameController.formatIndianCurrency(monthlyPassiveIncome)
                            color: "#9b59b6"
                            Layout.preferredWidth: 120
                        }
                        Label {
                            text: gameController.formatPercent(annualReturn)
                            color: annualReturn >= 0 ? "#2ecc71" : "#e74c3c"
                            Layout.preferredWidth: 80
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
                                gameController.deleteAsset(id)
                            }
                        }
                    }
                }

                Label {
                    anchors.centerIn: parent
                    text: "No assets recorded yet. Start building wealth!"
                    color: "#7f8c8d"
                    font.pixelSize: 14
                    visible: gameController.assetModel.count === 0
                }
            }
        }
    }
}
