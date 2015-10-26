import QtQuick 2.4


Row {
    default property alias children: body.children
    property int spacing: 10

    id: rowMain

    Flickable {
        id: flickable
        width: rowMain.width - (body.height > height ? 25 : 0)
        height: rowMain.height
        flickableDirection: Flickable.VerticalFlick
        contentHeight: body.height
        contentWidth: width
        boundsBehavior: Flickable.StopAtBounds
        clip: true

        Column {
            id: body
            spacing: rowMain.spacing
            width: parent.width
            clip: true
        }
    }

    ROVScrollBar {
        height: rowMain.height
        width: 25

        flick: flickable

        radius: 2
        basicWidth: 10
        expandedWidth: 15
        color: "#424242"
    }

}
