import QtQuick 2.0
import QtGraphicalEffects 1.0

ROVCard {
    title: "Telemetry"
    anchors.left: parent.left
    anchors.right: parent.right
    height: parent.height/2
    headerColor: mainColor

    //Status Indicator
    Rectangle {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 10
        anchors.topMargin: 10

        property int size: 20
        width: size
        height: size
        radius: size

        color: controller.Running ? (controller.Communication ? "#22ff22" : "#ff2222") : "#dddddd"
    }

    ROVTelemetry{}

    ROVHeight{
    id: rov
    property real deep: mainWindow.depth
    }

}
