import QtQuick 2.4
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.0

ROVCard {
    id: thrusters
    anchors.left: parent.left
    anchors.right: parent.right

    height: (parent.height/2)

    title: "Thrusters"
    headerColor: mainColor

    Item {
        anchors.fill: parent
        anchors.margins: 15

        Grid {
            id: horizontalThrusters
            width: 280
            height: 280
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            antialiasing: true
            columns: 2
            rows: 2
            spacing: 100
            ROVThruster {
                orientation: "horizontal";
                rotation: 20;
                value: (controller.Running && controller.ThrusterValues[0]) ? controller.ThrusterValues[0] : "Off"
            }
            ROVThruster {
                orientation: "horizontal";
                rotation: -20;
                value: (controller.Running && controller.ThrusterValues[1]) ? controller.ThrusterValues[1] : "Off"
            }
            ROVThruster {
                orientation: "horizontal";
                rotation: 160;
                value: (controller.Running && controller.ThrusterValues[2]) ? controller.ThrusterValues[2] : "Off"
            }
            ROVThruster {
                orientation: "horizontal";
                rotation: 200;
                value: (controller.Running && controller.ThrusterValues[3]) ? controller.ThrusterValues[3] : "Off"
            }

        }

        Grid {
            width: 182
            height: 182
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            antialiasing: true
            columns: 2
            rows: 2
            spacing: 2
            ROVThruster {
                orientation: "vertical";
                value: (controller.Running && controller.ThrusterValues[4]) ? controller.ThrusterValues[4] : "Off"
            }
            ROVThruster {
                orientation: "vertical";
                value: (controller.Running && controller.ThrusterValues[5]) ? controller.ThrusterValues[5] : "Off"
            }
            ROVThruster {
                orientation: "vertical";
                value: (controller.Running && controller.ThrusterValues[6]) ? controller.ThrusterValues[6] : "Off"
            }
            ROVThruster {
                orientation: "vertical";
                value: (controller.Running && controller.ThrusterValues[7]) ? controller.ThrusterValues[7] : "Off"
            }
        }
    }
}
