import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.3

RadioButton {

    property int size

    id: radioButton

    style: RadioButtonStyle {
         indicator: Rectangle {
                 implicitWidth: radioButton.size
                 implicitHeight: radioButton.size
                 radius: radioButton.size
                 border.color: control.checked ? mainColor : "#606060"
                 border.width: 2
                 Rectangle {
                     visible: control.checked
                     color: mainColor
                     radius: radioButton.size
                     width: radioButton.size/2
                     height: radioButton.size/2
                     anchors.centerIn: parent
                 }
         }

         label: Text {
             text: control.text
             color: "white"
             font.pixelSize: radioButton.size
         }

         spacing: 8
     }


}
