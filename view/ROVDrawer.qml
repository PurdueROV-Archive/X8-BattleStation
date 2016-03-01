import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Rectangle {
    id: drawer

    default property alias children: body.children
    property int offset: 0
    color: "#111111"
    width: 400
    height: parent.height - 60
    anchors.bottom: parent.bottom
    opacity: 0
    x: parent.width - offset
    Behavior on x {NumberAnimation {duration: 100}}
    z: 100

    MouseArea {
        anchors.fill: parent
        preventStealing: true
        propagateComposedEvents: false
    }

    Item  {
        id: body
        anchors.fill: parent
        anchors.margins: 10


    }

}
