import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtCharts

Rectangle {
    id: lineChartCard
    property string title: ""
    property var data: []  // Array of {label, value, secondary}
    property color lineColor: "#4ecdc4"
    property color secondaryLineColor: "#e94560"
    property string primaryLabel: "Value"
    property string secondaryLabel: ""

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
            text: lineChartCard.title
            color: "#ecf0f1"
            font.pixelSize: 16
            font.bold: true
        }

        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true

            ChartView {
                anchors.fill: parent
                antialiasing: true
                backgroundColor: "transparent"
                plotAreaColor: "transparent"
                legend.color: "transparent"
                title: ""
                margins.top: 0
                margins.bottom: 0
                margins.left: 0
                margins.right: 0

                LineSeries {
                    id: line1
                    name: lineChartCard.primaryLabel
                    color: lineChartCard.lineColor
                    width: 3
                    pointsVisible: true
                    pointLabelsVisible: false

                    onCountChanged: refreshData()
                    function refreshData() {
                        if (!lineChartCard.data) return;
                        line1.clear();
                        var cats = [];
                        var maxVal = 0;
                        for (var i = 0; i < lineChartCard.data.length; i++) {
                            line1.append(i, lineChartCard.data[i].value);
                            cats.push(lineChartCard.data[i].label);
                            if (lineChartCard.data[i].value > maxVal) maxVal = lineChartCard.data[i].value;
                        }
                        if (lineChartCard.secondaryLabel !== "" && lineChartCard.data.length > 0 && lineChartCard.data[0].secondary !== undefined) {
                            line2.visible = true;
                            line2.clear();
                            for (var j = 0; j < lineChartCard.data.length; j++) {
                                line2.append(j, lineChartCard.data[j].secondary);
                                if (lineChartCard.data[j].secondary > maxVal) maxVal = lineChartCard.data[j].secondary;
                            }
                        } else {
                            line2.visible = false;
                        }
                        valueAxis.max = maxVal * 1.2;
                        catAxis.categories = cats;
                    }
                }

                LineSeries {
                    id: line2
                    name: lineChartCard.secondaryLabel
                    color: lineChartCard.secondaryLineColor
                    width: 3
                    pointsVisible: true
                    visible: false
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

                Component.onCompleted: {
                    line1.refreshData();
                }
            }
        }
    }
}
