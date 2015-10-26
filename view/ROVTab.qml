import QtQuick 2.4
import QtGraphicalEffects 1.0


Rectangle {

    MouseArea {
        id: ma
        anchors.fill: parent
        hoverEnabled: true
        propagateComposedEvents: true

        onPressed: {

            if (!animation.running) {
                woop.size = 0
                woop.opacity = 0.4
                woop.mouseX = mouse.x
                woop.mouseY = mouse.y
                animation.start()
            }
            mouse.accepted = false
        }
    }

    Rectangle {
        id: rovTab
        color: (styleData.selected) ? "#222222" : "#111111"
        radius: 0
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
        color: mainColor
        x: mouseX-(size/2)
        y: mouseY-(size/2)
        opacity: 0.4

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
                from: 0.4
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
        height: 2
        anchors.bottom: parent.bottom
        opacity: styleData.selected ? 1.0 : (ma.containsMouse ? 1.0 :  0.5)
        color: mainColor
    }
}
