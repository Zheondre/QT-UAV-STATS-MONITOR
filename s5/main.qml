import QtQuick 2.12
import QtQuick.Controls 2.4 //needed for linux
//import QtQuick.Controls 2.12
import QtQuick.Layouts 1.1
import QtGraphicalEffects 1.15

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: ApplicationWindow.width
    height: 480
    title: qsTr("Ballard")
    Item{
     id: itemDesc
     property var ph: 24
     property var pw: 24
    // property var tchBttnClr: "white"
     property var tchBttnClr:"#004e66"

    }
    Rectangle {
        id: mainHeader
        //height: 45
        height: 70
        width: parent.width
        color: "#007ea3"

// if we are on Menu change image and appear on the right of the screen
        RoundButton {
            id: roundButton
            anchors.left: parent.left
            anchors.leftMargin: 10
            flat: true
            display: AbstractButton.IconOnly
            anchors.verticalCenter: parent.verticalCenter
            //width: itemDesc.pw
            //height: itemDesc.ph
            icon.color: "transparent"
            icon.source: "images/menu-4-24.ico"
            padding: 0
            //onClicked: UtilsForm.show()
            onClicked: m1.open()
            background: Rectangle {
                color: tabBar.currentIndex == 3 ? itemDesc.tchBttnClr : "#007ea3"
            }
        }
    Menu{
     id:m1

     MenuItem {
         //img: ""
         // id: l1;
         text: "Home"
     }
     MenuItem {
         //img: ""
         // id: l1;
         text: "Favorites"
     }
     MenuItem {
         //img: ""
         // id: l1;
         text: "Input/Output "
     }
     MenuItem {
         //img: ""
         text: "Save Settings"
     }
     MenuItem {
         //img: ""
         text: "Load Settings"
     }
     MenuItem {
         //img: ""
         // id: l1;
         text: "System Loader"
     }
     MenuItem {
         //img: ""
         text: "Datalog Reader"
     }
     MenuItem {
         //img: ""
         text: "Mobile Logs"
     }
     MenuItem {
         //img: ""
         text: "About"
     }
     MenuItem {
         //img: ""
         text: "Help"
     }

    }
        Row {

            width: ApplicationWindow.width
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            Label {
                text: qsTr("Status: ")
               // leftPadding: 6
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                color: "white"
                font.pixelSize: 20

            }

            Label {
                id: labelStatus
                text: qsTr("NODATA")
                horizontalAlignment: Text.AlignHCenter
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                color: "white"
                font.pixelSize: 20
            }
        }
    }

    SwipeView {
        id: swipeView
        anchors.top: parent.top
        anchors.topMargin: mainHeader.height
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        currentIndex: tabBar.currentIndex

        Page1Form {
        }

        FavsForm {
        }

        Page2Form {
        }


        Page3Form {
        }

        Page4Form {
        }

    }

    footer: TabBar {
        id: tabBar
        contentHeight: 50
        currentIndex: swipeView.currentIndex

        TabButton {
            id: tabButton2
            //if desktop
            //text: qsTr("FAVS")
            //els if mobile
            //text: qsTr("HOME")

            Image {
                width: itemDesc.pw
                height: itemDesc.ph
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                source:"images/home-7-32.ico"
             }

            background: Rectangle {
                color: tabBar.currentIndex == 0 ? itemDesc.tchBttnClr : "#007ea3"
            }
        }
        TabButton {
            id: tabButtonfavs
            //if desktop
            //text: qsTr("FAVS")
            Image {
                width: itemDesc.pw
                height: itemDesc.ph
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                source:"images/star-4-32.ico"
             }

            background: Rectangle {
                color: tabBar.currentIndex == 1 ? itemDesc.tchBttnClr : "#007ea3"
            }
        }

        TabButton {
            //text: qsTr("I/O")
            Image {
                width: itemDesc.pw + 6
                height: itemDesc.ph + 6
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
               source:"images/i-o.png"
            }
            background: Rectangle {
                color: tabBar.currentIndex == 2 ? itemDesc.tchBttnClr : "#007ea3"
            }
        }
        TabButton {
            id: tabButton
           // text: qsTr("PLOT")
            Image {
                id: pt
                width: itemDesc.pw
                height: itemDesc.ph
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
               source:"images/graph-32.ico"
            }
/*
            ColorOverlay {
                   anchors.fill: pt
                   source: pt
                   color: black
               }*/
            background: Rectangle {

                color: tabBar.currentIndex == 3 ? itemDesc.tchBttnClr : "#007ea3"
            }
        }
        TabButton {
            id: tabButton1
            //text: qsTr("ALARMS")
            Image {
                width: itemDesc.pw
                height: itemDesc.ph
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
               source:"images/error-2-32.ico"
            }
            background: Rectangle {
                color: tabBar.currentIndex == 4 ? itemDesc.tchBttnClr : "#007ea3"
            }
        }
        /*
        TabButton {
            text: qsTr("UTIL")
            background: Rectangle {
                color: tabBar.currentIndex == 4 ? tchBttnClr: "#007ea3"
            }
        }
        */
    }
}





/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.009999999776482582;height:480;width:640}D{i:27;anchors_height:25;anchors_width:25}
D{i:33;anchors_height:25;anchors_width:25}D{i:36;anchors_height:25;anchors_width:25}
}
##^##*/
