import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.0

import "view" as ROVView

Window {
    property string rovName: "X8"
    property string cerulean: "#6D9BC3"
    property string teal:     "#00BCD4"
    property string amber:    "#FFC107"
    property string mainColor: "#455A64"
    property string mainAccent: amber

    id: mainWindow
    visible: true
    width: 1920
    height: 1010
    visibility: "Maximized"
    color: "#151515"
    title: "Purdue IEEE | ROV " + rovName
    objectName: "mainWindow"


    Rectangle {
        id: actionBar
        height: 60
        width: mainWindow.width
        color: mainColor

        Text {
            x: 20
            height: actionBar.height
            font.pixelSize: 30

            color: "white"
            verticalAlignment: Text.AlignVCenter

            text: "Purdue IEEE | ROV " + rovName + " BattleStation"
        }

        Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: actionBar.bottom
            height: 20
            gradient: Gradient {
                 GradientStop { position: 0.0; color: "#33000000" }
                 GradientStop { position: 1.0; color: "#00000000" }
             }
        }
    }

    Item {
        objectName: "mainGrid"
        id: mainGrid

        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.top: actionBar.bottom

        anchors.margins: 10
        anchors.topMargin: 20
        anchors.bottomMargin: 20

        clip: true
        transformOrigin: Item.TopLeft



        //Left Column
        Column {
            id: leftColumn

            width: mainGrid.width/3 - 10
            height: mainGrid.height
            spacing: 20

            anchors.top: mainGrid.top
            anchors.left: mainGrid.left
            anchors.leftMargin: 0

            ROVView.GUITimer{}

            ROVView.ROVCard {
                title: "Card 1"
                anchors.left: parent.left
                anchors.right: parent.right
                height: parent.height - 150
                headerColor: mainColor
            }

        }

        //Center Column
        Column {
            id: centerColumn

            width: mainGrid.width/3 - 10
            height: mainGrid.height
            spacing: 20

            anchors.top: mainGrid.top
            anchors.horizontalCenterOffset: 0
            anchors.horizontalCenter: parent.horizontalCenter

            ROVView.ROVCard {
                title: "Card 2"
                anchors.left: parent.left
                anchors.right: parent.right
                height: parent.height
                headerColor: mainColor
            }

        }

        //Right Column
        Column {
            id: rightColumn

            width: mainGrid.width/3 - 10
            height: mainGrid.height
            spacing: 20

            anchors.top: mainGrid.top
            anchors.right: mainGrid.right
            anchors.rightMargin: 0

            ROVView.ROVCard {
                title: "Card 3"
                anchors.left: parent.left
                anchors.right: parent.right
                height: parent.height/2
                headerColor: mainColor
            }

            ROVView.GUIConfiguration{}
        }
    }
}
