import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    anchors.fill: parent

    Item {
        anchors.fill: parent
        Rectangle {
            id: circle
            property real size: parent.width/2
            property real rotationValue: controller.Rotation
            Behavior on rotationValue {NumberAnimation {duration: 100}}
            width: size
            height: size
            anchors.centerIn: parent
            radius: size
            color: "#2e2e2e"

            Item {
                property int pitch: controller.Pitch
                Behavior on pitch {NumberAnimation {duration: 100}}
                width: parent.width
                height: parent.width
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                rotation: circle.rotationValue

                Column {
                    y: parent.pitch
                    spacing: (circle.size - (3*9))/8
                    anchors.horizontalCenter: parent.horizontalCenter
                    Repeater {
                        model: 9
                        Rectangle {
                            anchors.horizontalCenter: parent.horizontalCenter
                            width: (index == 4) ? circle.size : circle.size/2;
                            height: 3
                            color: amber
                            radius: 2
                        }
                    }
                }
            }

            Rectangle {
                width: 4
                height: 60

                color: "black"
                rotation: circle.rotationValue
                x: circle.size/2 + Math.sin(rotation*(Math.PI/180))*(circle.size/2) - (width/2)
                y: circle.size/2 - Math.cos(rotation*(Math.PI/180))*(circle.size/2) - (height/2)
            }


            layer.enabled: true
            layer.effect: OpacityMask {
                maskSource: Item {
                    width: circle.width
                    height: circle.height
                    Rectangle {
                        anchors.centerIn: parent
                        width: circle.width
                        height: circle.width
                        radius: circle.width
                    }
                }
            }
        }

    }

    Rectangle {
        anchors.centerIn: parent
        width: circle.size+5
        height: circle.size+5
        radius: circle.size
        color: "#00000000"
        border.width: 5
        border.color: "black"
    }
}