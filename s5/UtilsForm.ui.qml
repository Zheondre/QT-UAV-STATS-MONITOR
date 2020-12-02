import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.1

Page {
    id: page

    width: applicationWindow.width
    height: applicationWindow.height

    Rectangle {
        width: parent.width
        height: parent.height
        color: "#90A4AE"

        // height: applicationWindow.height - (50 + 90)
        ListView {

            width: parent.width
            height: parent.height
            spacing: 1
            //model: utilsModel {}
            model: ListModel {

                ListElement {
                    //img: ""
                    // id: l1;
                    name: "Home"
                }
                ListElement {
                    //img: ""
                    // id: l1;
                    name: "Favorites"
                }
                ListElement {
                    //img: ""
                    // id: l1;
                    name: "Input/Output "
                }
                ListElement {
                    //img: ""
                    name: "Save Settings"
                }
                ListElement {
                    //img: ""
                    name: "Load Settings"
                }
                ListElement {
                    //img: ""
                    // id: l1;
                    name: "System Loader"
                }
                ListElement {
                    //img: ""
                    name: "Datalog Reader"
                }
                ListElement {
                    //img: ""
                    name: "Mobile Logs"
                }
                ListElement {
                    //img: ""
                    name: "About"
                }
                ListElement {
                    //img: ""
                    name: "Help"
                }
            }
            delegate: Rectangle {
                //ListModel.get.:
                width: parent.width
                height: 55
                Text {
                    text: name
                    horizontalAlignment: Text.AlignHCenter
                    anchors.horizontalCenter: page.horizontalCenter
                    anchors.centerIn: parent
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}
}
##^##*/
