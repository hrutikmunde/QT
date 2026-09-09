import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtCharts

Rectangle {
    id: barChartCard
    property string title: ""
    property var data: []  // Array of {label, value}
    property color barColor: "#4ecdc4"

    height: 280
    radius: 12
    color: "#16213e"
    border.color: "#2c3e50"
    border.width: 1

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 16
        spacing: 8

        Label {
            text: barChartCard.title
            color: "#ecf0f1"
            font.pixelSize: 16
            font.bold: true
        }

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true

            ChartView {
                id: chartView
                anchors.fill: parent
                antialiasing: true
                legend.visible: false
                backgroundColor: "transparent"
                plotAreaColor: "transparent"
                title: ""
                margins.top: 0
                margins.bottom: 0
                margins.left: 0
                margins.right: 0

                BarSeries {
                    id: barSeries
                    labelsVisible: true
                    labelsFormat: "@value"
                    BarSet {
                        id: barSet
                        values: []
                        color: barChartCard.barColor
                        labelColor: "#ecf0f1"
                    }

                    onCountChanged: updateBars()

                    function updateBars() {
                        if (!barChartCard.data) return;
                        barSet.remove(0, barSet.count());
                        var cats = [];
                        for (var i = 0; i < barChartCard.data.length; i++) {
                            barSet.append(barChartCard.data[i].value);
                            cats.push(barChartCard.data[i].label);
                        }
                        barSeries.attachAxis(catAxis);
                        catAxis.categories = cats;
                    }
                }

                ValueAxis {
                    id: valueAxis
                    min: 0
                    labelTextColor: "#95a5a6"
                    gridLineColor: "#2c3e50"
                }

                BarCategoryAxis {
                    id: catAxis
                    labelsColor: "#bdc3c7"
                }
            }

            Component.onCompleted: {
                if (barSeries) {
                    barSeries.updateBars();
                }
            }
        }
    }
}
