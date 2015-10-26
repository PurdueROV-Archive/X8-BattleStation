import QtQuick 2.4
import QtGraphicalEffects 1.0


Rectangle {

    id: main
    property string headerColor
    property string accent

    MouseArea {
        id: ma
        anchors.fill: parent
        hoverEnabled: true
        propagateComposedEvents: true

        onPressed: {
            if (styleData.selected === false) {
                animation.stop()
            }

            if (!animation.running) {
                woop.size = 0
                woop.opacity = 0.3
                woop.mouseX = mouse.x
                woop.mouseY = mouse.y
                animation.start()
            }
            mouse.accepted = false


        }
    }

    Rectangle {
        id: rovTab
        color: main.headerColor
        width: parent.width
        height: parent.height
    }

    Rectangle {
        id: woop
        property int size: 0
        property int max: parent.width*2
        property int mouseX: 0
        property int mouseY: 0
        width: size
        height: size
        radius: size
        color: "white"
        x: mouseX-(size/2)
        y: mouseY-(size/2)
        opacity: 0.3

        SequentialAnimation {
            id: animation
            NumberAnimation {
                target: woop
                property: "size"
                from: 0
                to: woop.max
                duration: 400
            }
            NumberAnimation {
                target: woop
                property: "opacity"
                from: 0.3
                to: 0.0
                duration: 700
            }
        }

    }

    Text {
        id: text
        anchors.centerIn: parent
        text: styleData.title
        color: "white"
        font.bold: styleData.selected
        font.pixelSize: 12
        z: 2
    }

    Rectangle {
        width: parent.width
        height: 3
        anchors.bottom: parent.bottom
        opacity: styleData.selected ? 1.0 : (ma.containsMouse ? 0.5 :  0)
        color: main.accent
    }
}
