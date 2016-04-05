import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.0

import "view" as ROVView

Window {
    property string rovName:   "X8"
    property string cerulean:  "#6D9BC3"
    property string teal:      "#00BCD4"
    property string amber:     "#FFC107"
    property string slate:     "#455A64"
    property string mainColor:  slate
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

            text: "BattleStation"
            font.weight: Font.Thin
        }

        Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: actionBar.bottom
            height: 5
            color: "black"
            opacity: 0.2
        }

        ROVView.ROVHamburger {
            drawer: drawer
        }


    }

    ROVView.ROVDrawer {
        id: drawer

        ROVView.GUIDrawerConfiguration{}
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

            width: mainGrid.width*0.3 - 10
            height: mainGrid.height
            spacing: 20

            anchors.top: mainGrid.top
            anchors.left: mainGrid.left
            anchors.leftMargin: 0

            ROVView.GUITimer{}

            ROVView.GUIMissionTasks{}

        }

        //Center Column
        Column {
            id: centerColumn

            width: mainGrid.width*0.4 - 10
            height: mainGrid.height
            spacing: 20

            anchors.top: mainGrid.top
            anchors.horizontalCenterOffset: 0
            anchors.horizontalCenter: parent.horizontalCenter

            ROVView.GUISystemStatus{}


            ROVView.GUIConfiguration{}
        }

        //Right Column
        Column {
            id: rightColumn

            width: mainGrid.width*0.3 - 10
            height: mainGrid.height
            spacing: 20

            anchors.top: mainGrid.top
            anchors.right: mainGrid.right
            anchors.rightMargin: 0

            ROVView.GUISensorData{}

            ROVView.GUIThrusters{}
        }
    }
}
