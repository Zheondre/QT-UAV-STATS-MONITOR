import QtQuick 2.12
import QtQuick.Window 2.12
import QtCharts 2.15

import QtQuick.Controls 2

import myspline 1.0
Window {
    id: pltWindow
    objectName: "plotWindow"

    width: 640;  height: 480
    visible: true
    //title: qsTr("Hello World")

    //signal addButtonClicked()
    signal srchEditSignal(string txt)
    signal editingFinished(s : string)
    signal startStop()

    ChartView{
        id: qmlViewChart
        objectName:  "qmlViewChart"
        width: 400
        height: 300
        title:"FcAir"
        anchors.fill: parent
        anchors.bottomMargin: 0
        anchors.leftMargin: 152
        antialiasing: true

        property var idVal: 0
        property var sName: ""
        property var axisName: ""
        property var temp2: NULL

        property var splinObArry: []

        property  var temp:
        //How do we let qchartview know about the spline array ?

        DateTimeAxis {
            id: dt
            //objectName: axisX
            format: "hh:mm:ss"
            tickCount: 20
        }
        //allocate SplineSeries array for chartview when needed
        function addSeries(name: string) {
            temp = Qt.createQmlObject('import QtCharts 2.15; SplineSeries{}',
            qmlViewChart)

            //temp.id =;
            temp.name = name;
            temp2 = dt;

            //temp.objectName = name;
            temp.axisX = dt;
            //temp.axisY = ;

            splinObArry.push(temp)
            //update graph
        }

        function deleteASeries(){
        }

        /*
        SplineSeries{
        id: test
        name: idVal
        axisX: dt // this works but is null when setting the time series on dynamic spline series
        }
        */

        }


    Rectangle {
        id: rectangle
        x: 0
        y: 0
        width: 152
        height: 480
        color: "#faf9f9"

        TextField {
            id: search
            objectName: "srch"
            x: 8
            y: 63
            width: 137
            height: 33
            horizontalAlignment: Text.AlignHCenter
            placeholderText: qsTr("Search")
            onEditingFinished: srchEditSignal(search.text)
        }

        Text {
            id: element
            x: 35
            y: 26
            width: 83
            height: 24
            color: "#e73a3a"
            text: qsTr("Honeywell")
            font.pixelSize: 18
        }
    }

        Button {
            id: startSop
            objectName: "startStop"
            x: 0
            y: 442
            width: 152
            height: 38
            text: qsTr("Start")
            signal startStop()
            onClicked: startStop()
        }

        Button {
            id: addfcItem
            objectName: "addfcItem"
            x: 0
            y: 401
            width: 152
            height: 38
            text: qsTr("Add")
            signal addButtonClicked()
            onClicked:addButtonClicked()
        }

        ListView {
            id: listView
            x: 0
            y: 103
            width: 152
            height: 299
            delegate: Item {
                x: 5
                width: 80
                height: 40
                Row {
                    id: row1
                    Rectangle {
                        width: 40
                        height: 40
                        color: colorCode
                    }

                    Text {
                        text: name
                        anchors.verticalCenter: parent.verticalCenter
                        font.bold: true
                    }
                    spacing: 10
                }
            }
            model: ListModel {
                ListElement {
                    name: "Grey"
                    colorCode: "grey"
                }

                ListElement {
                    name: "Red"
                    colorCode: "red"
                }

                ListElement {
                    name: "Blue"
                    colorCode: "blue"
                }

                ListElement {
                    name: "Green"
                    colorCode: "green"
                }
            }
        }
    }

    /*##^##
Designer {
    D{i:0;formeditorZoom:0.6600000262260437}
}
##^##*/
