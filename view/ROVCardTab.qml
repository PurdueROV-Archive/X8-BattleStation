import QtQuick 2.4
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.0

Rectangle {
    id: card

    default property alias children: tabs.children

    property string title: ""
    property string headerColor: "#00BCD4"
    property string accent: "yellow"

    color: "#212121"
    radius: 2

    Rectangle {
        id: header
        width: parent.width
        height: 40
        color: card.headerColor
        radius: 2

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
            antialiasing: true
            font.bold: true
        }
    }

    Rectangle {
        id: backgroundFix
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: header.bottom
        anchors.topMargin: -5
        height: 35
        color: headerColor
    }

    TabView {
        id: tabs
        anchors.top: header.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        clip: true

        style: TabViewStyle {
            frameOverlap: 1
            tab: ROVCardTabs {
                clip: true
                implicitWidth: Math.round(tabs.width/tabs.count)
                implicitHeight: 30
                headerColor: card.headerColor
                accent: card.accent
            }
            frame: Rectangle {color: "transparent" }
            tabBar: Rectangle {color: card.headerColor }
        }

    }

    Rectangle {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: backgroundFix.bottom
        height: 10
        gradient: Gradient {
             GradientStop { position: 0.0; color: "#33000000" }
             GradientStop { position: 1.0; color: "#00000000" }
         }
    }

}
