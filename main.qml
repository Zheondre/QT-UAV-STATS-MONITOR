import QtQuick 2.12
import QtQuick.Window 2.12
import QtCharts 2.15

import QtQuick.Controls 2


Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    signal addButtonClicked()
    signal srchSelectSignal(s : string)
    signal editingFinished(s : string)
    Column {

       id: column
        x: 0
        y: 0
        width: 152
        height: 480
        visible: false
    }

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

        property var splinObArry: []
        //How do we let qchartview know about the spline array ?

        Rectangle {
            id: rectangle
            x: -152
            y: 0
            width: 153
            height: 480
            color: "#faf9f9"

            TextField {
                id: search
                x: 8
                y: 63
                width: 137
                height: 33
                horizontalAlignment: Text.AlignHCenter
                placeholderText: qsTr("Search")
                //onEditingFinished:
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

            DateTimeAxis {
               id: dateTime
               format: "hh:mm:ss"
               tickCount: 20
           }
    //allocate SplineSeries array for chartview when needed
        function addSeries() {
            sName = mspline.getName(idval)
            splinObArry.push(Qt.createQmlObject('SplineSeries{
            id:' +sName+
                                                'name:'+ sName+
                                                'axisX:'+axisName+
                                                'axisY:'+dateTime+
                                                '}',
                                                chart,'qmlCreationError.txt'));

            idVal += 1
            //update graph
        }

        function deleteASeries(){
        }


        SplineSeries{
            id: test
            name: idVal
            axisX: axisName
        }



    }


    Button {
        id: startSop
        objectName: "startSop"
        x: 0
        y: 442
        width: 152
        height: 38
        text: qsTr("Start")
      //  onClicked:
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
