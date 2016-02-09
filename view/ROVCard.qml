import QtQuick 2.4
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.0

Rectangle {
    id: card

    default property alias children: body.children

    property string title: ""
    property string headerColor: "#ff3333"
    color: "#212121"
    radius: 2

    Rectangle {
        id: header
        width: parent.width
        height: 40
        color: headerColor
        radius: 2

        Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            height: 5
            color: headerColor
        }

        Label {
            id: label
            text: title
            color: "white"
            height: 20
            font.pixelSize: 20
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 20
            anchors.topMargin: 8
            font.weight: Font.Thin
            antialiasing: true
        }
    }

    Item {
        id: body
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: header.bottom
        anchors.margins: 15
        clip: true
    }

    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: header.bottom
        height: 2
        color: "black"
        opacity: 0.3
//        gradient: Gradient {
//             GradientStop { position: 0.0; color: "#33000000" }
//             GradientStop { position: 1.0; color: "#00000000" }
//         }
    }

}
