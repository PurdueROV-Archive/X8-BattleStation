import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2


CheckBox {
    id: checkTask
    property int size: 16;
    property int worth: 0
    property int value: checkTask.checked ? worth : 0

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
                    font.pixelSize: checkTask.size-6
                    font.bold: true
                    width: checkTask.size
                    height: checkTask.size
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }

        label: Text {
            id: taskLabel
            color: checkTask.checked ? "#666666" : "white"
            font.pixelSize: size
            font.strikeout: checkTask.checked
            text: checkTask.text
            font.bold: !checkTask.checked
            x: 5
        }
    }
}
