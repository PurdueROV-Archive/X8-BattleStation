import QtQuick 2.4
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.2

ComboBox {

    id: box1

    style: ComboBoxStyle {
        background: Rectangle {
            border.width: control.activeFocus ? 2 : 1
            color: control.hovered ? "#333333" : "#00000000"
            radius: 0
            border.color: mainColor
            implicitWidth: 30
            implicitHeight: 30
        }

    }
}
