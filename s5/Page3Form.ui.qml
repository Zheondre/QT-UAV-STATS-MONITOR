import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    id: page
    width: applicationWindow.width
    height: applicationWindow.height

    header: Label {
        //text: qsTr("Page 3")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    Rectangle {
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width - 30
        height: 500
    }

    Label {
        text: qsTr("data plot.")
        anchors.centerIn: parent
    }
}
