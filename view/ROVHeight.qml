import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

        Item {
            anchors.fill: parent



            Repeater {
                model: 14
                Rectangle {
                    id:one
                    height: 1
                    width: 50
                    x: parent.width - width
                    y: parent.height/2 + (index-rov.deep)*(parent.height/4)
                    Behavior on y {NumberAnimation {duration: 300}}
                    color: "white"

                    Repeater {
                        model: 3
                        Rectangle {
                            height: 1
                            width: (index == 1) ? 30 : 15
                            x: parent.width - width
                            y: ((rov.height/4)/4) * (index+1)
                            color: "white"
                        }
                    }
                }
            }

            Repeater {
                model: 14
                Text {
                    text: index
                    x: parent.width-60
                    y: parent.height/2 + (index-rov.deep)*(parent.height/4) - 8
                    Behavior on y {NumberAnimation {duration: 300}}
                    font.pixelSize: 15
                    font.bold: true
                    color: "yellow"
                }
            }


        Rectangle {
            id: heightPosition
            height: 2
            width: 80
            x: parent.width - width
            y: parent.height/2
            color: "orange"
        }
  }



