import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4

Page {
    id: page
    width: applicationWindow.width
    height: 480

    signal buttonBtSignal();
       objectName: "homePage"
    // if mobile
    Rectangle {
        id: element
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width
        CircularGauge {
            id: h2Gauge

            implicitWidth: 300
            implicitHeight: 300
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            anchors.top: parent.top
            anchors.topMargin: 55

            anchors.horizontalCenter: parent.horizontalCenter
            style: CircularGaugeStyle {

                tickmark: Rectangle {
                    visible: true
                    implicitWidth: outerRadius * 0.02
                    antialiasing: true
                    implicitHeight: outerRadius * 0.06
                    //color: "#90A4AE"
                    color: "black"
                }
                minorTickmark: Rectangle {
                    visible: true
                    implicitWidth: outerRadius * 0.01
                    antialiasing: true
                    implicitHeight: outerRadius * 0.03
                    //color: "#90A4AE"
                    color: "black"
                }

                needle: Rectangle {
                    y: outerRadius * 0.15
                    implicitWidth: outerRadius * 0.03
                    implicitHeight: outerRadius * 0.9
                    antialiasing: true
                    color: Qt.rgba(0.66, 0.3, 0, 1)
                }
            }

            Text {
                id: indexText
                text: "H2 Level"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: valueText.top

                color: "black"
            }
            Text {
                id: valueText
                text: "Unknown"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
            }
        }

        //Rectangle{
        Column {
            id: p1row
            width: applicationWindow.width
            height: 45

            //anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: h2Gauge.bottom
            anchors.topMargin: 25
            Label {
                id: fllabel
                text: qsTr("Flight Time")
                //Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.horizontalCenter: parent.horizontalCenter
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            }

            Label {
                id: ftime
                text: qsTr("Unknown")
                //   Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                //verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.horizontalCenter: parent.horizontalCenter
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            }
        }

        // only show for emergency landing


        /*
        Row {
            id: row
            width: applicationWindow.width
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: p1row.bottom

            Text {
                id: erFltTimeLabel
                text: qsTr("testing")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }
            Text {
                id: erFltTime
                text: qsTr("testing")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }*/
        Button {
            id: btButton

            y: 466
            text: qsTr("Connect")
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.rightMargin: -50
            anchors.leftMargin: -50
            onClicked:{
                 page.buttonBtSignal();
            //emit fcStats.runbt()
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}D{i:12}
}
##^##*/

