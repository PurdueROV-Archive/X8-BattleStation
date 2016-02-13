import QtQuick 2.4
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.0

Item {
    anchors.fill: parent
    anchors.margins: 15

    ROVScrollingBox {
        id: taskList
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: points.top

        clip: true

        spacing: 20

        property int value: {
            (task1.value)  + (task2.value)  + (task3.value)  +
            (task4.value)  + (task5.value)  + (task6.value)  +
            (task7.value)  + (task8.value)  + (task9.value)  +
            (task10.value) + (task11.value) + (task12.value) +
            (task13.value)
        }

        ROVMissionTask {
            id: task1
            text: "Remove algae sample underneath ice - 5pts"
            worth: 5
        }
        ROVMissionTask {
            id: task2
            text: "Return algae sample - 5pts"
            worth: 5
        }
        ROVMissionTask {
            id: task3
            text: "Remove sea urchin - 5pts"
            worth: 5
        }
        ROVMissionTask {
            id: task4
            text: "Return sea urchin - 5pts"
            worth: 5
        }
        ROVMissionTask {
            id: task5
            text: "Count and identify star species - 10pts"
            worth: 10
        }
        ROVMissionTask {
            id: task6
            text: "Deploy acoustic sensor - 10pts"
            worth: 10
        }
        ROVMissionTask {
            id: task7
            text: "Survey iceberg at 4 points - 5pts"
            worth: 5
        }
        ROVMissionTask {
            id: task8
            text: "Measure iceberg keel depth - 10pts"
            worth: 10
        }
        ROVMissionTask {
            id: task9
            text: "Measure iceberg diameter - 10pts"
            worth: 10
        }
        ROVMissionTask {
            id: task10
            text: "Calculate iceberg volume - 5pts"
            worth: 5
        }
        ROVMissionTask {
            id: task11
            text: "Map location of iceberg from coordinates - 10pts"
            worth: 10
        }
        ROVMissionTask {
            id: task12
            text: "Determine iceberg threat to surface - 10pts"
            worth: 10
        }
        ROVMissionTask {
            id: task13
            text: "Determine iceberg threat to subsea assets - 10pts"
            worth: 10
        }
    }

    Label {
        id: points
        height: 40
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        verticalAlignment: Text.AlignBottom

        font.bold: true
        font.pixelSize: 20
        color: "white"
        text: "Science Under the Ice: " + taskList.value + "pts"
    }
}
