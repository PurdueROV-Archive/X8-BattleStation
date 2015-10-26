import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2


CheckBox {
    id: checkTask
    property int size

    style: CheckBoxStyle {

        indicator: Rectangle {
            id: indicator
            implicitWidth: size
            implicitHeight: size
            radius: 2
            border.width: 2
            border.color: "#606060"
            Rectangle {
                visible: control.checked
                color: mainColor
                radius: 2
                implicitWidth: size
                implicitHeight: size
                border.width: 2
                border.color: mainColor

                Label {
                    text: "✓"
                    color: "white"
                    font.pixelSize: checkTask.size-8
                    font.bold: true
                    width: checkTask.size
                    height: checkTask.size
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignTop
                }
            }
        }

        label: Text {
            id: taskLabel
            color: "white"
            font.pixelSize: size
            text: checkTask.text
            x: 5
        }
    }
}
