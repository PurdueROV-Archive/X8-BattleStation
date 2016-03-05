import QtQuick 2.4
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.0

ROVCard {
    id: configuration
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.margins: 0

    height: (parent.height/2)

    title: "Configuration"
    headerColor: mainColor

    //Serial and Controller Config
    Column {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        spacing: 10


        Label {
            text: "Joystick 1: " + controller.JoystickName
            anchors.left: parent.left;
            anchors.right: parent.right

            font.bold: true
            font.pixelSize: 18
            color: "white"
        }
        Label {
            text: "Connection " + controller.ConnectionIP + ":" + controller.ConnectionPort
            anchors.left: parent.left;
            anchors.right: parent.right

            font.bold: true
            font.pixelSize: 18
            color: "white"
        }
    }

    ROVButton {
        id: threadControl
        height: 30
        width: 150
        anchors.centerIn: parent

        text: (!controller.Running) ? "Connect" : "Stop"
        enabled: controller.JoystickCount > 0
        fontSize: 20
        onClicked: {
            controller.Running = !controller.Running
        }
    }
}
