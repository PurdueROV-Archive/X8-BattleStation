import QtQuick 2.4

    Item {
        id: path
        anchors.fill: parent

        Repeater {
            model: graph.number-1
            Rectangle {
                property int centerX: index*((graph.width-50) / (graph.number-1)) + 5
                property int centerY : (graph.maxData-graph.data[index])*graph.height/(graph.maxData-graph.minData) +5
                property int centerX2: (index+1)*((graph.width-50) / (graph.number-1)) + 5
                property int centerY2 : (graph.maxData-graph.data[index+1])*graph.height/(graph.maxData-graph.minData) +5

                width: Math.sqrt(Math.pow((centerX-centerX2),2)+Math.pow((centerY-centerY2),2))
                height: 1
                x: (centerX+centerX2)/2-width/2
                y: (centerY+centerY2)/2

                color: amber
                rotation: (Math.atan((centerY-centerY2)/(centerX-centerX2)))*180/Math.PI
            }
        }

        Repeater {
            model: graph.number
            Rectangle {
                width: 10
                height: width
                color: "white"
                x: index*((graph.width-50) / (graph.number-1))
                y: (graph.maxData-graph.data[index])*graph.height/(graph.maxData-graph.minData)
                radius: width
            }
        }
        Repeater {
            model: (graph.maxData-graph.minData)/10 + 1
        Rectangle {
            id:line1
            height: 1
            width: parent.width
            x:0
            y:graph.height*index/Math.round((graph.maxData-graph.minData)/10) + 5
        }
        }

       Repeater {
           model:Math.round((graph.maxData-graph.minData)/10) + 1

            Text {
                text: graph.maxData - index * 10
                x: 0
                y: graph.height*index/Math.round((graph.maxData-graph.minData)/10)-20
                font.pixelSize: 15
                font.bold: true
                //anchors.horizontalCenter: parent.horizontalCenter
                color: "white"
            }

       }


        Repeater {
            model: graph.number

            Text {
                id:label
                x: (graph.width-50)*index / (graph.number-1)
                y: (graph.maxData-graph.data[index])*graph.height/(graph.maxData-graph.minData)-20
                text: graph.data[index]
                font.pixelSize: 15
                color: "white"
            }
        }
}
