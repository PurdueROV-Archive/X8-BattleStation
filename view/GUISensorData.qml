import QtQuick 2.4
import QtQuick.Controls 1.2
import QtGraphicalEffects 1.0
import QtQuick.Controls.Styles 1.0


ROVCard {
    title: "Sensor Data"
    anchors.left: parent.left
    anchors.right: parent.right
    height: parent.height/2
    headerColor: mainColor

    ROVGraph {
         id: graph
         anchors.fill: parent
         height: 200
         property int minData: -30
         property int maxData: 30
         property variant data: controller.TempData
         property int number: data.length
     }
}