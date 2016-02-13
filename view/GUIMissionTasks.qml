import QtQuick 2.4
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.0


ROVCard {
    id: missionTasks
    anchors.left: parent.left
    anchors.right: parent.right

    height: parent.height - 130

    title: "Mission Tasks"
    headerColor: mainColor

    MissionTasks1 {}
}
