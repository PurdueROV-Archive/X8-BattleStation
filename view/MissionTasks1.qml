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

        spacing: 15

        property int value: {
            (task1.value)  + (task2.value)  + (task3.value)  +
            (task4.value)  + (task5.value)  + (task6.value)  +
            (task7.value)  + (task8.value)  + (task9.value)  +
            (task10.value) + (task11.value) + (task12.value) +
            (task13.value) + (task14.value) + (task15.value) +
            (task16.value) + (task17.value) + (task18.value) +
            (task19.value) + (task20.value) + (task21.value) +
            (task22.value) + (task23.value) + (task24.value) +
            (task25.value) + (task26.value) + (task27.value) +
            (task28.value) + (task29.value) + (task30.value) +
            (task31.value) + (task32.value) + (task33.value) +
            (task34.value) + (task35.value) + (task36.value) +
            (task37.value) + (task38.value) + (task39.value) +
            (task40.value)
        }

        ROVMissionTask {
            id: task1
            text: "Insert temperature into venting fluid – 10pts"
            worth: 10
        }


        Label {
            color: "white"
            font.pixelSize: 16
            font.bold: true
            text: "Measure temperature of venting fluid – 20pts"
        }
        ROVMissionTask {
            id: task2
            text: "within 2°C – 20pts"
            worth: 20
        }
        ROVMissionTask {
            id: task3
            text: "within 4°C – 10pts "
            worth: 10
        }
        ROVMissionTask {
            id: task4
            text: "within 5°C – 5pts"
            worth: 5
        }


        ROVMissionTask {
            id: task5
            text: "Determine thickness of ice crust - 10pts "
            worth: 10
        }
        ROVMissionTask {
            id: task6
            text: "Determine depth of the ocean under the ice - 10pts "
            worth: 10
        }


        Label {
            color: "white"
            font.pixelSize: 16
            font.bold: true
            text: "Connect the ESP to the power and communications hub – 50pts"
        }
        ROVMissionTask {
            id: task7
            text: "Retrieve the ESP connector – 5pts "
            worth: 5
        }
        ROVMissionTask {
            id: task8
            text: "Lay the ESP cable through a 1st waypoints  – 5pts"
            worth: 5
        }
        ROVMissionTask {
            id: task9
            text: "Lay the ESP cable through a 2nd waypoints  – 5pts"
            worth: 5
        }
        ROVMissionTask {
            id: task10
            text: "Lay the ESP cable through a 3rd waypoints  – 5pts"
            worth: 5
        }
        ROVMissionTask {
            id: task11
            text: "Open power and communications hub door – 10pts"
            worth: 10
        }
        ROVMissionTask {
            id: task12
            text: "Insert ESP connector into power and communications hub – 20pts"
            worth: 20
        }


        Label {
            color: "white"
            font.pixelSize: 16
            font.bold: true
            text: "Identify serial numbers of CubeSats - 20pts"
        }
        ROVMissionTask {
            id: task13
            text: "Identify 1st CubeSat – 5pts"
            worth: 5
        }
        ROVMissionTask {
            id: task14
            text: "Identify 2nd CubeSat – 5pts"
            worth: 5
        }
        ROVMissionTask {
            id: task15
            text: "Identify 3rd CubeSat – 5pts"
            worth: 5
        }
        ROVMissionTask {
            id: task16
            text: "Identify 4th CubeSat – 5pts"
            worth: 5
        }


        Label {
            color: "white"
            font.pixelSize: 16
            font.bold: true
            text: "Move CubeSats to collection basket - 20pts"
        }
        ROVMissionTask {
            id: task17
            text: "Move 1st CubeSat – 5pts"
            worth: 5
        }
        ROVMissionTask {
            id: task18
            text: "Move 2nd CubeSat – 5pts"
            worth: 5
        }
        ROVMissionTask {
            id: task19
            text: "Move 3rd CubeSat – 5pts"
            worth: 5
        }
        ROVMissionTask {
            id: task20
            text: "Move 4th CubeSat – 5pts"
            worth: 5
        }


        Label {
            color: "white"
            font.pixelSize: 16
            font.bold: true
            text: "Collect two oil samples from different mats - 10pts"
        }
        ROVMissionTask {
            id: task21
            text: "Collect 1st oil sample - 5pts"
            worth: 5
        }
        ROVMissionTask {
            id: task22
            text: "Collect 2nd oil sample - 5pts"
            worth: 5
        }

        Label {
            color: "white"
            font.pixelSize: 16
            font.bold: true
            text: "Return two oil samples to the surface - 10pts"
        }
        ROVMissionTask {
            id: task23
            text: "Return 1st oil sample - 5pts"
            worth: 5
        }
        ROVMissionTask {
            id: task24
            text: "Return 2nd oil sample - 5pts"
            worth: 5
        }



        Label {
            color: "white"
            font.pixelSize: 16
            font.bold: true
            text: "Analyze gas chromatograph of oil samples – 20pts"
        }
        ROVMissionTask {
            id: task25
            text: "Analyze 1st oil sample - 10pts"
            worth: 10
        }
        ROVMissionTask {
            id: task26
            text: "Analyze 1st oil sample - 10pts"
            worth: 10
        }


        Label {
            color: "white"
            font.pixelSize: 16
            font.bold: true
            text: "Photograph coral colonies - 10pts"
        }
        ROVMissionTask {
            id: task27
            text: "Photograph 1st coral - 5pts"
            worth: 5
        }
        ROVMissionTask {
            id: task28
            text: "Photograph 2nd coral - 5pts"
            worth: 5
        }


        Label {
            color: "white"
            font.pixelSize: 16
            font.bold: true
            text: "Compare coral colonies to previous years – 10pts"
        }
        ROVMissionTask {
            id: task29
            text: "Compare 1st coral colony - 5pts"
            worth: 5
        }
        ROVMissionTask {
            id: task30
            text: "Compare 2nd coral colony - 5pts"
            worth: 5
        }


        Label {
            color: "white"
            font.pixelSize: 16
            font.bold: true
            text: "Return coral colonies to surface – 10pts"
        }
        ROVMissionTask {
            id: task31
            text: "Return 1st coral colony - 5pts"
            worth: 5
        }
        ROVMissionTask {
            id: task32
            text: "Return 2nd coral colony - 5pts"
            worth: 5
        }

        ROVMissionTask {
            id: task33
            text: "Install flange to wellhead - 10pts"
            worth: 10
        }

        Label {
            color: "white"
            font.pixelSize: 16
            font.bold: true
            text: "Secure flange to wellhead with two bolts - 10pts"
        }
        ROVMissionTask {
            id: task34
            text: "Install 1st bolt - 5pts"
            worth: 5
        }
        ROVMissionTask {
            id: task35
            text: "Install 2nd bolt - 5pts"
            worth: 5
        }

        ROVMissionTask {
            id: task36
            text: "Install wellhead cap over flange - 10pts"
            worth: 10
        }

        Label {
            color: "white"
            font.pixelSize: 16
            font.bold: true
            text: "Secure cap to flange with four bolts - 20pts"
        }
        ROVMissionTask {
            id: task37
            text: "Install 1st bolt - 5pts"
            worth: 5
        }
        ROVMissionTask {
            id: task38
            text: "Install 2nd bolt - 5pts"
            worth: 5
        }
        ROVMissionTask {
            id: task39
            text: "Install 3rd bolt - 5pts"
            worth: 5
        }
        ROVMissionTask {
            id: task40
            text: "Install 4th bolt - 5pts"
            worth: 5
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
        text: "Collected Points: " + taskList.value + "pts"
    }
}
