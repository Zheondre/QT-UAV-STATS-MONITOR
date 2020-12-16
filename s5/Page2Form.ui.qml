import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.1

import StatsMdl 1.0

//import StatsLst 1.0
import fcairsts 1.0
Page {
    id: page
    width: applicationWindow.width
    height: applicationWindow.height - (50 + mainHeader.height)

    //height: applicationWindow.height
    Rectangle {
        // background color bellow header
        width: parent.width
        height: parent.height
        //color: "#90A4AE"
        color: "#f0f3f4"
        Rectangle {
            id: statsLabel
            height: 45
            ////width: applicationWindow.width
            //width: child.width
            //color: "#90A4AE"
            color: "#f0f3f4"
            //children: font.pixelSize: Qt.application.font.pixelSize * 1
            // anchors.top: mainHeader.bottom
            // anchors.topMargin: 0
            anchors.verticalCenter: children.verticalCenter

            Row {
                id: pg2RowListLabel
                //anchors.verticalCenter: children.verticalCenter
                //Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                height: parent.height
                Text {
                    id: element
                    text: qsTr("Fav")
                    anchors.verticalCenter: parent.verticalCenter
                    verticalAlignment: Text.AlignVCenter
                    //anchors.verticalCenter: parent.verticalCenter

                    //transformOrigin: Item.Center
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    //font.pixelSize: 10
                    //verticalAlignment: Text.AlignVCenter
                    //Layout.leftMargin: 10
                    //color: "white"
                }
                Text {
                    id: element1
                    text: qsTr("Name")
                    anchors.left: element.right
                    anchors.leftMargin: 8
                    anchors.verticalCenter: parent.verticalCenter
                    verticalAlignment: Text.AlignVCenter
                    //font.pixelSize: 10
                    //color: "white"
                    //Layout.leftMargin: 60
                }
                Text {
                    id: element2
                    text: qsTr("Value")
                    anchors.left: element1.right
                    anchors.leftMargin: 90
                    verticalAlignment: Text.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter
                    //font.pixelSize: 10
                    //color: "white"
                    //Layout.leftMargin: 90
                }

                Text {
                    id: element3
                    text: qsTr("Unt")
                    anchors.left: element2.right
                    anchors.leftMargin: 35
                    verticalAlignment: Text.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter
                    //font.pixelSize: 10
                    //color: "white"
                    //Layout.leftMargin: -50
                }

                Text {
                    id: element4
                    width: 40
                    anchors.left: element3.right
                    anchors.leftMargin: 10
                    text: qsTr("Force")
                    verticalAlignment: Text.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter
                    //font.pixelSize: 10
                    //color: "white"
                    // Layout.rightMargin: 60
                }
                Text {
                    id: element5
                    anchors.left: element4.right
                    anchors.leftMargin: 10
                    text: qsTr("Input")
                    verticalAlignment: Text.AlignVCenter
                    anchors.verticalCenter: parent.verticalCenter
                    //font.pixelSize: 10
                    //color: "white"
                    // Layout.rightMargin: 60
                }
            }
        }

        ListView {

            anchors.top: statsLabel.bottom
            anchors.topMargin: 1

            implicitWidth: parent.width
            implicitHeight: applicationWindow.height - (statsLabel.height + mainHeader.height)
            spacing: 1

            clip: true

            model: StatsModel {
                list: fcStats
            }

            delegate: Rectangle {
                id: lvrec
                color: model.force ? "Red" : "White"
                //color: "white"
                height: 55
                width: applicationWindow.width

                // RowLayout {
                Row {
                    id: row
                    height: lvrec.height
                    CheckBox {
                        // height: lvrec.height
                        id: favCheck
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.leftMargin: -10
                        //Layout.leftMargin: -10
                        scale: 0.7
                        onClicked: model.fav = checked
                    }

                    Text {
                        width: 100
                        height: parent.height
                        id: nameDisplay
                        //text: qsTr("Name")
                        text: model.name
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignLeft
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: favCheck.right
                        anchors.leftMargin: -5
                        //color: "white"
                        //font
                    }

                    // }
                    Rectangle {
                        id: dataLabelrec
                        height: lvrec.height
                        width: 105
                        color: "black"
                        anchors.left: nameDisplay.right
                        anchors.leftMargin: 0
                        //Layout.leftMargin: -35
                        Text {
                            id: dataDisplay
                            width: 85

                            //text: qsTr("Testing")
                            //text: bl.getValue
                            text: model.value
                            horizontalAlignment: Text.AlignHCenter
                            color: "white"
                            anchors.centerIn: parent
                        }
                    }
                    Text {
                        //height: lvrec.height
                        id: unitDisplay
                        //text: qsTr("Unt")
                        //text: bl.getUnit
                        text: model.unit
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: dataLabelrec.right
                        anchors.leftMargin: 5
                        // Layout.leftMargin: -40
                        horizontalAlignment: Text.AlignLeft
                        verticalAlignment: Text.AlignVCenter
                    }
                    CheckBox {
                        height: lvrec.height
                        id: forceCheck
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: unitDisplay.right
                        anchors.leftMargin: -5
                        // Layout.leftMargin: -10
                        scale: 0.7
                        //onClicked: bl.setForce = checked
                        onClicked: model.force = checked
                        // if check box is checked change row except value  color to yellow
                    }

                    //TextEdit {
                    TextField {
                        //height: lvrec.height
                        id: forcedUserInput
                        //text: model.userInput
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: forceCheck.right
                        anchors.leftMargin: -5
                        //verticalAlignment: Text.AlignBottom
                        onEditingFinished: model.userInput = text
                        horizontalAlignment: Text.AlignHCenter
                    }
                }
            }
        }
    }
}



