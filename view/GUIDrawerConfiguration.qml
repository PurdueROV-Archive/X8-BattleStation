import QtQuick 2.4
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.0

Item {
    anchors.fill: parent


    //Serial and Controller Config
    Column {
        anchors.fill: parent
        spacing: 10

        Label {
            text: "Configuration"
            anchors.left: parent.left;
            anchors.right: parent.right

            font.bold: true
            font.pixelSize: 18
            color: "white"
        }


        Label {
            text: "\nJoystick 1:"
            anchors.left: parent.left;
            anchors.right: parent.right

            font.bold: true
            font.pixelSize: 18
            color: "white"
        }



        Item {
            width: parent.width
            height: 30

            ComboBox {
                id: joystick1Combo
                height: 30
                anchors.left: parent.left;
                anchors.right: refresh.left;
                anchors.rightMargin: 10
                model: controller.JoystickDevices
                enabled: !controller.Running
                onCurrentIndexChanged: controller.JoystickSelect(currentIndex)
            }

            ROVButton {
                id: refresh
                height: 30
                width: 50
                anchors.right: parent.right
                text: "↻"
                fontSize: 20
                bold: true
                enabled: !controller.Running
                onClicked: controller.RefreshLists()
            }
        }

        Label {
            text: "\nROV IP:"
            anchors.left: parent.left;
            anchors.right: parent.right

            font.bold: true
            font.pixelSize: 18
            color: "white"
        }

        Item {
            width: parent.width
            height: 30

            TextField {
                id: connectionIP
                height: 30
                anchors.left: parent.left
                anchors.right: connectionPort.left
                anchors.rightMargin: 10
                horizontalAlignment: Text.AlignRight
                width: parent.width
                text: "192.168.1.100"
                enabled: !controller.Running
                font.pixelSize: 20
                Binding {
                    target: controller
                    property: "ConnectionIP"
                    value: connectionIP.text
                }
            }


            TextField {
                id: connectionPort
                height: 30
                width: 100
                anchors.right: parent.right
                text: "5100"
                enabled: !controller.Running
                font.pixelSize: 20
                validator: IntValidator {bottom: 1; top: 65536;}
                onTextChanged: {
                    if (text.length < 1) {
                        controller.ConnectionPort = 0
                    }
                }

                Binding {
                    target: controller
                    property: "ConnectionPort"
                    value: connectionPort.text
                }
            }

        }



        Label {
            text: "\nTuning Constants:"
            anchors.left: parent.left;
            anchors.right: parent.right

            font.bold: true
            font.pixelSize: 18
            color: "white"
        }

        Label {
            text: "Tuning Constant: A"
            anchors.left: parent.left;
            anchors.right: parent.right

            font.pixelSize: 12
            color: "white"
        }
        TextField {
            height: 30
            horizontalAlignment: TextInput.AlignHCenter
            width: parent.width
            text: "0"
            validator: IntValidator {bottom: -32678; top: 32677;}
            enabled: !controller.Running
            font.pixelSize: 20
        }
        Label {
            text: "Tuning Constant: B"
            anchors.left: parent.left;
            anchors.right: parent.right

            font.pixelSize: 12
            color: "white"
        }
        TextField {
            height: 30
            horizontalAlignment: TextInput.AlignHCenter
            width: parent.width
            text: "0"
            validator: IntValidator {bottom: -32678; top: 32677;}
            enabled: !controller.Running
            font.pixelSize: 20
        }
        Label {
            text: "Tuning Constant: C"
            anchors.left: parent.left;
            anchors.right: parent.right

            font.pixelSize: 12
            color: "white"
        }
        TextField {
            height: 30
            horizontalAlignment: TextInput.AlignHCenter
            width: parent.width
            text: "0"
            validator: IntValidator {bottom: -32678; top: 32677;}
            enabled: !controller.Running
            font.pixelSize: 20
        }

        Label {
            text: "\nPivots X, Y, Z:"
            anchors.left: parent.left;
            anchors.right: parent.right

            font.bold: true
            font.pixelSize: 18
            color: "white"
        }

        Item {
            anchors.right: parent.right
            anchors.left: parent.left
            height: 30

            TextField {
                id: xPivot
                height: 30
                horizontalAlignment: TextInput.AlignHCenter
                anchors.right: yPivot.left
                anchors.left: parent.left
                anchors.rightMargin: 10
                text: "0"
                validator: IntValidator {bottom: -128; top: 127;}
                enabled: !controller.Running
                font.pixelSize: 20
            }
            TextField {
                id: yPivot
                height: 30
                anchors.horizontalCenter: parent.horizontalCenter
                width: (parent.width / 3) - 20
                horizontalAlignment: TextInput.AlignHCenter
                text: "0"
                validator: IntValidator {bottom: -128; top: 127;}
                enabled: !controller.Running
                font.pixelSize: 20
            }
            TextField {
                id: zPivot
                height: 30
                horizontalAlignment: TextInput.AlignHCenter
                anchors.right: parent.right
                anchors.left: yPivot.right
                anchors.leftMargin: 10
                text: "0"
                validator: IntValidator {bottom: -128; top: 127;}
                enabled: !controller.Running
                font.pixelSize: 20
            }
        }
    }
}
