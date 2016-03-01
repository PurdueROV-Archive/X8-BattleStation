import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Item {
    property var drawer
    property int margin: 20
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.right: parent.right
    anchors.margins: margin
    width: parent.height/2

    Rectangle {
        width: parent.width
        height: parent.height/10
        color: "white"

        anchors.top: parent.top
    }
    Rectangle {
        width: parent.width
        height: parent.height/10
        color: "white"

        anchors.centerIn: parent
    }
    Rectangle {
        width: parent.width
        height: parent.height/10
        color: "white"

        anchors.bottom: parent.bottom
    }

    Rectangle {
        id: woop
        property int size: 0
        property int max: parent.width*1.5
        width: size
        height: size
        radius: size
        color: "white"
        anchors.centerIn: parent
        opacity: 0.3

        SequentialAnimation {
            id: animation
            NumberAnimation {
                target: woop
                property: "size"
                from: 0
                to: woop.max
                duration: 150
            }
            NumberAnimation {
                target: woop
                property: "opacity"
                from: 0.3
                to: 0.0
                duration: 100
            }
        }
    }

    MouseArea {
        id: hamClick
        anchors.fill: parent
        onClicked: {
            animation.stop()
            woop.size = 0
            woop.opacity = 0.3
            animation.start()

            drawer.opacity = 1
            drawer.offset = (drawer.offset > 0) ? 0 : drawer.width
        }
    }
}
