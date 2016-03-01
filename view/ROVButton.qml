import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

Item {

    property int fontSize: 30
    property string color: mainColor
    property string  text: ""
    property bool    bold: false

    signal clicked

    id: rovButton

    property int buttonRadius: 2

    Rectangle {
        id: background
        radius: buttonRadius
        anchors.fill: parent
        clip: true

        color: (rovButton.enabled) ? rovButton.color : "#bbbbbb"

        Rectangle {
            anchors.fill: parent
            color: "white"
            radius: buttonRadius
            opacity: (ma.containsMouse) ? 0.3 : 0.0
            Behavior on opacity {NumberAnimation {duration: 300}}
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

    }

    Rectangle {
        z: -1
        height: rovButton.height
        width: rovButton.width
        anchors.horizontalCenter: rovButton.horizontalCenter
        anchors.top: rovButton.top
        anchors.topMargin: (ma.pressed) ? 6 : 3
        radius: buttonRadius
        color: "#30000000"

        opacity: (ma.containsMouse) ? 1 : 0.0
        Behavior on opacity {NumberAnimation {duration: 300}}
        Behavior on anchors.topMargin {NumberAnimation {duration: 100}}
    }


    Label {
        text: rovButton.text
        verticalAlignment: Text.AlignVCenter
        color: (rovButton.enabled) ? "white" : "#999999"
        font.pixelSize: fontSize
        horizontalAlignment: Text.AlignHCenter
        anchors.verticalCenter: rovButton.verticalCenter
        width: rovButton.width
        font.weight: Font.Thin
        font.bold: bold
    }


    MouseArea {
        id: ma
        anchors.fill: parent
        hoverEnabled: true
        propagateComposedEvents: true

        onClicked: {
            animation.stop()
            woop.size = 0
            woop.opacity = 0.3
            woop.mouseX = mouse.x
            woop.mouseY = mouse.y
            animation.start()

            mouse.accepted = false
            rovButton.clicked()
        }
    }
}
