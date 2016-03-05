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

    property bool open: false
    property bool switchIt: true
    clip: true


    Rectangle {
        id: top
        width: parent.width
        height: parent.height/10
        color: "white"
        rotation: 0
        x: 0
        y: 0
        Behavior on y {NumberAnimation {duration: 100}}
        Behavior on rotation {NumberAnimation {duration: 100}}
    }

    Rectangle {
        id: mid
        width: parent.width
        height: parent.height/10
        color: "white"

        x: 0
        y: parent.height/2 - height/2

        Behavior on x {NumberAnimation {duration: 100}}
    }

    Rectangle {
        id: bottom
        width: parent.width
        height: parent.height/10
        color: "white"
        rotation: 0
        x: 0
        y: parent.height - height
        Behavior on y {NumberAnimation {duration: 100}}
        Behavior on rotation {NumberAnimation {duration: 100}}
    }

    MouseArea {
        id: hamClick
        anchors.fill: parent
        onClicked: {
            if (!open) {
                drawer.opacity = 1
                drawer.offset = drawer.width

                top.y = top.parent.height/2 - top.height/2
                top.rotation = (switchIt) ? -45 : 45

                mid.x = -mid.width

                bottom.y = bottom.parent.height/2 - bottom.height/2
                bottom.rotation = (switchIt) ? 45 : -45

                open = true
            } else {
                drawer.offset = 0

                top.y = (switchIt) ? top.parent.height - top.height : 0;
                top.rotation = 0

                mid.x = 0

                bottom.y = (switchIt) ? 0 : bottom.parent.height - bottom.height
                bottom.rotation = 0

                open = false
                switchIt = !switchIt
            }
        }
    }
}
