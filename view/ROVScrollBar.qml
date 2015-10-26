import QtQuick 2.0

//Based of scrollbar by Stack Overflow Commentor: bacarozzo
//found on Stack Overflow here: http://stackoverflow.com/a/26583525

Item {
   id: scrollbar

    property Flickable flick : undefined
    property int basicWidth: 10
    property int expandedWidth: 20
    property alias color : bar.color
    property alias radius : bar.radius

    clip: true
    visible: flick.visible

    MouseArea {
        id: scrollbarMA
        anchors.fill: parent
        hoverEnabled: true
        onWheel: {
            if (wheel.angleDelta.y > 0) {
                flick.flick(0, 800)
            } else if (wheel.angleDelta.y < 0) {
                flick.flick(0, -800)
            }
        }
    }

    Rectangle {
        id: bar
        clip: true
        width: basicWidth
        anchors.right: parent.right
        height: flick.visibleArea.heightRatio * flick.height
        visible: flick.visibleArea.heightRatio < 1.0
        radius: 10

        opacity: ma.pressed ? 1 : ma.containsMouse ? 0.65 : 0.4
        Behavior on opacity {NumberAnimation{duration: 150}}

        Binding {
            target: bar
            property: "width"
            value: expandedWidth
            when: ma.drag.active || ma.containsMouse || scrollbarMA.containsMouse
        }
        Behavior on width {NumberAnimation {duration: 150}}

        Binding {
            target: bar
            property: "y"
            value: !isNaN(flick.visibleArea.heightRatio) ? (ma.drag.maximumY * flick.contentY) / (flick.contentHeight * (1 - flick.visibleArea.heightRatio)) : 0
            when: !ma.drag.active
        }

        Binding {
            target: flick
            property: "contentY"
            value: ((flick.contentHeight * (1 - flick.visibleArea.heightRatio)) * bar.y) / ma.drag.maximumY
            when: ma.drag.active && flick !== undefined
        }

        MouseArea {
            id: ma
            anchors.fill: parent
            hoverEnabled: true
            drag.target: parent
            drag.axis: Drag.YAxis
            drag.minimumY: 0
            drag.maximumY: flick.height - bar.height
            //preventStealing: true
        }
    }
}
