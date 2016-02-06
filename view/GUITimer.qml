import QtQuick 2.4

Item {

    property real startTime: 0
    property real delta: 0

    anchors.left: parent.left
    anchors.right: parent.right
    anchors.margins: 0
    height: 110

    //Timer
    Timer {
        id: timerTrigger
        interval:200
        running:false
        repeat: true
        onTriggered: {
            var tempTime = Math.floor(((new Date).getTime() - startTime)/1000);
            var secs = (tempTime % 60);
            var mins = Math.floor(tempTime/60);

            secs = (secs < 10) ? ("0" + secs) : secs;
            mins = (mins < 10) ? ("0" + mins) : mins;

            timer.text =  mins + ":" + secs;

            if (mins >= 10) {
                timer.color = "orange";
            }
            if (mins >= 13) {
                timer.color = "red"
            }

        }
    }

    ROVCard {
        id: timerArea
        anchors.fill: parent

        title: "Timer"
        headerColor: mainColor

            //Start button
            ROVButton {
                id: startBtn
                height: parent.height
                width: 150
                text: "Start"
                anchors.left: parent.left
                anchors.leftMargin: 30
                anchors.verticalCenter: parent.verticalCenter
                enabled: true
                onClicked: {
                    if (timerTrigger.running) {
                        timerTrigger.stop();
                        resetBtn.enabled = true;
                        delta = (new Date).getTime() - startTime;
                        startBtn.text = "Resume";
                    } else {
                        timerTrigger.running = true;
                        resetBtn.enabled = false;
                        startBtn.text = "Pause";
                        if (startTime == 0) {
                            startTime = (new Date).getTime();
                        } else {
                            startTime = (new Date).getTime() - delta;
                        }
                    }
                }
            }

            //Stop button
            ROVButton {
                id: resetBtn
                height: parent.height
                width: 150
                text: "Reset"
                anchors.right: parent.right
                anchors.rightMargin: 30
                anchors.verticalCenter: parent.verticalCenter
                enabled: false
                onClicked: {
                    if (!timerTrigger.running) {
                        timerTrigger.running = false;
                        resetBtn.enabled = false;
                        startBtn.text = "Start";
                        timer.text = "00:00";
                        timer.color = mainColor;
                        startTime = 0;
                    }
                }
            }

            //Timer text
            Text {
                id: timer
                y: 0
                width: 171
                height: 70
                text: "00:00"
                anchors.horizontalCenter: parent.horizontalCenter
                verticalAlignment: Text.AlignVCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenterOffset: 0

                color: mainColor
                font.family: "Arial"
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 50
            }
    }
}
